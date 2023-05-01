#include "CCamera.h"
#include "CBase4618.h"
#include <opencv2/opencv.hpp>

CCamera::CCamera()
{
    capture_width = 640;
    capture_height = 480;
    framerate = 15;
    display_width = 640;
    display_height = 480;

    pipeline = gstreamer_pipeline(capture_width, capture_height, framerate,
                                  display_width, display_height);

    cv::VideoCapture cap(pipeline, cv::CAP_GSTREAMER);
    cv::namedWindow("Camera", cv::WINDOW_AUTOSIZE);
}

CCamera::~CCamera()
{
    cap.release();
}

CCamera::update() {
    if(!cap.isOpened()) {
        std::cout << "Failed to open camera." << std::endl;
        return (-1);
        }

    if (!cap.read(frame)) {
            std::cout <<" Capture read error." << std::endl;
        }
}
