/**
 * author: Hui Ouyang
 */

#ifndef HCIPROJ_CURSORCONTROLLER_H
#define HCIPROJ_CURSORCONTROLLER_H

#include <windows.h>

/**
 * this is a Controller class used to control the cursor in windows
 */
class CursorController {
private:
    POINT p;

    double k; // width ratio
    double b; // height ratio

    int sw; // screen width
    int sh; // screen height

    void refreshPos();

public:
    /**
     * this method is used to get the current X position of the cursor
     * @return the X position of the cursor
     */
    int getXPos();

    /**
     * this method is used to get the current Y position of the cursor
     * @return the Y position of the cursor
     */
    int getYPos();

    /**
     * this method is used to get the current X and Y position of the cursor
     * @return the POINT instance with the X and Y position of the cursor
     */
    POINT getPos();

    /**
     * this method is used to set the position of the curosr
     * @param X the X position of the cursor
     * @param Y the Y position of the cursor
     */
    static void setPos(int X, int Y);

    /**
     * this method is used to move the cursor
     * @param difX the moved distance of X position
     * @param difY the moved distance of Y position
     */
    void move(int difX, int difY);

    /**
     * this method can keep the left click
     */
    static void keepLeftClick();

    /**
     * this method can keep the right click
     */
    static void keepRightClick();

    /**
     * this method can release the left click
     */
    static void releaseLeftClick();

    /**
     * this method can release the right click
     */
    static void releaseRightClick();

    /**
     * this method can click left single time
     */
    static void leftClick();

    /**
     * this method can click the left twice
     */
    static void leftDoubleClick();

    /**
     * this method can click right single time
     */
    void rightClick();

    void setFrameSize(int fw, int fh);

    void setPosScale(int lastX, int lastY, int currentX, int currentY);

};

#endif //HCIPROJ_CURSORCONTROLLER_H
