# HCI [C/C++ programming course project]

This is a project of the course C/C++ programming.



There is two mode in our program.

**Tracking mode**: use the Tracker and CascadeClassifier from OpenCV, it is stable, but the user should specify the object (hand).

**Detection mode**: only use the CascadeClassifier from OpenCV, it is not very stable, but the user need not to specify the object (hand).



**Enter the program:**

+ a message box will ask you whether you want to use the Detection mode. (or Tracking mode in default)

**Enter the Tracking mode:**

+ specify the object (hand) first, and then press the **enter** or **space** in your keyboard
+ then, the tracker will track the object, the movement of the object will move the cursor
+ also, if you change your hand to fist, the cursor will double click

**Enter the Detection mode:**

+ the program will auto detect your hand (in palm or in fist)
+ when your hand in palm, the cursor will keep click
+ when your hand in fist, the cursor will release click
+ when your hand move, the cursor also move



the demo in the demo-videos directory



## Project Settings

+ OpenCV 4.2.0
+ opencv_contrib 4.2.0
+ MinGW-w64 x86_64 8.1.0
+ CLion
+ CMake 3.15.3

Project developed and tested under CLion and mingw64-x86_64-8.1.0.



## Getting Started

#### Clone this project

```
git clone https://github.com/Hui-Ouyang16/HCIProj.git
```

#### Setting OpenCV DIR in CMakeLists.txt

Before doing this, you should install OpenCV and opencv_contrib in your computer (yell, we all know you can do it by yourselves)

If you do not know how to do this, you can refer [How-to-install-OpenCV-in-windows-10-using-MinGW.pdf](https://github.com/Hui-Ouyang16/HCIProj/blob/master/docs/How-to-install-OpenCV-in-windows-10-using-MinGW.pdf) [may sometimes you should download the file to read it]

```cmake
# change to your OpenCV path
set(OpenCV_DIR "E:/opencv-mingw/build/install")
# change to your OpenCV path
set(OpenCV_INCLUDE_DIRS "E:/opencv-mingw/opencv/include")

# change to your OpenCV path
include_directories(
        ${PROJECT_SOURCE_DIR}
        "E:/opencv-mingw/opencv/include"
)
```

#### Setting the Toolchains and Working Directory in CLion

Setting the Toolchains: use MinGW

Setting the Working Directory: use the root of the project file

Setting the Environment variables: use the bin directory of your OpenCV install

#### Enjoy the program



## Project Requirements

**Controlling your computer remotely by hands**

At present, the COVID-19 is wantonly propagated in the world, and it has a major negative impact on daily life in all countries. In particular, it is pointed out that the facilities that humans often use, including elevators, computers, mobile phones, medical instruments and screens, generally consist of plastics and stainless steels. The recent research clearly shows that the virus can survive for 2-3 days on these surfaces, which is a very worrying conclusion. When people use these devices, the current inevitable way is to directly touch the screen and buttons. There is no doubt that the chance of spreading coronavirus is greatly increased. Therefore, designing a new non-contact interactive system is particularly important and critical. To this end, this project is going to design a non-contact interactive system based on the OpenCV library. This system will use an ordinary camera to detect the movement trajectory of items (hands) in the field of view and simply recognize the meaning expressed by the trajectory, such as circle, rectangle or triangle etc. These signals composed of trajectory and motion meaning can be transferred to control computers. An example can be found in the website: https://www.youtube.com/watch?v=_pM_jOOnHog&t=6s

1)   It supports to read images from a camera and then store the image, using APIs provided by OpenCV.

2)   It supports to locate an object (by default, the hand is selected as the object), which is specified by users in the image. The functions of object detection can be implemented by students (you) or can be invoked from APIs of OpenCV. The location in the image space is generally represented by four numbers for a **rectangle** (top-left corner and down-right corner), which contains the object.

3)   It supports to track the target which detected in the above step. The trace of the object in the image space is represented by a set of points, which are the centers of the rectangles. The trace of moving objects should be recorded and analyzed.

4)   It supports to identify some specific meaning of trajectory, such as circle, rectangle or triangle etc..

5)   Using the above-mentioned detected trajectories (sets of points) and the identified trajectory meaning, students are required to further implement simple controlling functions, such as cursor movement, click or double clicks, etc. to show the validation of the above implemented operations.