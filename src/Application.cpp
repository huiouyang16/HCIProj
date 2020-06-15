/**
 * author: Hui Ouyang
 */

#include "Application.h"

Application::Application() {
    this->lastPos = new POINT;
    this->cursorController = new CursorController();
    this->lastPos->x = -1;
    this->lastPos->y = -1;
    this->currentPos = new POINT;
    this->currentPos->x = -1;
    this->currentPos-> y = -1;
}

Application::~Application() {
    delete this->cursorController;
    delete this->lastPos;
    delete this->currentPos;
}

void Application::run() {
    this->capture.open(0);
    if (!fist_cascade.load("res/fist.xml")) {
        cout << "load fist file failed." << endl;
        return;
    }

    if (this->capture.isOpened()) {
        this->capture >> this->frame;
        if (!this->frame.empty()) {
            int frame_width = this->frame.cols;
            int frame_height = this->frame.rows;
            this->cursorController->setFrameSize(frame_width, frame_height);
        }else{
            return;
        }
    }else{
        return;
    }

    if (!palm_cascade.load("res/rpalm.xml")) {
        cout << "load palm xml file failed." << endl;
        return;
    }
    while (true) {
        if (this->capture.isOpened()) {
            this->capture >> this->frame;

            if (!this->frame.empty()) {
                this->detectAndDisplay();
            }

            moveCursor();
            detectAndClick();

            waitKey(30);
        } else {
            cout << "Open the camera failed." << endl;
            break;
        }
    }
    this->capture.release();
}

void Application::moveCursor(){
    if(isPalm){
        cursorController->setPosScale(lastPos->x, lastPos->y, currentPos->x, currentPos->y);
    }
}

void Application::detectAndClick(){
    if(last_isPalm && isFist){
//        cursorController->leftClick();
        cursorController->leftDoubleClick();
    }
}

void Application::detectAndDisplay() {

    vector<Rect> palm;
    vector<Rect> fist;

    Mat frame_gray;
    cvtColor(this->frame, frame_gray, CV_BGR2GRAY);
    equalizeHist(frame_gray, frame_gray);

    palm_cascade.detectMultiScale(frame_gray, palm, 1.1,
                                  2, 0 | CASCADE_SCALE_IMAGE,
                                  Size(30, 30));
    fist_cascade.detectMultiScale(frame_gray, fist, 1.1,
                                  2, 0 | CASCADE_SCALE_IMAGE,
                                  Size(30, 30));

    if(!palm.empty()){
        last_isPalm = isPalm;
        isPalm = true;
        this->lastPos->x = this->currentPos->x;
        this->lastPos->y = this->currentPos->y;
        this->currentPos->x = palm[0].x;
        this->currentPos->y = palm[0].y;
    }else{
        isPalm = false;
    }
    if(!fist.empty()){
        last_isFist = isFist;
        isFist = true;
        this->lastPos->x = this->currentPos->x;
        this->lastPos->y = this->currentPos->y;
        this->currentPos->x = fist[0].x;
        this->currentPos->y = fist[0].y;
    }else{
        isFist = false;
    }

    for (auto &i : palm) {
        Point center(i.x + i.width * 0.5, i.y + i.height * 0.5);
        ellipse(this->frame, center, Size(i.width * 0.5, i.height * 0.5), 0, 0,
                360, Scalar(255, 0, 255), 4, 8, 0);
    }

    for (auto &i : fist) {
        Point center(i.x + i.width * 0.5, i.y + i.height * 0.5);
        ellipse(this->frame, center, Size(i.width * 0.5, i.height * 0.5), 0, 0,
                360, Scalar(255, 0, 0), 4, 8, 0);
    }

    imshow("test", this->frame);
}