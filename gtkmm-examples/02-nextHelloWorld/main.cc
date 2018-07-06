/*
 * "Programming with gtkmm" https://developer.gnome.org/gtkmm-tutorial/stable/sec-helloworld.html.en
 *
 * Displays a labelled button in a window. When the button is clicked, the text "Hello World" is printed
 * to standard output.
 */

#include <gtkmm/main.h>
#include "helloworld.h"

int main( int argc, char * argv[] ) {
    // Initialize gtkmm with the command line arguments, as appropriate.
    auto app = Gtk::Application::create( argc, argv, "org.gtkmm.example" );

    HelloWorld hello;                // Create the window with the button.
    return app->run( hello );        // Show the window and return when it is closed.
} // main
