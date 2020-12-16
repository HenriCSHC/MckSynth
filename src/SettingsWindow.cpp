#include "SettingsWindow.hpp"
#include <iostream>

Slider::Slider()
{
    set_range(0.0, 1.0);
    set_digits(3);
    set_value_pos(Gtk::POS_TOP);
    set_draw_value();
    set_inverted();
    set_value(0.5);
}

void Slider::on_value_changed()
{
    std::cout << "Slider changed: " << get_value() << std::endl;
}

bool ScopeArea::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
    Gtk::Allocation allocation = get_allocation();
    const int width = allocation.get_width();
    const int height = allocation.get_height();

    int xc = width / 2;
    int yc = height / 2;

    cr->set_line_width(2.0);
    cr->set_source_rgb(0.0, 0.5, 1.0);
    cr->move_to(xc, 0);
    cr->line_to(xc, height);
    cr->move_to(0, yc);
    cr->line_to(width, yc);
    cr->stroke();

    return true;
}

SettingsWindow::SettingsWindow() 
{
}

SettingsWindow::~SettingsWindow()
{

}

void SettingsWindow::Fill(std::vector<std::string> &inputPorts, std::vector<std::string> &outputPorts)
{
    set_title("[MckSynth] Midi Settings");
    set_default_size(300, 400);

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

    m_vertBox.set_spacing(5);
    m_vertBox.set_orientation(Gtk::ORIENTATION_VERTICAL);
    m_vertBox.pack_start(m_inputCombo, Gtk::PACK_SHRINK);
    m_vertBox.pack_start(m_outputCombo, Gtk::PACK_SHRINK);
    m_vertBox.pack_start(m_scope, Gtk::PACK_EXPAND_WIDGET);

    m_horBox.add(m_slider);
    m_horBox.add(m_vertBox);

    add(m_horBox);
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