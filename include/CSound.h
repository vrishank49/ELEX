#include <iostream>
#include <pigpio.h>
#include <fstream>
#define HYDRA_SPEAKER 5

#define LFAMOTOR "/home/supra49/Desktop/SOUNDS/LFA motor.wav"

class CSound
{
    public:
        CSound();
        virtual ~CSound();
        void playsound(std::string filedirectory);
        void play();

    protected:

    private:
};
