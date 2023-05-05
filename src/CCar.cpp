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
    // CAMERA CODE FOR ARUCO DETECTION
    _guidance.get_im(hydraframe);
    cv::imshow(HYDRACAM_TITLE, hydraframe);

    // JOHN'S OLD MOTOR CONTROL CODE - MOVE TO CMOTORS WHEN WE HAVE TIME
        //std::cin >> kb_ctrl;
        kb_ctrl = cv::waitKey(1);

        switch (kb_ctrl)
        {
        case 'w'://53
            std::cout << "go forward" << std::endl;
            gpioWrite(25, 1); //activate h bridge
            gpioWrite(17, 1); //move wheel A
            gpioWrite(27, 0); //move wheel A
            gpioWrite(24, 1); //move wheel B
            gpioWrite(23, 0); //move wheel B
            break;
        case 'a'://49
            std::cout << "turn left" << std::endl;
            gpioWrite(25, 1); //activate h bridge
            gpioWrite(17, 1); //move wheel A
            gpioWrite(27, 0); //move wheel A
            gpioWrite(24, 0); //move wheel B
            gpioWrite(23, 1); //move wheel B
            break;
        case 's'://50
            std::cout << "go backward" << std::endl;
            gpioWrite(25, 1); //activate h bridge
            gpioWrite(17, 0); //move wheel A
            gpioWrite(27, 1); //move wheel A
            gpioWrite(24, 0); //move wheel B
            gpioWrite(23, 1); //move wheel B
            break;
        case 'd'://51
            std::cout << "turn right" << std::endl;
            gpioWrite(25, 1); //activate h bridge
            gpioWrite(17, 0); //move wheel A
            gpioWrite(27, 1); //move wheel A
            gpioWrite(24, 1); //move wheel B
            gpioWrite(23, 0); //move wheel B
            break;
            case 'x'://48
            std::cout << "stop" << std::endl;
            gpioWrite(25, 0); //deactivate h bridge
            gpioWrite(17, 0); //move wheel A
            gpioWrite(27, 0); //move wheel A
            gpioWrite(24, 0); //move wheel B
            gpioWrite(23, 0); //move wheel B

            break;
        default:
            std::cout << "stop" << std::endl;
            gpioWrite(25, 0); //deactivate h bridge
            gpioWrite(17, 0); //move wheel A
            gpioWrite(27, 0); //move wheel A
            gpioWrite(24, 0); //move wheel B
            gpioWrite(23, 0); //move wheel B
            break;
        }
    }
}
