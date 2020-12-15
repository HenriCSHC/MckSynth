#pragma once
#include <string>
#include <vector>

class RtMidiIn;
class RtMidiOut;

class MidiHandler {
    public:
        MidiHandler();
        ~MidiHandler();

        bool Init();
        std::vector<std::string> GetInputList() { return inputList; }
        std::vector<std::string> GetOutputList() { return outputList; }
        bool OpenInput(unsigned index);
        
        void MidiInCallback(double timeStamp, std::vector<unsigned char> *message);

    private:
        RtMidiIn *midiIn;
        RtMidiOut *midiOut;
        std::vector<std::string> inputList;
        std::vector<std::string> outputList;
};