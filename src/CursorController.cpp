/**
 * author: Hui Ouyang
 */

#include "CursorController.h"
#include <iostream>

void CursorController::refreshPos() {
    GetCursorPos(&this->p);
}

int CursorController::getXPos() {
    this->refreshPos();
    return this->p.x;
}

int CursorController::getYPos() {
    this->refreshPos();
    return this->p.y;
}

POINT CursorController::getPos() {
    this->refreshPos();
    POINT res;
    res.x = this->p.x;
    res.y = this->p.y;
    return res;
}

void CursorController::setPosScale(int lastX, int lastY, int currentX, int currentY) {

    int STEDY_THRESHOLD = 12;
    double BOOST_RATIO = 0.7;

    int odx = lastX - currentX;
    int ody = currentY - lastY;

    std::cout << odx << "        " << ody;

    odx = abs(odx) < STEDY_THRESHOLD ? 0 : odx;
    ody = abs(ody) < STEDY_THRESHOLD ? 0 : ody;


    this->refreshPos();
    int posX = this->p.x + BOOST_RATIO * k * odx;
    int posY = this->p.y + BOOST_RATIO * b * ody;
    setPos(posX, posY);

    std::cout << "      |      " << posX << "        " << posY << std::endl;

}

void CursorController::setPos(int X, int Y) {
    SetCursorPos(X, Y);
}

void CursorController::move(int difX, int difY, int rate) {
    this->refreshPos();
    for (int i = 1; i <= rate; ++i) {
        setPos(this->p.x + difX * i, this->p.y + difY * i);
    }
}

void CursorController::keepLeftClick() {
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
}

void CursorController::keepRightClick() {
    mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
}

void CursorController::releaseLeftClick() {
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
}

void CursorController::releaseRightClick() {
    mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
}

void CursorController::leftClick() {
    keepLeftClick();
    releaseLeftClick();
}

void CursorController::leftDoubleClick() {
    leftClick();
    leftClick();
}

void CursorController::rightClick() {
    keepRightClick();
    releaseRightClick();
}

void CursorController::setFrameSize(int fw, int fh) {
    sw = GetSystemMetrics(0);
    sh = GetSystemMetrics(1);
    k = sw * 1.0 / fw;
    b = sh * 1.0 / fh;
}

