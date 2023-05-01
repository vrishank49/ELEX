#include <iostream>
#include "pigpio.h"
#include <opencv2/opencv.hpp>
#include "cvui.h"

#include "CControlPi.h"
#include "CBase4618.h"
#include "CPong.h"
#include "CSort.h"
#include "CFinal.h"

std::string gstreamer_pipeline(int capture_width, int capture_height, int framerate, int display_width, int display_height) {
    return
            " libcamerasrc ! video/x-raw, "
            " width=(int)" + std::to_string(capture_width) + ","
            " height=(int)" + std::to_string(capture_height) + ","
            " framerate=(fraction)" + std::to_string(framerate) +"/1 !"
            " videoconvert ! videoscale !"
            " video/x-raw,"
            " width=(int)" + std::to_string(display_width) + ","
            " height=(int)" + std::to_string(display_height) + " ! appsink";
}

void print_menu()
{
    std::cout << "\n***********************************";
    std::cout << "\n* ELEX4618 Template Project";
    std::cout << "\n***********************************";
    std::cout << "\n(1) Lab 1 - User Input";
    std::cout << "\n(2) Lab 2 - Grading";
    std::cout << "\n(3) Lab 3 - Embedded Control";
    std::cout << "\n(4) Lab 4 - Etch-A-Sketch";
    std::cout << "\n(5) Lab 5 - Pong";
    std::cout << "\n(6) Lab 6 - Classic Arcade Game";
    std::cout << "\n(7) Lab 7 - Linux Port";
    std::cout << "\n(8) Lab 8 - Recycling Sorter";
    std::cout << "\n(0) Exit";
    std::cout << "\nCMD> ";
}

////////////////////////////////////////////////////////////////
// Lab 1
////////////////////////////////////////////////////////////////
void lab1()
{
}

////////////////////////////////////////////////////////////////
// Lab 2
////////////////////////////////////////////////////////////////
void lab2()
{
}

////////////////////////////////////////////////////////////////
// Lab 3
////////////////////////////////////////////////////////////////
void lab3()
{
    CControlPi control;
    int user_input = 0, type, channel, value, button_sel, press_count = 0;

    while (cv::waitKey(1) != 'q') {
      std::cout << "\n(1) - Joystick Input\n(2) - Button Input\n(3) - Button Debounce Test\n(4) - Servo Test\nPlease select an option: ";
      std::cin >> user_input;

      switch (user_input) {
      case 1: // test joystick output
        while (cv::waitKey(1) != 'q') {
         control.get_data(ANALOG, JOY_X, control.value);
         std::cout << "X: " << control.value << std::endl;
         // std::cout << "(% " << control.get_analog(control.value) << ")" << std::endl;
         control.get_data(ANALOG, JOY_Y, control.value);
         std::cout << "Y: "<< control.value << std::endl << std::endl;
         // std::cout << "(% " << control.get_analog(control.value) << ")" << std::endl << std::endl;
        }
         break;
      case 2: // test button press
        std::cout << "Which button: ";
        std::cin >> button_sel;

        while (cv::waitKey(1) != 'q') {
            if (button_sel == 1) {
                control.get_data(DIGITAL, BUTTON_1, control.value);
                //cv::waitKey(25);
            }
            else if (button_sel == 2) {
                control.get_data(DIGITAL, BUTTON_2, control.value);
                //cv::waitKey(25);
            }

            std::cout << control.value << std::endl;
        }
        break;
      case 3: // test debounce/increment button press
         press_count = 1;
            std::cout << "Which button? ";
            std::cin >> button_sel;
            if (button_sel == 1) {
               do {
                  if (control.get_button(DIGITAL, BUTTON_1)) { // check if button has been pressed on falling edge of active low signal
                     std::cout << "Press Count = " << press_count << std::endl;
                     press_count++;
                     //cv::waitKey(25);
                  }
               } while (cv::waitKey(1) != 'q');

            }
            else if (button_sel == 2)
            {
               do {
                  if (control.get_button(DIGITAL, BUTTON_2)) { // check if button has been pressed on falling edge of active low signal
                     std::cout << "Press Count = " << press_count << std::endl;
                     press_count++;
                     //cv::waitKey(25);

                  }
               } while (cv::waitKey(1) != 'q');
            }
            else
               std::cout << "Please enter a valid button, 1 or 2.";
            std::cout << std::endl;
         break;
      case 4: // servo test (find boundaries before gears grind)
      while (cv::waitKey(1) != 'q') {
      //for (int pos = 500; pos < 2500; pos++) {
      //  control.set_data(SERVO, SERVO_1, pos);
      //  cv::waitKey(1);
      //}



      //for (int pos = 2500; pos > 500; pos--) {
      //  control.set_data(SERVO, SERVO_1, pos);
      //        cv::waitKey(1);
      //}
        control.set_data(SERVO, SERVO_2, control.servo_pos2);
        control.set_data(SERVO, SERVO_1, control.servo_pos);

        // *** Found servo dead ranges to be 459-2541

        control._control_canvas = cv::Mat::zeros(800, 800, CV_8UC3);
        cvui::trackbar(control._control_canvas, 0, 60, 700, &control.servo_pos, (int)0, (int)3000);
        cvui::trackbar(control._control_canvas, 0, 200, 700, &control.servo_pos2, (int)0, (int)3000);

        //cvui::trackbar(control._control_canvas, 0, 60, 700, &control.servo_pos, (int)SERVO_1_RANGE_LOW, (int)SERVO_1_RANGE_HIGH);
        cv::imshow(CONTROL_TITLE, control._control_canvas);
        cv::waitKey(1);
      }

         break;
      default:
         std::cout << "\nNo such case exists.\n\n";
         break;
      }

      //gpioTerminate();
   }

    // to kill gpio in terminal:
    // cat /var/run/pigpio.pid
    // sudo kill -9 <number/pid that shows up>
}

////////////////////////////////////////////////////////////////
// Lab 4
////////////////////////////////////////////////////////////////
void lab4()
{
   // cv::Point canvas_size = cv::Point(CANVAS_SIZE_X, CANVAS_SIZE_Y); // decide how big to make the canvas by defining a cv::Point variable
   // CSketch sketch(COM9, canvas_size); // construct CSketch with given parameters
   // sketch.run();  // run created sketch object
}

////////////////////////////////////////////////////////////////
// Lab 5
////////////////////////////////////////////////////////////////
void lab5()
{
    //cv::Point pong_canvas_size = cv::Point(PONG_CANVAS_SIZE_X, PONG_CANVAS_SIZE_Y); // decide how big to make the canvas by defining a cv::Point variable
    CPong pong; // construct CSketch with given parameters
    pong.run();  // run created sketch object
}

////////////////////////////////////////////////////////////////
// Lab 6
////////////////////////////////////////////////////////////////
void lab6()
{
    //CSpaceInvadersGame spaceinvaders(COM9);
    //spaceinvaders.run();
}

////////////////////////////////////////////////////////////////
// Lab 8
////////////////////////////////////////////////////////////////
void lab8()
{
    CSort sorter;
    sorter.run();
}

void lab9()
{
    CFinal finalproject;
    finalproject.run();
}

int main (void) {
    int cmd = -1;
    do
    {
        print_menu();
        std::cin >> cmd;
        switch (cmd)
        {
            case 1: lab1();
            case 2: lab2();
            case 3: lab3();
            case 4: lab4();
            case 5: lab5();
            case 6: lab6();
            case 8: lab8();
            case 9: lab9();
        }
    } while (cmd != 0);
}
