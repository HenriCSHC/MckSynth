#include <gtkmm.h>
#include <iostream>
#include <cstdlib>

Gtk::Window* pWindow = nullptr;

int main(int argc, char **argv)
{
    auto app = Gtk::Application::create(argc, argv, "com.mck-audio.gladetest");

    auto refBuilder = Gtk::Builder::create();
    try
    {
        refBuilder->add_from_file("gui.glade");
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
    if (pWindow) {
        app->run(*pWindow);
        delete pWindow;
    }

    return EXIT_SUCCESS;
}