/**
 * author: Hui Ouyang
 */

#include "TrackingApplication.h"

TrackingApplication::TrackingApplication() {
    this->cursorController = new CursorController;
}

TrackingApplication::~TrackingApplication() {
    delete cursorController;
}

void TrackingApplication::run() {
    this->capture.open(0);

    this->capture >> this->frame;
    roi = selectROI("HCI Proj Tracking", frame);

    if (roi.width == 0 || roi.height == 0) {
        return;
    }

    tracker = TrackerKCF::create();
    tracker->init(frame, roi);

    while (true) {
        this->capture >> this->frame;
        if (this->frame.empty()) {
            break;
        }

        tracker->update(frame, roi);
        rectangle(frame, roi, Scalar(255, 0, 0), 2, 1);
        imshow("HCI Proj Tracking", frame);

        if (waitKey(1) == 27) {
            break;
        }
    }
}
