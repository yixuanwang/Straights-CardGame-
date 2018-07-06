// Includes the entire gtkmm kit. Should normally be more specific.
#include <gtkmm.h>           
#include <iostream>

int main( int argc, char * argv[] ) {
    // Creates a Gtk::Application object initialized from argument list. Necessary in all gtkmm applications.
    // Passes in command-line arguments and application id.
    // application id must conform to rules listed in
    // https://developer.gnome.org/gio/stable/GApplication.html#g-application-id-is-valid
    auto app = Gtk::Application::create( argc, argv, "org.gtkmm.examples.base" );

    // Creates a window, which is displayed via the run command.
    Gtk::Window window;

    // Set the default window size.
    window.set_default_size( 200, 200 );
    std::cout << "waiting for window to close" << std::endl;
    
    // Shows the window and enters the main gtkmm processing loop, which will finish when the window is closed.
    return app->run( window );
} // main
