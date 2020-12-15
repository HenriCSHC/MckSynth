#include "SettingsWindow.hpp"
#include <iostream>

SettingsWindow::SettingsWindow() 
{
}

SettingsWindow::~SettingsWindow()
{

}

void SettingsWindow::Fill(std::vector<std::string> &inputPorts, std::vector<std::string> &outputPorts)
{
    set_title("[MckSynth] Midi Settings");

    for (unsigned i = 0; i < inputPorts.size(); i++)
    {
        m_inputCombo.append(inputPorts[i]);
    }
    m_inputCombo.signal_changed().connect(sigc::mem_fun(*this, &SettingsWindow::on_input_changed));
    for (unsigned i = 0; i < outputPorts.size(); i++)
    {
        m_outputCombo.append(outputPorts[i]);
    }
    m_outputCombo.signal_changed().connect(sigc::mem_fun(*this, &SettingsWindow::on_output_changed));

    m_box.set_orientation(Gtk::ORIENTATION_VERTICAL);
    m_box.pack_start(m_inputCombo);
    m_box.pack_start(m_outputCombo);

    add(m_box);
    show_all_children();
}

void SettingsWindow::on_input_changed()
{
    Glib::ustring text = m_inputCombo.get_active_text();
    if (text.empty() == false)
    {
        std::cout << "As MIDI input you chose " << text << std::endl;
    }
}

void SettingsWindow::on_output_changed()
{
    Glib::ustring text = m_outputCombo.get_active_text();
    if (text.empty() == false)
    {
        std::cout << "As MIDI output you chose " << text << std::endl;
    }
}