#include "pigpio.h"
#include <iostream>

#define AIN1 17
#define AIN2 27
#define PWMA 22
#define PWMB 18
#define BIN2 23
#define BIN1 24
#define STANDBY 25

#define PWM_FREQ 1000
#define PWM_RANGE 512
#define PWM_DUTYCYCLE 255

#define SHOOT_SERVO 26

class CMotor
{
public:
    CMotor();
    ~CMotor();
    void set_pwm_left(int val);
    void set_pwm_right(int val);
    int get_pwm_left();
    int get_pwm_right();

    void stop();
    void forward(float time);
    void backward(float time);
    void left(float time);
    void right(float time);
    void gpio_init(); // to set GPIO PINMAP cleanly
};
