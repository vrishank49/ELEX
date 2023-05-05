#include "CGuidance.h"

std::string CGuidance::gstreamer_pipeline(int capture_width, int capture_height, int framerate, int display_width, int display_height) {
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

CGuidance::CGuidance()
{
    capture_width = 1280;
    capture_height = 720;
    framerate = 60;
    display_width = 640;
    display_height = 360;

    pipeline = gstreamer_pipeline(capture_width, capture_height, framerate, display_width, display_height);
    cap.open(pipeline, cv::CAP_GSTREAMER);

    dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_6X6_250);
    detectorParams = cv::aruco::DetectorParameters::create();
}

CGuidance::~CGuidance()
{
    cap.release();
}

void CGuidance::update()
{
    cap >> _frame;
    if (_frame.empty()) {
        std::cerr << "ERROR: Blank frame grabbed\n";
        exit(0);
    }
}

void CGuidance::detectMarkers()
{
      cv::Mat _frame;
      cap >> _frame;

      if (_frame.empty() == false)
      {
        cv::aruco::detectMarkers(_frame, dictionary, corners, ids);
        if (ids.size() > 0)
        {
          cv::aruco::drawDetectedMarkers(_frame, corners, ids);
        }
      }
}

void CGuidance::get_im(cv::Mat &_frame)
{
    cap.read(_frame);
}
