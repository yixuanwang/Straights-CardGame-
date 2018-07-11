#include "ImageButton.h"
using namespace std;

ImageButton::ImageButton(const string& xpm_filename)
{
    // Create box for image and label
    box = new Gtk::HBox;
    box->set_border_width(0.2);

    // Now on to the image stuff
    image = new Gtk::Image(xpm_filename);

    // Pack the image and label into the box
    box->pack_start(*image);

    box->show_all();
    add(*box);
}

ImageButton::~ImageButton()
{
  delete image;
  delete box;
}
