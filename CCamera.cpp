#include "CCamera.h"
#include <opencv2/opencv.hpp>
#include "cvui.h"

std::string CCamera::gstreamer_pipeline(int capture_width, int capture_height, int framerate, int display_width, int display_height) {
    return
            " libcamerasrc ! video/x-raw, "
            " width=(int)" + std::to_string(capture_width) + ","
            " height=(int)" + std::to_string(capture_height) + ","
            " framerate=(fraction)" + std::to_string(framerate) +"/1 !"
            " videoconvert ! videoscale !"
            " video/x-raw,"
            " width=(int)" + std::to_string(display_width) + ","
            " height=(int)" + std::to_string(display_height) + " ! appsink";
}

CCamera::CCamera()
{
    capture_width = 640;
    capture_height = 480;
    framerate = 15;
    display_width = 640;
    display_height = 480;

    pipeline = gstreamer_pipeline(capture_width, capture_height, framerate,
                                  display_width, display_height);

    cap = cv::VideoCapture(pipeline, cv::CAP_GSTREAMER);

    cvui::init(CAMERA_TITLE);
    cvui::init(HSV_TITLE);


    //cv::namedWindow(CAMERA_TITLE, cv::WINDOW_AUTOSIZE);
    //cv::namedWindow(HSV_TITLE, cv::WINDOW_AUTOSIZE);
}

CCamera::~CCamera()
{
    cap.release();
}

void CCamera::get_camera(cv::Mat &frame, cv::Mat &_hsvframe) {
    cap.read(frame);
    cv::cvtColor(frame, _hsvframe, cv::COLOR_BGR2HSV);
}
