/**
 * author: Hui Ouyang
 */

#include "CursorController.h"

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

void CursorController::setPos(int X, int Y) {
    SetCursorPos(X, Y);
}

void CursorController::move(int difX, int difY) {
    this->refreshPos();
    setPos(this->p.x + difX, this->p.y + difY);
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



