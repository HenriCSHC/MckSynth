#pragma once
#include <string>
#include <vector>
#include <gtkmm/window.h>
#include <gtkmm/comboboxtext.h>
#include <gtkmm/box.h>

class SettingsWindow : public Gtk::Window
{
    public:
        SettingsWindow();
        virtual ~SettingsWindow();
        void Fill(std::vector<std::string> &inputPorts, std::vector<std::string> &outputPorts);

    protected:
        // Signal handlers;
        void on_input_changed();
        void on_output_changed();

        Gtk::ComboBoxText m_inputCombo;
        Gtk::ComboBoxText m_outputCombo;
        Gtk::Box m_box;

        std::vector<std::string> m_inputPorts;
        std::vector<std::string> m_outputPorts;
};