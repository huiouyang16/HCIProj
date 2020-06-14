#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgproc/types_c.h>
#include <opencv2/tracking.hpp>
#include <opencv2/tracking/tracker.hpp>
#include <iostream>
#include "CursorController.h"

using namespace cv;
using namespace std;

void detectAndDisplay(Mat frame);

int main() {

    /**
     * example of the class CursorController
     */
//    auto *cc = new CursorController;
//    cc->setPos(1808, 12);
//    cc->leftClick();
//    cc->setPos(1717, 860);
//    Sleep(1000);
//    cc->leftDoubleClick();

    cout << "OpenCV Version: " << CV_VERSION << endl;

    VideoCapture capture;
    Mat frame;

    Rect2d roi;
    capture.open(0);

    while (true) {
        if (capture.isOpened()) {
            capture >> frame;

            if (!frame.empty()) {
                detectAndDisplay(frame);
            } else {
                cout << "this frame is empty" << endl;
            }

            waitKey(30);
        } else {
            cout << "Camera cannot open!" << endl;
            break;
        }
    }

    capture.release();
    return 0;
}

void detectAndDisplay(Mat frame) {
    CascadeClassifier palm_cascade;

    if (!palm_cascade.load("res/palm.xml")) {
        cout << "load palm xml file filed." << endl;
        return;
    }

    vector<Rect> palm;
    Mat frame_gray;
    cvtColor(frame, frame_gray, CV_BGR2GRAY);
    equalizeHist(frame_gray, frame_gray);

    palm_cascade.detectMultiScale(frame_gray, palm, 1.1,
                                  2, 0 | CASCADE_SCALE_IMAGE,
                                  Size(30, 30));

    for (auto &i : palm) {
        Point center(i.x + i.width * 0.5, i.y + i.height * 0.5);
        ellipse(frame, center, Size(i.width * 0.5, i.height * 0.5), 0, 0,
                360, Scalar(255, 0, 255), 4, 8, 0);

    }

    imshow("window_name", frame);
}
