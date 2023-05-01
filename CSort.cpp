#include "CSort.h"
#include "cvui.h"
#include <opencv2/opencv.hpp>
#include "pigpio.h"

CSort::CSort() {
    if (gpioInitialise() < 0) {}
    //cvui::init(MASK_TITLE);
    //cvui::init(__MASK_TITLE_GREEN);
    cvui::init(TRACKBAR_TITLE);
    //cvui::init(_TRACKBAR_TITLE_GREEN);

    gpioSetMode(LED1_PIN, PI_OUTPUT);
    gpioWrite(LED1_PIN, 1);
    //gpioSetMode(SERVO_1, PI_OUTPUT);
    //gpioSetMode(SERVO_2, PI_OUTPUT);

    minrange = {90, 90, 50};
    maxrange = {120, 255, 255};
    minrangegreen = {54.3, 45.7, 58.0};
    maxrangegreen = {96.8,255,255};

    _trackbarframe = cv::Mat::zeros(400, 600, CV_8UC3);
    //__trackbarframegreen = cv::Mat::zeros(400, 600, CV_8UC3);

    gpioServo(SERVO_1, 700);
    gpioServo(SERVO_2, 700);
}

void CSort::cleanframe(cv::Mat &frame) {
    for (int i = 0; i <= 3; i++) {
        cv::dilate(frame, frame, cv::Mat());
    }

    for (int i = 0; i <= 3; i++) {
        cv::erode(frame, frame, cv::Mat());
    }


}

void CSort::update() {
    _camera.get_camera(_camera.frame, _camera._hsvframe);
    cv::inRange(_camera._hsvframe, minrange, maxrange, _maskframe); // this for blue
    cv::inRange(_camera._hsvframe, minrangegreen, maxrangegreen, _maskframegreen);
    //::inRange(_camera._hsvframe, minrangenone, maxrangenone, _maskframe);

    // clean up inRange with dilate and erode

    cleanframe(_maskframe);
    cleanframe(_maskframegreen);

    _mean = cv::mean(_maskframe);
    _meangreen = cv::mean(_maskframegreen);

    if (_mean[0] > 13) {
        std::cout << "blue" << std::endl;
        gpioServo(SERVO_1, SERVO_OPEN_POS);
        cv::waitKey(1);
        gpioServo(SERVO_2, 2200);
        cv::waitKey(1000);
        gpioServo(SERVO_1, SERVO_BLOCK_POS);
        cv::waitKey(1);
        gpioServo(SERVO_2, 1000);
    }
    else if (_meangreen[0] > 13) {
        std::cout << "green" << std::endl;
        gpioServo(SERVO_1, SERVO_OPEN_POS);
        cv::waitKey(1);
        gpioServo(SERVO_2, 1050);
        cv::waitKey(1000);
        gpioServo(SERVO_1, SERVO_BLOCK_POS);
        cv::waitKey(1);
        gpioServo(SERVO_2, 1000);
    }
    else {
        std::cout << "none" << std::endl;
        gpioServo(SERVO_1, SERVO_BLOCK_POS);
        cv::waitKey(1);
        gpioServo(SERVO_2, 1000);
        //cv::waitKey(20);

    }


    //std::cout << _meangreen[0] << std::endl;
}

void CSort::draw() {
    _trackbarframe = cv::Mat::zeros(400, 600, CV_8UC3);
    //__trackbarframegreen = cv::Mat::zeros(400, 600, CV_8UC3);

    cvui::trackbar(_trackbarframe, 10, 60, 500, &minrange[0], (double)1, double(255));
    cvui::trackbar(_trackbarframe, 10, 120, 500, &maxrange[0], (double)1, double(255));
    cvui::trackbar(_trackbarframe, 10, 180, 500, &minrange[1], (double)1, double(255));
    cvui::trackbar(_trackbarframe, 10, 240, 500, &maxrange[1], (double)1, double(255));
    cvui::trackbar(_trackbarframe, 10, 300, 500, &minrange[2], (double)1, double(255));
    cvui::trackbar(_trackbarframe, 10, 360, 500, &maxrange[2], (double)1, double(255));

    //cvui::trackbar(__trackbarframegreen, 10, 60, 500, &minrangegreen[0], (double)1, double(255));
    //cvui::trackbar(__trackbarframegreen, 10, 120, 500, &maxrangegreen[0], (double)1, double(255));
    //cvui::trackbar(__trackbarframegreen, 10, 180, 500, &minrangegreen[1], (double)1, double(255));
    //cvui::trackbar(__trackbarframegreen, 10, 240, 500, &maxrangegreen[1], (double)1, double(255));
    //cvui::trackbar(__trackbarframegreen, 10, 300, 500, &minrangegreen[2], (double)1, double(255));
    //cvui::trackbar(__trackbarframegreen, 10, 360, 500, &maxrangegreen[2], (double)1, double(255));

    cv::imshow(CAMERA_TITLE, _camera.frame);
    //cv::imshow(HSV_TITLE, _camera._hsvframe);
    cv::imshow(MASK_TITLE, _maskframe);
    cv::imshow(_MASK_TITLE_GREEN, _maskframegreen);
    cv::imshow(TRACKBAR_TITLE, _trackbarframe);
    //cv::imshow(_TRACKBAR_TITLE_GREEN, __trackbarframegreen);

    // display image
}
