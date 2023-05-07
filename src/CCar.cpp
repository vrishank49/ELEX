#include "CCar.h"

CCar::CCar() {

    if (gpioInitialise() < 0) // check to initialize GPIO
    {
        std::cerr << "Failed to initialize GPIO." << std::endl;
    }

    kb_ctrl = 'x';

    gpioSetMode(AIN1, PI_OUTPUT); //AIN1
    gpioSetMode(AIN2, PI_OUTPUT); //AIN2
    gpioSetMode(PWMA, PI_OUTPUT); //PWMA
    gpioSetMode(PWMB, PI_OUTPUT); //PWMB
    gpioSetMode(BIN2, PI_OUTPUT); //BIN2
    gpioSetMode(BIN1, PI_OUTPUT); //BIN1
    gpioSetMode(STANDBY, PI_OUTPUT); //standby (activates|deactivates h bridge)

    // setting PWMA
    gpioSetPWMfrequency(PWMA, PWM_FREQ);
    gpioSetPWMrange(PWMA, PWM_RANGE);
    gpioPWM(PWMA, PWM_DUTYCYCLE);

    //setting PWMB
    gpioSetPWMfrequency(PWMB, PWM_FREQ);
    gpioSetPWMrange(PWMB, PWM_RANGE);
    gpioPWM(PWMB, PWM_DUTYCYCLE);

    cv::namedWindow(HYDRACAM_TITLE, cv::WINDOW_NORMAL); // Create window with normal dimensions
    cv::resizeWindow(HYDRACAM_TITLE, 640, 480); // Set window size
    cvui::init(HYDRACAM_TITLE);

    running = true;
}

CCar::~CCar() {
    gpioTerminate();
}

void CCar::drive() {

while(running) // John's old motor control code
    {

    _guidance.get_im(hydraframe);
    _guidance.detectMarkers(hydraframe);
    cv::imshow(HYDRACAM_TITLE, hydraframe);

    kb_ctrl = cv::waitKey(10);
    //std::cin >> kb_ctrl;

        switch (kb_ctrl)
        {
        case 'w'://53
            std::cout << "go forward" << std::endl;
            gpioWrite(STANDBY, 1); //activate h bridge
            gpioWrite(AIN1, 1); //move wheel A
            gpioWrite(AIN2, 0); //move wheel A
            gpioWrite(BIN1, 1); //move wheel B
            gpioWrite(BIN2, 0); //move wheel B
            break;
        case 'a'://49
            std::cout << "turn left" << std::endl;
            gpioWrite(STANDBY, 1); //activate h bridge
            gpioWrite(AIN1, 1); //move wheel A
            gpioWrite(AIN2, 0); //move wheel A
            gpioWrite(BIN1, 0); //move wheel B
            gpioWrite(BIN2, 1); //move wheel B
            break;
        case 's'://50
            std::cout << "go backward" << std::endl;
            gpioWrite(STANDBY, 1); //activate h bridge
            gpioWrite(AIN1, 0); //move wheel A
            gpioWrite(AIN2, 1); //move wheel A
            gpioWrite(BIN1, 0); //move wheel B
            gpioWrite(BIN2, 1); //move wheel B
            break;
        case 'd'://51
            std::cout << "turn right" << std::endl;
            gpioWrite(STANDBY, 1); //activate h bridge
            gpioWrite(AIN1, 0); //move wheel A
            gpioWrite(AIN2, 1); //move wheel A
            gpioWrite(BIN1, 1); //move wheel B
            gpioWrite(BIN2, 0); //move wheel B
            break;
        default:
            std::cout << "stop" << std::endl;
            gpioWrite(STANDBY, 0); //deactivate h bridge
            gpioWrite(AIN1, 0); //move wheel A
            gpioWrite(AIN1, 0); //move wheel A
            gpioWrite(BIN1, 0); //move wheel B
            gpioWrite(BIN2, 0); //move wheel B
            break;
        }
    }
}


