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

    private:
        RtAudio audio;
        std::vector<RtAudio::DeviceInfo> devices;
};