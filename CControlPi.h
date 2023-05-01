#pragma once
#include <opencv2/opencv.hpp>

/**
 * @file CControlPi.h
 * @brief Declaration of CControlPi class.
 */

#pragma once
//#include "Serial.h"

 /**
  * @brief Joystick X axis channel.
  */
#define JOY_X 11

  /**
   * @brief Joystick Y axis channel.
   */
#define JOY_Y 4

   /**
    * @brief Button 1 channel.
    */
#define BUTTON_1 17

    /**
     * @brief Button 2 channel.
     */
#define BUTTON_2 4

     /**
      * @brief Green LED channel.
      */
#define GREEN_LED 39

      /**
       * @brief Red LED channel.
       */
#define RED_LED 38

       /**
        * @brief Blue LED channel.
        */
#define BLUE_LED 37

        /**
         * @brief COM port for communication.
         */
#define COM5 5
#define COM9 9

#define SERVO_1 27
#define SERVO_2 22

#define SERVO_1_RANGE_LOW 500
#define SERVO_1_RANGE_HIGH 2502

#define CONTROL_TITLE "CControlPi"

         /**
          * @brief Enumeration of possible data types.
          */
enum { DIGITAL = 0, ANALOG, SERVO };

/**
 * @brief The CControlPi class provides methods for interacting with a microcontroller.
 */
class CControlPi {
private:


//   Serial _com; ///< The communication port.
   int type; ///< The type of data.

   int current_button_state; ///< The current button state.
   int previous_button_state; ///< The previous button state.
   bool press_check; ///< Flag indicating if button is pressed.

   //ADC
   unsigned char inBuf[3];
   int handle;



public:

    // canvas
    cv::Mat _control_canvas;

       // Servo
   int servo_pos;
   int servo_pos2;

    int channel; ///< The channel of the data.
    int value; ///< The value of the data.



   /**
    * @brief Constructor for the CControlPi class.
    */
   CControlPi();

   /**
    * @brief Destructor for the CControlPi class.
    */
   ~CControlPi();

   /**
    * @brief Initializes the communication port.
    * @param comport The communication port number.
    */
   void init();

   /**
    * @brief Gets the analog value from a channel.
    * @param result The analog result.
    * @return The analog value.
    */
   float get_analog(int result);

   /**
    * @brief Gets data from a channel.
    * @param type The type of data.
    * @param channel The channel of the data.
    * @param result The data result.
    * @return True if successful, false otherwise.
    */
   bool get_data(int type, int channel, int& result);

   /**
    * @brief Sets data on a channel.
    * @param type The type of data.
    * @param channel The channel of the data.
    * @param val The value of the data.
    * @return True if successful, false otherwise.
    */
   bool set_data(int type, int channel, int val);

   /**
    * @brief Gets the state of a button.
    * @param type The type of button.
    * @param channel The channel of the button.
    * @return True if the button is pressed, false otherwise.
    */
   bool get_button(int type, int channel);

   /**
    * @brief Delays for a specified time.
    * @param delay The delay time.
    */
   void delay_timer(double delay);

   /**
    * @brief Replicates kbhit function
    */
   int kbhit(void);
};
