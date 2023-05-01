// Code taken from: https://github.com/Qengineering/Libcamera-OpenCV-RPi-Bullseye-64OS/blob/main/main.cpp

#pragma once

#ifndef CCAMERA_H
#define CCAMERA_H


class CCamera : public CBase4618
{
    private:

        std::string gstreamer_pipeline(int capture_width, int capture_height, int framerate, int display_width, int display_height);
    public:
        int capture_width, capture_height, framerate, display_width, display_height;
         CCamera();
        ~CCamera();

        update();

    protected:

};

#endif // CCAMERA_H
