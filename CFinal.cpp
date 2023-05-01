#include "CFinal.h"
#include "cvui.h"
#include <opencv2/opencv.hpp>

CFinal::CFinal()
{
    if (gpioInitialise() < 0) {};

    cvui::init("MOTOR FUNCTIONS");

    _motorframe = cv::Mat::zeros(400, 600, CV_8UC3);

    gpioSetPWMfrequency(PWM_A, 1000);
    gpioSetPWMrange(PWM_A, 255);
    gpioPWM(PWM_A, 127);

    //setting PWMB
    gpioSetPWMfrequency(PWM_B, 1000);
    gpioSetPWMrange(PWM_B, 255);
    gpioPWM(PWM_B, 127);

    gpioSetMode(PWM_A, PI_OUTPUT);
    gpioSetMode(PWM_B, PI_OUTPUT);
    gpioSetMode(A_IN_1, PI_OUTPUT);
    gpioSetMode(A_IN_2, PI_OUTPUT);
    gpioSetMode(B_IN_1, PI_OUTPUT);
    gpioSetMode(B_IN_2, PI_OUTPUT);
    gpioSetMode(STANDBY, PI_OUTPUT);

    kb_ctrl = 2048;

}

CFinal::~CFinal()
{
    gpioTerminate();
}

void CFinal::update() {
    //std::cin >> kb_ctrl;
    kb_ctrl = cv::waitKey(10);
}

void CFinal::draw() {
    //_motorframe = cv::Mat::zeros(400, 600, CV_8UC3);

    switch (kb_ctrl)
        {
        case 5://53
            std::cout << "go forward" << std::endl;
            gpioWrite(STANDBY, 1); //activate h bridge
            gpioWrite(A_IN_1, 1); //move wheel A
            gpioWrite(A_IN_2, 0); //move wheel A
            gpioWrite(B_IN_1, 1); //move wheel B
            gpioWrite(B_IN_2, 0); //move wheel B
            break;
        case 1://49
            std::cout << "turn left" << std::endl;
            gpioWrite(STANDBY, 1); //activate h bridge
            gpioWrite(A_IN_1, 1); //move wheel A
            gpioWrite(A_IN_2, 0); //move wheel A
            gpioWrite(B_IN_1, 0); //move wheel B
            gpioWrite(B_IN_2, 1); //move wheel B
            break;
        case 2://50
            std::cout << "go backward" << std::endl;
            gpioWrite(STANDBY, 1); //activate h bridge
            gpioWrite(A_IN_1, 0); //move wheel A
            gpioWrite(A_IN_2, 1); //move wheel A
            gpioWrite(B_IN_1, 0); //move wheel B
            gpioWrite(B_IN_2, 1); //move wheel B
            break;
        case 3://51
            std::cout << "turn right" << std::endl;
            gpioWrite(STANDBY, 1); //activate h bridge
            gpioWrite(A_IN_1, 0); //move wheel A
            gpioWrite(A_IN_2, 1); //move wheel A
            gpioWrite(B_IN_1, 1); //move wheel B
            gpioWrite(B_IN_2, 0); //move wheel B
            break;
        case 0://48
            std::cout << "stop" << std::endl;
            gpioWrite(STANDBY, 0); //deactivate h bridge
            gpioWrite(A_IN_1, 0); //move wheel A
            gpioWrite(A_IN_2, 0); //move wheel A
            gpioWrite(B_IN_1, 0); //move wheel B
            gpioWrite(B_IN_2, 0); //move wheel B
            break;
        default:
            std::cout << "no valid commands" << std::endl;
            break;
        }
    //cvui::trackbar(_motorframe, 10, 60, 500, &minA1, (int)0, int(1));
    //cvui::trackbar(_motorframe, 10, 120, 500, &minA2, (int)0, int(1));

}
