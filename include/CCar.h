//#include "CServer.h"
#include "CMotor.h"
#include "CGuidance.h"
#include "CBase4618.h"
//#include "CCamera.h"
#include "pigpio.h"
#include "cvui.h"
#include <opencv2/opencv.hpp>
#include <thread>

#define HYDRACAM_TITLE "HYDRA CAM (.Y.)"

class CCar
{
private:
    //CServer _server;
    CMotor _motors;
    CGuidance _guidance;
    cv::Mat hydraframe;

    std::mutex hydra_mutex;

    bool running;

    static void serverthrd(CCar *ptr);
    static void imagethrd(CCar *ptr);

public:
    CCar();
    ~CCar();

    std::thread drivethread();
    std::thread imagethread(cv::Mat &hydraframe, std::mutex& frame_mutex);

    char kb_ctrl;

    void drive();
};
