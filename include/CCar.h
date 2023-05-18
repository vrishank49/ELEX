#include "CMotor.h"
#include "CGuidance.h"
#include "CBase4618.h"
#include "CSound.h"
#include "server.h"

#include "cvui.h"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <thread>
#include <mutex>

#define HYDRACAM_TITLE "HYDRA CAM (.Y.)"
#define PORT 5035

#define LED_1 6

class CCar
{
private:
    CServer _server;
    CMotor _motors;
    CGuidance _guidance;
    CSound _sound;

    std::mutex _mutex;

    bool running;

    static void serverthrd(CCar *ptr);
    static void imagethrd(CCar *ptr);

public:
    cv::Mat hydraframe;
    CCar();
    ~CCar();

    float time;
    std::vector<std::string> cmds;

    //std::thread drivethread();
    //std::thread imagethread(cv::Mat &hydraframe);

    char kb_ctrl;

    void drive();

    void serverinit(CServer* server);
    void motorcontrol(const std::string& key);
    void imageprocess();
    void imagedisplay();

    void servocontrol(int ms);
};
