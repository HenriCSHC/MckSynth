#include <gtkmm.h>
#include <iostream>
#include <cstdlib>
#include <cmath>

Gtk::Window *pWindow = nullptr;
Gtk::Scale *pScale = nullptr;
Gtk::DrawingArea *pDrawing = nullptr;

static void scale_value_changed()
{
    if (pScale)
    {
        std::cout << "Slider changed: " << pScale->get_value() << std::endl;
    }
}
static gchar *
format_value_callback(gdouble value)
{
    double db = 20.0 * std::log10(value);
    return g_strdup_printf("%.*fdB", 1, db);
}
static bool drawing_draw(const Cairo::RefPtr<Cairo::Context> &cr)
{
    Gtk::Allocation allocation = pDrawing->get_allocation();
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

int main(int argc, char **argv)
{
    auto app = Gtk::Application::create(argc, argv, "com.mck-audio.gladetest");

    auto refBuilder = Gtk::Builder::create();
    try
    {
        refBuilder->add_from_file("./content/gui.glade");
    }
    catch (const Glib::FileError &ex)
    {
        std::cerr << "FileError: " << ex.what() << std::endl;
        return EXIT_FAILURE;
    }
    catch (const Glib::MarkupError &ex)
    {
        std::cerr << "MarkupError: " << ex.what() << std::endl;
        return EXIT_FAILURE;
    }
    catch (const Gtk::BuilderError &ex)
    {
        std::cerr << "BuilderError: " << ex.what() << std::endl;
        return EXIT_FAILURE;
    }

    refBuilder->get_widget("MyWindow", pWindow);
    if (pWindow)
    {
        pWindow->set_default_size(400, 300);
        refBuilder->get_widget("GainSlider", pScale);
        if (pScale)
        {
            pScale->set_range(0.0, 1.0);
            pScale->set_value(0.5);
            pScale->signal_value_changed().connect(sigc::ptr_fun(scale_value_changed));
            pScale->signal_format_value().connect(sigc::ptr_fun(format_value_callback));
        }
        refBuilder->get_widget("Scope", pDrawing);
        if (pDrawing)
        {
            pDrawing->signal_draw().connect(sigc::ptr_fun(drawing_draw));
        }
        app->run(*pWindow);
        delete pWindow;
    }

    return EXIT_SUCCESS;
}