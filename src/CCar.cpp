#include "CCar.h"

CCar::CCar() {
    if (gpioInitialise() < 0) {
        std::cerr << "Failed to initialize GPIO." << std::endl;
    }

    kb_ctrl = 'x';
    running = true;

    cv::namedWindow(HYDRACAM_TITLE, cv::WINDOW_NORMAL);
    cv::resizeWindow(HYDRACAM_TITLE, 640, 480);
    cvui::init(HYDRACAM_TITLE);

    time = 1;
}

CCar::~CCar() {
    _server.stop();
    gpioTerminate();
    cv::destroyAllWindows();
}

void CCar::serverinit(CServer* server) {
    server->start(PORT);
}

void CCar::drive() {
    std::thread imagethread(&CCar::imageprocess, this);
    imagethread.detach();

    std::thread t(&CCar::serverinit, this, &_server);
    t.detach();

    while (running) {
        std::vector<std::string> cmds;
        _server.get_cmd(cmds);

        for (const std::string& cmd : cmds) {
            motorcontrol(cmd);
        }

        {
            std::lock_guard<std::mutex> lock(_mutex);
            if (!hydraframe.empty()) {
                cv::imshow(HYDRACAM_TITLE, hydraframe);
            }
        }

        int key = cv::waitKey(1);
        if (key == 'q') {
            break;
        }
    }
}


void CCar::motorcontrol(const std::string& key) {
    if (key == "w") {
        std::cout << "go forward!!!" << std::endl;
        _motors.forward(time);
    } else if (key == "a") {
        std::cout << "turn left" << std::endl;
        _motors.left(time);
    } else if (key == "s") {
        std::cout << "go backward" << std::endl;
        _motors.backward(time);
    } else if (key == "d") {
        std::cout << "turn right" << std::endl;
        _motors.right(time);
    } else if (key == "k") {
        std::cout << "shoot" << std::endl;
        gpioServo(SHOOT_SERVO, 1700);
    } else {
        std::cout << "stop" << std::endl;
        _motors.stop();
        gpioWrite(LED_1, 1);
    }
}

void CCar::imageprocess() {
    while (true) {
        cv::Mat new_frame;
        _guidance.get_im(new_frame);
        _guidance.detectMarkers(new_frame);
        {
            std::lock_guard<std::mutex> lock(_mutex);
            hydraframe = new_frame;
        }
    }
}
