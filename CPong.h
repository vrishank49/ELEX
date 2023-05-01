#pragma once
#include "CBase4618.h"

#define PONG_CANVAS_SIZE_X 800
#define PONG_CANVAS_SIZE_Y 600
#define BUTTON_WIDTH 100
#define BUTTON_HEIGHT 30

#define PONG_TITLE "Pong by Vrishank"

/**
 * @brief CPong is a class that inherits from CBase4618 and provides an implementation
 * of the game Pong.
 */
class CPong : public CBase4618
{
private:
   CControlPi _pongcontrol; ///< An object of CControlPi to read control inputs
   cv::Point _pong_canvas; ///< A cv::Point object to hold canvas coordinates
   cv::Point ball; ///< A cv::Point object to hold ball position
   cv::Point ball_direction; ///< A cv::Point object to hold ball direction
   int ballsize; ///< The radius of the ball
   int ballspeed; ///< The speed of the ball
   int _player_paddle_pos_new; ///< The new position of the paddle
   int _player_paddle_pos_old; ///< The old position of the paddle

   int _winreset; ///< Flag to reset when game is won

   int _playerscore; ///< Player score
   int _botscore; ///< Bot score

   double _current_time; ///< Current time
   double _delta_time; ///< Change in time
   double _prev_time; ///< Previous time
   double frequency; ///< Frequency (Tick / Ticks per second)
   double fps; ///< Frames per second
   double initialframe; ///< Initial frame holder

   bool _resetflag; ///< Flag for reset check


   cv::Rect _player_paddle_dim; ///< A cv::Rect object to hold player paddle dimensions
   cv::Rect _bot_paddle_dim; ///< A cv::Rect object to hold bot paddle dimensions
   cv::Scalar _white; ///< A cv::Scalar object to hold white color values

public:
   /**
    * @brief Constructor of CPong class.
    * @param webcam_index Index of the webcam to use.
    * @param pong_canvas A cv::Point object to hold canvas coordinates.
    */
   CPong();

   ~CPong() {};

   /**
    * @brief Update the state of the game.
    */
   void update();

   /**
    * @brief Draw the game.
    */
   void draw();
};
