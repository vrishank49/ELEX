#include <opencv2/opencv.hpp>
#include <opencv2/aruco.hpp>
#include "cvui.h"

//#include "raspicam_cv.h"

class CGuidance
{
private:
    cv::Mat _frame;
    cv::VideoCapture cap;

public:
    std::string pipeline;

    int capture_width, capture_height, framerate, display_width, display_height;
    std::string gstreamer_pipeline(int capture_width, int capture_height, int framerate, int display_width, int display_height);

    int dictionaryId;
    float markerLength;
    cv::Ptr<cv::aruco::DetectorParameters> detectorParams;
    cv::Ptr<cv::aruco::Dictionary> dictionary;
    std::vector<int> ids;
    std::vector<std::vector<cv::Point2f>> corners;
    std::vector<cv::Vec3d> rvecs, tvecs;

    CGuidance();
    ~CGuidance();
    void update();
    void detectMarkers(cv::Mat &_frame);
    void get_im(cv::Mat &_frame);
};
