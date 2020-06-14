/**
 * author: Hui Ouyang
 */

#include "Application.h"

Application::Application() {
    this->lastPos = new POINT;
    this->cursorController = new CursorController;
    this->lastPos->x = -1;
    this->lastPos->y = -1;
}

Application::~Application() {
    delete this->cursorController;
    delete this->lastPos;
}

void Application::run() {
    this->capture.open(0);
    while (true) {
        if (this->capture.isOpened()) {
            this->capture >> this->frame;

            if (!this->frame.empty()) {
                this->detectAndDisplay();
            }
            waitKey(30);
        } else {
            cout << "Open the camera failed." << endl;
            break;
        }
    }
    this->capture.release();
}

void Application::detectAndDisplay() {
    CascadeClassifier palm_cascade;

    if (!palm_cascade.load("res/aGest.xml")) {
        cout << "load palm xml file filed." << endl;
        return;
    }

    vector<Rect> palm;
    Mat frame_gray;
    cvtColor(this->frame, frame_gray, CV_BGR2GRAY);
    equalizeHist(frame_gray, frame_gray);

    palm_cascade.detectMultiScale(frame_gray, palm, 1.1,
                                  2, 0 | CASCADE_SCALE_IMAGE,
                                  Size(30, 30));

    for (auto &i : palm) {
        Point center(i.x + i.width * 0.5, i.y + i.height * 0.5);
        if (this->lastPos->x != -1) {
            this->cursorController->setPos(i.x, i.y);
        }
        this->lastPos->x = i.x;
        this->lastPos->y = i.y;

        ellipse(this->frame, center, Size(i.width * 0.5, i.height * 0.5), 0, 0,
                360, Scalar(255, 0, 255), 4, 8, 0);

    }

    imshow("HCI Proj", this->frame);
}