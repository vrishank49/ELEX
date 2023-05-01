// Code taken from: https://github.com/Qengineering/Libcamera-OpenCV-RPi-Bullseye-64OS/blob/main/main.cpp

// CCamera function returns a video input to CSort.


#pragma once
#include <string>
#include <vector>
#include "CBase4618.h"

#define CAMERA_TITLE "CCamera"
#define HSV_TITLE "HSV FEED"
#define MASK_TITLE "MASK FEED"
#define _MASK_TITLE_GREEN "MASK FEED GREEN"
#define TRACKBAR_TITLE "TRACKBARS"
#define _TRACKBAR_TITLE_GREEN "TRACKBARS GREEN"

class CCamera
{
private:

public:
    cv::Mat frame;
    cv::Mat _hsvframe;

    std::vector <double> minscalar;
    std::vector <double> maxscalar;

    std::string pipeline;
    cv::VideoCapture cap;

    int capture_width, capture_height, framerate, display_width, display_height;
    std::string gstreamer_pipeline(int capture_width, int capture_height, int framerate, int display_width, int display_height);
    CCamera();
    ~CCamera();
    void get_camera(cv::Mat &frame, cv::Mat &_hsvframe); // git code goes here
};
