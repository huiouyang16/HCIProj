cmake_minimum_required(VERSION 3.15)
project(HCIProj)

set(CMAKE_CXX_STANDARD 20)
add_executable(HCIProj src/main.cpp src/CursorController.cpp src/CursorController.h)

# change to your OpenCV path
set(OpenCV_DIR "E:/opencv-mingw/build/install")
# change to your OpenCV path
set(OpenCV_INCLUDE_DIRS "E:/opencv-mingw/opencv/include")

find_package(OpenCV REQUIRED)

message(STATUS "OpenCV library status:")
message(STATUS " version: ${OpenCV_VERSION}")
message(STATUS " libraries: ${OpenCV_LIBS}")
message(STATUS " include path: ${OpenCV_INCLUDE_DIRS}")

# change to your OpenCV path
include_directories(
        ${PROJECT_SOURCE_DIR}
        "E:/opencv-mingw/opencv/include"
)

include_directories(${OpenCV_INCLUDE_DIRS})

target_link_libraries(HCIProj ${OpenCV_LIBS})