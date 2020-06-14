/**
 * author: Hui Ouyang
 */

#ifndef HCIPROJ_APPLICATION_H
#define HCIPROJ_APPLICATION_H

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

class Application {
private:
    VideoCapture capture;
    Mat frame;
    POINT *lastPos;
    POINT *currentPos;
    CursorController *cursorController;
    bool isFist = false;
    bool isPalm = false;
    bool last_isFist = false;
    bool last_isPalm = false;
    CascadeClassifier palm_cascade;
    CascadeClassifier fist_cascade;

public:
    Application();

    ~Application();

    void run();

    void detectAndDisplay();

    void detectAndClick();

    void moveCursor();
};

#endif //HCIPROJ_APPLICATION_H
