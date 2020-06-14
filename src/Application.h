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
    CursorController *cursorController;

public:
    Application();

    ~Application();

    void run();

    void detectAndDisplay();
};

#endif //HCIPROJ_APPLICATION_H
