#pragma once
#include <vector>
#include "rtaudio/RtAudio.h"

class AudioHandler {
    public:
        AudioHandler();
        ~AudioHandler();

        void Init();
        bool Start();
        bool Stop();
        
        double lastValues[2];
        double freq = 440.0;
        unsigned phase = 0;
        unsigned sampleRate = 48000;

    private:
        RtAudio audio;
        std::vector<RtAudio::DeviceInfo> devices;
};