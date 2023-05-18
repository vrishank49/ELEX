#include "CMotor.h"

CMotor::CMotor()
{
    gpio_init();
    //ctor
}

CMotor::~CMotor()
{
    //dtor
}

void CMotor::gpio_init() {

    if (gpioInitialise() < 0) // check to initialize GPIO
    {                         // GPIO initialize in CCar instead of CMotors incase I have other
                              // inputs for GPIO
        std::cerr << "Failed to initialize GPIO." << std::endl;
    }

    gpioSetMode(AIN1, PI_OUTPUT); //AIN1
    gpioSetMode(AIN2, PI_OUTPUT); //AIN2
    gpioSetMode(PWMA, PI_OUTPUT); //PWMA
    gpioSetMode(PWMB, PI_OUTPUT); //PWMB
    gpioSetMode(BIN2, PI_OUTPUT); //BIN2
    gpioSetMode(BIN1, PI_OUTPUT); //BIN1
    gpioSetMode(STANDBY, PI_OUTPUT); //standby (activates|deactivates h bridge)

    gpioSetMode(SHOOT_SERVO, PI_OUTPUT);

        // setting PWMA default
    gpioSetPWMfrequency(PWMA, PWM_FREQ);
    gpioSetPWMrange(PWMA, PWM_RANGE);
    gpioPWM(PWMA, PWM_DUTYCYCLE);

        //setting PWMB default
    gpioSetPWMfrequency(PWMB, PWM_FREQ);
    gpioSetPWMrange(PWMB, PWM_RANGE);
    gpioPWM(PWMB, PWM_DUTYCYCLE);
}

void CMotor::stop() {
            gpioWrite(STANDBY, 0); //deactivate h bridge
            gpioWrite(AIN1, 0); //move wheel A
            gpioWrite(AIN1, 0); //move wheel A
            gpioWrite(BIN1, 0); //move wheel B
            gpioWrite(BIN2, 0); //move wheel B
}

void CMotor::forward(float time) {
            gpioWrite(STANDBY, 1); //activate h bridge
            gpioWrite(AIN1, 1); //move wheel A
            gpioWrite(AIN2, 0); //move wheel A
            gpioWrite(BIN1, 1); //move wheel B
            gpioWrite(BIN2, 0); //move wheel B
}

void CMotor::backward(float time) {
            gpioWrite(STANDBY, 1); //activate h bridge
            gpioWrite(AIN1, 0); //move wheel A
            gpioWrite(AIN2, 1); //move wheel A
            gpioWrite(BIN1, 0); //move wheel B
            gpioWrite(BIN2, 1); //move wheel B
}

void CMotor::left(float time) {
            gpioWrite(STANDBY, 1); //activate h bridge
            gpioWrite(AIN1, 1); //move wheel A
            gpioWrite(AIN2, 0); //move wheel A
            gpioWrite(BIN1, 0); //move wheel B
            gpioWrite(BIN2, 1); //move wheel B
}

void CMotor::right(float time) {
            gpioWrite(STANDBY, 1); //activate h bridge
            gpioWrite(AIN1, 0); //move wheel A
            gpioWrite(AIN2, 1); //move wheel A
            gpioWrite(BIN1, 1); //move wheel B
            gpioWrite(BIN2, 0); //move wheel B
}


