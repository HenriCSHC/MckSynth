#include <iostream>
#include <cstdlib>
#include <thread>
#include <gtkmm.h>

#include "AudioHandler.hpp"
#include "MidiHandler.hpp"
#include "SettingsWindow.hpp"

AudioHandler audioHandler;
MidiHandler midiHandler;

int main(int argc, char **argv)
{
    if (midiHandler.Init() == false) {
        return EXIT_FAILURE;
    }

    audioHandler.Init();

    std::vector<std::string> inputList = midiHandler.GetInputList();
    std::vector<std::string> outputList = midiHandler.GetOutputList();

    auto app = Gtk::Application::create(argc, argv, "com.mck.synth");

    SettingsWindow settingsWindow;
    settingsWindow.Fill(inputList, outputList);

    audioHandler.Start();

    app->run(settingsWindow);

    audioHandler.Stop();

    /*
    if (inputList.size() >= 2)
    {
        midiHandler.OpenInput(1);
        while(true) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }*/

    return EXIT_SUCCESS;
}