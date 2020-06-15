/**
 * author: Hui Ouyang
 */

#include "TrackingApplication.h"

TrackingApplication::TrackingApplication() {
    this->cursorController = new CursorController;
    this->lastPos = new POINT;
    this->currentPos = new POINT;

    this->lastPos->x = -1;
    this->currentPos->y = -1;
    this->lastFist = false;
    this->redRect = 0;
}

TrackingApplication::~TrackingApplication() {
    delete this->cursorController;
    delete this->lastPos;
    delete this->currentPos;
}

void TrackingApplication::run() {
    if (!this->fist_cascade.load("res/fist.xml")) {
        cout << "load fist file failed." << endl;
        return;
    }
    if (!this->palm_cascade.load("res/rpalm.xml")) {
        cout << "load palm file failed." << endl;
        return;
    }

    this->capture.open(0);
    if (!this->capture.isOpened()) {
        cout << "open the camera failed." << endl;
        return;
    }

    this->capture >> this->frame;
    this->roi = selectROI("HCI Proj Tracking", this->frame);
    int frame_width = this->frame.cols;
    int frame_height = this->frame.rows;
    this->cursorController->setFrameSize(frame_width, frame_height);

    if (this->roi.width == 0 || this->roi.height == 0) {
        return;
    }
    this->currentPos->x = this->roi.x + 0.5 * this->roi.width;
    this->currentPos->y = this->roi.y + 0.5 * this->roi.height;
    cursorController->setPos(cursorController->k * this->currentPos->x,
                             cursorController->b * this->currentPos->y);

    this->tracker = TrackerCSRT::create();
    this->tracker->init(this->frame, this->roi);

    while (true) {
        this->capture >> this->frame;
        if (this->frame.empty()) {
            break;
        }

        this->tracker->update(this->frame, this->roi);

        // move the cursor
        this->lastPos->x = this->currentPos->x;
        this->lastPos->y = this->currentPos->y;

        this->currentPos->x = this->roi.x + 0.5 * this->roi.width;
        this->currentPos->y = this->roi.y + 0.5 * this->roi.height;

        // detect the fist
        vector<Rect> fist;
        Mat frame_gray;
        cvtColor(this->frame, frame_gray, CV_BGR2GRAY);
        equalizeHist(frame_gray, frame_gray);

        this->fist_cascade.detectMultiScale(frame_gray, fist, 1.1,
                                            2, 0 | CASCADE_SCALE_IMAGE,
                                            Size(30, 39));

        // detect the palm
        vector<Rect> palm;
        this->palm_cascade.detectMultiScale(frame_gray, palm, 1.1,
                                            2, 0 | CASCADE_SCALE_IMAGE,
                                            Size(30, 39));


        if (!fist.empty() && palm.empty()) {
            if (!this->lastFist) {
                this->redRect = 3;
//                CursorController::leftDoubleClick();
                CursorController::leftClick();
            }
            this->lastFist = true;
        } else {
            if (this->lastPos->x != -1) {
                this->cursorController->move(this->lastPos->x - this->currentPos->x,
                                             this->currentPos->y - this->lastPos->y,
                                             3);
            }
            this->lastFist = false;
        }

        // draw this frame
        if (this->redRect) {
            rectangle(this->frame, this->roi,
                      Scalar(0, 0, 255), 2, 1);
            this->redRect--;
        } else {
            rectangle(this->frame, this->roi,
                      Scalar(0, 255, 0), 2, 1);
        }
        imshow("HCI Proj Tracking", this->frame);

        if (waitKey(1) == 27) {
            break;
        }
    }
}
