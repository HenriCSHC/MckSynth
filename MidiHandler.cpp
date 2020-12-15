#include "MidiHandler.hpp"
#include <iostream>
#include <cstdlib>
#include <rtmidi/RtMidi.h>

static void processMidiIn(double timeStamp, std::vector<unsigned char> *message, void *userData)
{
    ((MidiHandler *)userData)->MidiInCallback(timeStamp, message);
}


MidiHandler::MidiHandler()
    : inputList(), outputList(), midiIn(nullptr), midiOut(nullptr) {}

MidiHandler::~MidiHandler()
{
    // Cleanup
    if (midiIn != nullptr) {
        delete midiIn;
    }
    if (midiOut != nullptr) {
        delete midiOut;
    }
}

bool MidiHandler::Init()
{
    inputList.clear();
    outputList.clear();
    // MIDI IN
    try {
        midiIn = new RtMidiIn();
    } catch (RtMidiError &error) {
        error.printMessage();
        return false;
    }
    unsigned nPorts = midiIn->getPortCount();
    std::cout << std::to_string(nPorts) << " MIDI input ports are available:\n";
    std::string portName = "";
    for (unsigned i = 0; i < nPorts; i++)
    {
        try {
            portName = midiIn->getPortName(i);
        } catch (RtMidiError &error) {
            error.printMessage();
            return false;
        }
        std::cout << "  #" << i+1 << ": " << portName << "\n";
        inputList.push_back(portName);
    }
    std::cout << std::endl;

    // MIDI OUT
    try {
        midiOut = new RtMidiOut();
    } catch (RtMidiError &error) {
        error.printMessage();
        return false;
    }
    nPorts = midiOut->getPortCount();
    std::cout << std::to_string(nPorts) << " MIDI output ports are available:\n";
    portName = "";
    for (unsigned i = 0; i < nPorts; i++)
    {
        try {
            portName = midiOut->getPortName(i);
        } catch (RtMidiError &error) {
            error.printMessage();
            return false;
        }
        std::cout << "  #" << i+1 << ": " << portName << "\n";
        outputList.push_back(portName);
    }
    std::cout << std::endl;

    return true;
}

bool MidiHandler::OpenInput(unsigned index)
{
    if (index >= inputList.size())
    {
        return false;
    }

    try {
        midiIn->openPort(index);
    } catch (RtMidiError &error) {
        error.printMessage();
        return false;
    }

    midiIn->setCallback(&processMidiIn, this);

    return true;
}

void MidiHandler::MidiInCallback(double timeStamp, std::vector<unsigned char> *message)
{
    unsigned nBytes = message->size();
    for (unsigned i = 0; i < nBytes; i++)
    {
        std::cout << "Byte " << i << " = " << (int)message->at(i) << ", ";
    }
    if (nBytes > 0)
    {
        std::cout << "stamp = " << timeStamp << std::endl;
    }
}