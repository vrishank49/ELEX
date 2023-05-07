#include "CCar.h"

CCar::CCar() {

    if (gpioInitialise() < 0) // check to initialize GPIO
    {                         // GPIO initialize in CCar instead of CMotors incase I have other
                              // inputs for GPIO
        std::cerr << "Failed to initialize GPIO." << std::endl;
    }

    kb_ctrl = 'x';
    running = true;

    cv::namedWindow(HYDRACAM_TITLE, cv::WINDOW_NORMAL); // Create window with normal dimensions
    cv::resizeWindow(HYDRACAM_TITLE, 640, 480); // Set window size
    cvui::init(HYDRACAM_TITLE);

    time = 1; // placeholder until I find out what this is for (autonomous?)

}

CCar::~CCar() {
    gpioTerminate();
}

void CCar::drive() {

    std::thread drivethread([&]() {
        while (running) {
            motorcontrol();
        }
    });

    std::thread imagethread(&CCar::imageprocess, this);

    std::thread videothread(&CCar::imagedisplay, this);

    drivethread.join();
    imagethread.join();
    videothread.join();
}

void CCar::motorcontrol() {
    std::lock_guard<std::mutex> lock(_mutex);

    kb_ctrl = cv::waitKey(1);
        switch (kb_ctrl)
        {
        case 'w'://53
            std::cout << "go forward" << std::endl;
            _motors.forward(time);
            break;
        case 'a'://49
            std::cout << "turn left" << std::endl;
            _motors.left(time);
            break;
        case 's'://50
            std::cout << "go backward" << std::endl;
            _motors.backward(time);
            break;
        case 'd'://51
            std::cout << "turn right" << std::endl;
            _motors.right(time);
            break;
        default:
            std::cout << "stop" << std::endl;
            _motors.stop();
            break;
        }
}

void CCar::imageprocess() {

    while (running) {
            cv::Mat tempframe;
            _guidance.get_im(tempframe);
            _guidance.detectMarkers(tempframe);

            { // {} to ensure lock gets released after clone completes
                std::lock_guard<std::mutex> lock(_mutex);
                hydraframe = tempframe.clone();
            }

        }
}

void CCar::imagedisplay() {
    while (running) {
        cv::Mat displayframe;

        { // ensure lock gets released after clone completes
            std::lock_guard<std::mutex> lock(_mutex);
            displayframe = hydraframe.clone();
        }

        if (!displayframe.empty()) { // check if the frame is not empty
            cv::imshow(HYDRACAM_TITLE, displayframe);
            //cv::waitKey(1);
        }
    }
}

