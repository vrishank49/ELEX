//#include "CServer.h"
#include "CMotor.h"
#include "CGuidance.h"
#include "CBase4618.h"

#include "cvui.h"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <thread>
#include <mutex>

#define HYDRACAM_TITLE "HYDRA CAM (.Y.)"

class CCar
{
private:
    //CServer _server;
    CMotor _motors;
    CGuidance _guidance;
    cv::Mat hydraframe;

    std::mutex _mutex;

    bool running;

    static void serverthrd(CCar *ptr);
    static void imagethrd(CCar *ptr);

public:
    CCar();
    ~CCar();

    float time;

    //std::thread drivethread();
    //std::thread imagethread(cv::Mat &hydraframe);

    char kb_ctrl;

    void drive();

    void motorcontrol();
    void imageprocess();
    void imagedisplay();
};
