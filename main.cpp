#include <iostream>
#include <cstdlib>
#include <thread>
#include "MidiHandler.hpp"

MidiHandler midiHandler;

int main(int argc, char **argv)
{
    if (midiHandler.Init() == false) {
        return EXIT_FAILURE;
    }

    std::vector<std::string> inputList = midiHandler.GetInputList();

    if (inputList.size() >= 2)
    {
        midiHandler.OpenInput(1);
        while(true) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }

    return EXIT_SUCCESS;
}