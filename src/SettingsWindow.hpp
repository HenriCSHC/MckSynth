#pragma once
#include <string>
#include <vector>
#include <gtkmm/window.h>
#include <gtkmm/comboboxtext.h>
#include <gtkmm/box.h>
#include <gtkmm/drawingarea.h>
#include <gtkmm/hvscale.h>

class Slider : public Gtk::VScale
{
    public:
        Slider();
        virtual ~Slider() {};

    protected:
        void on_value_changed() override;
};

class ScopeArea : public Gtk::DrawingArea
{
    public:
        ScopeArea() {};
        virtual ~ScopeArea() {};

    protected:
        bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
};

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
        Gtk::Box m_horBox;
        Gtk::Box m_vertBox;
        ScopeArea m_scope;
        Slider m_slider;

        std::vector<std::string> m_inputPorts;
        std::vector<std::string> m_outputPorts;
};