/* gtkmm example of a custom dialog
 */

#include "examplewindow.h"
#include <iostream>

ExampleWindow::ExampleWindow():
    m_Button{"Show custom Dialog"},
    m_Dialog{"Custom Dialog"},
    m_Image{"img/cat-animal-cat-portrait-mackerel.jpg"},
    m_Label{"Nice cat!"}
{
    set_title("Custom Gtk::Dialog example");

    add(m_VBox);

    m_VBox.pack_start(m_ButtonBox);
    m_ButtonBox.pack_start(m_Button);
    m_Button.signal_clicked().connect(sigc::mem_fun(*this, &ExampleWindow::on_button_clicked) );

    m_Dialog.set_transient_for(*this);
    auto dbox = m_Dialog.get_content_area();
    dbox->add(m_Label);
    dbox->add(m_Image);
    m_Dialog.add_button( "A", 1 ); // returns a button ptr, but we're not using it so thrown away
    m_Dialog.add_button( "B", 2 );
    m_Dialog.add_button( "C", 3 );

    m_Dialog.signal_response().connect(
	sigc::mem_fun(*this, &ExampleWindow::on_about_dialog_response) );

    show_all_children();

    // The widget must be realized and mapped before grab_focus() is called.
    // That's why it's called after show_all_children().
    m_Button.grab_focus();
}

ExampleWindow::~ExampleWindow() {}

void ExampleWindow::on_about_dialog_response(int response_id) {
    std::cout << response_id
	      << ", close=" << Gtk::RESPONSE_CLOSE
	      << ", cancel=" << Gtk::RESPONSE_CANCEL
	      << ", delete_event=" << Gtk::RESPONSE_DELETE_EVENT
	      << std::endl;

    switch (response_id) {
      case 1:
	  std::cout << "chose A" << std::endl;
	  m_Dialog.hide();
	  break;
      case 2:
	  std::cout << "chose B" << std::endl;
	  m_Dialog.hide();
	  break;
      case 3:
	  std::cout << "chose C" << std::endl;
	  m_Dialog.hide();
	  break;
      case Gtk::RESPONSE_CLOSE:
      case Gtk::RESPONSE_CANCEL:
      case Gtk::RESPONSE_DELETE_EVENT:
	  m_Dialog.hide();
	  break;
      default:
	  std::cout << "Unexpected response!" << std::endl;
	  break;
    }
}

void ExampleWindow::on_button_clicked() {
    m_Dialog.show_all(); // show all of its widgets

    //Bring it to the front, in case it was already shown:
    m_Dialog.present();
}
