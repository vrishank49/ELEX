//#include "CServer.h"
#include "CMotor.h"
#include "CGuidance.h"
#include "CBase4618.h"
//#include "CCamera.h"
#include "pigpio.h"
#include "cvui.h"
#include <opencv2/opencv.hpp>

#define HYDRACAM_TITLE "HYDRA CAM (.Y.)"

class CCar
{
private:
    //CServer _server;
    CMotor _motors;
    CGuidance _guidance;
    cv::Mat hydraframe;

    bool running;

    static void serverthrd(CCar *ptr);
    static void imagethrd(CCar *ptr);

public:
    CCar();
    ~CCar();

    char kb_ctrl;

    void drive();
};
