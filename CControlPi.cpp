#include "CControlPi.h"
#include "pigpio.h"
#include <opencv2/opencv.hpp>
#define CVUI_IMPLEMENTATION
#include "cvui.h"

// #includes for kbhit
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

CControlPi::CControlPi() {
    _control_canvas = cv::Mat::zeros(800, 800, CV_8UC3);
    cvui::init(CONTROL_TITLE);
    cv::imshow(CONTROL_TITLE, _control_canvas);

    if (gpioInitialise() < 0) {} // initialize GPIO}

    gpioSetMode(BUTTON_1, PI_INPUT);
    gpioSetMode(BUTTON_2, PI_INPUT);

    // debounce
    previous_button_state = 1;

    // ADC
    handle = spiOpen(0, 200000, 3); // Mode 0, 200kHz

    servo_pos = 700;
    servo_pos2 = 700;

    // Servo
    gpioSetMode(SERVO_1, PI_OUTPUT);
    gpioSetMode(SERVO_2, PI_OUTPUT);
}

bool CControlPi::get_button(int type, int channel) {
    if (previous_button_state == 1)
   {
      press_check = true;
   }

   get_data(type, channel, previous_button_state);
   cv::waitKey(1);

   if (press_check == true) {

      get_data(type, channel, current_button_state);

      if ((current_button_state == 0) && (previous_button_state == 0)) {
         press_check = false;
         return true;
      }
      else
         return false;
   }
   else
      return false;
}

bool CControlPi::get_data(int type, int channel, int& value) {
    if (type == DIGITAL)
            value = gpioRead(channel);
    else if (type == ANALOG) {
        if (channel == JOY_X) {
            char cmd[] = { 1, 128, 0 }; // 0b1XXX0000 where XXX=channel 0
            spiXfer(handle, cmd, (char*) inBuf, 3); // Transfer 3 bytes
            value = ((inBuf[1] & 3) << 8) | inBuf[2]; // Format 10 bits
        }
        else if (channel == JOY_Y) {
            char cmd[] = { 1, 144, 0 }; // 0b1XXX0000 where XXX=channel 1
            spiXfer(handle, cmd, (char*) inBuf, 3); // Transfer 3 bytes
            value = ((inBuf[1] & 3) << 8) | inBuf[2]; // Format 10 bits
        }
    }
}

bool CControlPi::set_data(int type, int channel, int val) {
    if (type == DIGITAL) {}
    else if (type == SERVO) {
        if (channel == SERVO_1) {
            gpioServo(SERVO_1, val);
        }
        else if (channel == SERVO_2) {
            gpioServo(SERVO_2, val);
        }
    }
}

float CControlPi::get_analog(int result) {
    float temp_int = result * 100;
    return (temp_int / 1024);
}

// kbhit function taken from:
// https://cboard.cprogramming.com/c-programming/63166-kbhit-linux.html

CControlPi::~CControlPi() {
    gpioTerminate();
    cv::destroyAllWindows();
    spiClose(handle);
}
