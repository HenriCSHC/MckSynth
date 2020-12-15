#include "AudioHandler.hpp"
#include <iostream>

AudioHandler::AudioHandler()
{
    lastValues[0] = 0.0;
    lastValues[1] = 0.0;
}

AudioHandler::~AudioHandler()
{
}

int playback(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames, double streamTime, RtAudioStreamStatus status, void *userData)
{
    AudioHandler* audioHandler = (AudioHandler *)userData;

    double *buffer = (double *)outputBuffer;

    for (unsigned i = 0; i < nBufferFrames; i++)
    {
        for (unsigned j = 0; j < 2; j++)
        {
            *buffer++ = 0.7 * audioHandler->lastValues[j];
            audioHandler->lastValues[j] += 0.005 * (j+1+(j*0.1));
            if (audioHandler->lastValues[j] >= 1.0) {
                audioHandler->lastValues[j] -= 2.0;
            }
        }
    }

    return 0;
}

void AudioHandler::Init()
{
    unsigned nDevices = audio.getDeviceCount();
    devices.clear();
    devices.resize(nDevices);

    std::cout << "Audio Devices:\n";
    for (unsigned i = 0; i < nDevices; i++)
    {
        devices[i] = audio.getDeviceInfo(i);

        if (devices[i].probed)
        {
            std::cout << "  #" << i + 1 << ": " << devices[i].name << " (" << devices[i].inputChannels << " IN / " << devices[i].outputChannels << " OUT)\n";
        }
    }
    std::cout << "Default input device: " << (audio.getDefaultInputDevice()) << std::endl;
    std::cout << "Default output device: " << (audio.getDefaultOutputDevice()) << std::endl;
}

bool AudioHandler::Start()
{
    unsigned sampleRate = 48000;
    unsigned bufferSize = 256;
    //audio = new RtAudio(0, 2, 0, 0, RTAUDIO_FLOAT64, sampleRate, &bufferSize, )
    RtAudio::StreamParameters param;
    param.deviceId = audio.getDefaultOutputDevice();
    param.firstChannel = 0;
    param.nChannels = 2;

    try
    {
        audio.openStream(&param, NULL, RTAUDIO_FLOAT64, sampleRate, &bufferSize, &playback, this);
        audio.startStream();
    }
    catch (RtAudioError &e)
    {
        e.printMessage();
        return false;
    }

    return true;
}

bool AudioHandler::Stop()
{
    if (audio.isStreamRunning())
    {
        try
        {
            audio.stopStream();
        }
        catch (RtAudioError &e)
        {
            e.printMessage();
        }
    }

    if (audio.isStreamOpen())
    {
        audio.closeStream();
    }

    return true;
}