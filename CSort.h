#pragma once
#include "CBase4618.h"
#include "CCamera.h"
#include "CControlPi.h"
#include "pigpio.h"

#define LED1_PIN 18

#define SERVO_BLOCK_POS 830
#define SERVO_OPEN_POS 1350

class CSort : public CBase4618
{
private:

public:

    CCamera _camera;

    cv::Scalar minrange;
    cv::Scalar maxrange;

    cv::Scalar minrangegreen;
    cv::Scalar maxrangegreen;

    cv::Scalar minrangenone;
    cv::Scalar maxrangenone;

    cv::Scalar _mean;
    cv::Scalar _meanblue;
    cv::Scalar _meangreen;
    cv::Scalar _meannone;

    cv::Mat _maskframe;
    cv::Mat _maskframegreen;
    cv::Mat _trackbarframe;
    cv::Mat __trackbarframegreen;

    CSort();
    ~CSort() {};

    void update();
    void draw();

    bool detect(cv::Mat _hsvframe);
    void cleanframe(cv::Mat &frame);
};
