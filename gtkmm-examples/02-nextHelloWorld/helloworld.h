/*
 * "Programming with gtkmm" https://developer.gnome.org/gtkmm-tutorial/stable/sec-helloworld.html.en
 *
 * Displays a labelled button in a window. When the button is clicked, the text "Hello World" is printed
 * to standard output.
 */

#ifndef GTKMM_EXAMPLE_HELLOWORLD_H
#define GTKMM_EXAMPLE_HELLOWORLD_H

#include <gtkmm/button.h>
#include <gtkmm/window.h>

class HelloWorld : public Gtk::Window {
  public:
    HelloWorld();
    virtual ~HelloWorld();
	
  protected:
    // Signal handlers:
    virtual void onButtonClicked();
	
    // Member widgets:
    Gtk::Button m_button;
}; // HelloWorld

#endif
