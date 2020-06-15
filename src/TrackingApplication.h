/**
 * author: Hui Ouyang
 */
#ifndef HCIPROJ_TRACKINGAPPLICATION_H
#define HCIPROJ_TRACKINGAPPLICATION_H

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

using namespace std;
using namespace cv;

class TrackingApplication {
private:
    VideoCapture capture;
    Mat frame;
    Rect2d roi;
    POINT *lastPos;
    POINT *currentPos;
    CursorController *cursorController;
    Ptr<Tracker> tracker;
    CascadeClassifier fist_cascade;
    bool lastFist;
    int redRect;

public:
    TrackingApplication();

    ~TrackingApplication();

    void run();

};

#endif //HCIPROJ_TRACKINGAPPLICATION_H
