#include "CSound.h"
#include <fstream>
#include <pigpio.h>
#include <iostream>

CSound::CSound()
{
    // Constructor
}

CSound::~CSound()
{
    // Destructor
}

void CSound::playsound(std::string filedirectory)
{
    if (gpioInitialise() < 0)
    {
        std::cerr << "Failed to initialize pigpio." << std::endl;
        return;
    }

    const int SPEAKER = 17; // GPIO pin for the speaker
    gpioSetMode(SPEAKER, PI_OUTPUT);

    std::ifstream inputFile(filedirectory, std::ios::binary);
    if (!inputFile)
    {
        std::cerr << "Failed to open " << filedirectory << "." << std::endl;
        gpioTerminate();
        return;
    }

    // Determine the size of the file
    inputFile.seekg(0, std::ios::end);
    std::streampos fileSize = inputFile.tellg();
    inputFile.seekg(0, std::ios::beg);

    // Read the file into a buffer
    char* buffer = new char[fileSize];
    inputFile.read(buffer, fileSize);
    inputFile.close();

    const int sampleRate = 48000; // Adjust according to your audio file
    const double delaySeconds = 1.0 / sampleRate;

    for (int i = 0; i < fileSize; i++)
    {
        int normalizedValue = buffer[i] > 127 ? 1 : 0;
        //std::cout << normalizedValue << std::endl;
        gpioWrite(HYDRA_SPEAKER, normalizedValue);
        time_sleep(delaySeconds);
    }

    delete[] buffer;

    //gpioTerminate();
}
