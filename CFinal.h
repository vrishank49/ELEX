#pragma once
#include "CBase4618.h"
#include "CCamera.h"
#include "CControlPi.h"
#include "pigpio.h"
#include "CCamera.h"

#define PWM_A 22
#define PWM_B 18
#define A_IN_1 17
#define A_IN_2 27
#define B_IN_1 24
#define B_IN_2 23
#define STANDBY 25

class CFinal : public CBase4618
{
private:

public:

    cv::Mat _motorframe;
    int minA1, minA2, kb_ctrl;

    CFinal();
    ~CFinal();

    void update();
    void draw();
};

