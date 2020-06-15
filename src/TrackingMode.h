//
// Created by ASUS on 2020/6/14.
//

#ifndef HCIPROJ_TRACKINGMODE_H
#define HCIPROJ_TRACKINGMODE_H

#include <opencv2/opencv.hpp>
#include <opencv2/video.hpp>
#include <opencv2/tracking.hpp>
#include <opencv2/tracking/tracker.hpp>
#include <iostream>

using namespace cv;

Mat firstFrame;
Point previousPoint, currentPoint;
Rect2d bbox;
void draw_rectangle(int event, int x, int y, int flags, void*)
{
    if (event == EVENT_LBUTTONDOWN)
    {
        previousPoint = Point(x, y);
    }
    else if (event == EVENT_MOUSEMOVE && (flags&EVENT_FLAG_LBUTTON))
    {
        Mat tmp;
        firstFrame.copyTo(tmp);
        currentPoint = Point(x, y);
        rectangle(tmp, previousPoint, currentPoint, Scalar(0, 255, 0, 0), 1, 8, 0);
        imshow("output", tmp);
    }
    else if (event == EVENT_LBUTTONUP)
    {
        bbox.x = previousPoint.x;
        bbox.y = previousPoint.y;
        bbox.width = abs(previousPoint.x-currentPoint.x);
        bbox.height =  abs(previousPoint.y-currentPoint.y);
    }
    else if (event == EVENT_RBUTTONUP)
    {
        destroyWindow("output");
    }
}


void run()
{
    VideoCapture capture;
    Mat frame;
    frame = capture.open(0);
    if(!capture.isOpened())
    {
        printf("can not open ...\n");
        return;
    }
    //获取视频的第一帧,并框选目标
    capture.read(firstFrame);
    if(!firstFrame.empty())
    {
        namedWindow("output", WINDOW_AUTOSIZE);
        imshow("output", firstFrame);
        setMouseCallback("output", draw_rectangle, 0);
        waitKey();
    }
    std::cout << "captured." << std::endl;
    //使用TrackerMIL跟踪
    Ptr<TrackerMIL> tracker= TrackerMIL::create();
    //Ptr<TrackerTLD> tracker= TrackerTLD::create();
    //Ptr<TrackerKCF> tracker = TrackerKCF::create();
    //Ptr<TrackerMedianFlow> tracker = TrackerMedianFlow::create();
    //Ptr<TrackerBoosting> tracker= TrackerBoosting::create();
    capture.read(frame);
    if(!tracker->init(frame,bbox)){
        std::cout << "Cannot init tracker. exit" << std::endl;
    }
    namedWindow("output", WINDOW_AUTOSIZE);
    while (capture.read(frame))
    {
        tracker->update(frame,bbox);
        rectangle(frame,bbox, Scalar(255, 0, 0), 2, 1);
        imshow("output", frame);
        if(waitKey(20)=='q')
            return;
    }
    capture.release();
    destroyWindow("output");
}





#endif //HCIPROJ_TRACKINGMODE_H
