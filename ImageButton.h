#ifndef IMAGEBUTTON_H
#define IMAGEBUTTON_H

#include <string>
#include <gtkmm.h>

class ImageButton : public Gtk::Button
{
protected:
    Gtk::Image * image;
    Gtk::HBox * box;
public:
  /*
  ensures: initialization of this
  */
    ImageButton(const std::string& xpm_filename);
  /*
  modifies: stack
  ensures: memory is freed and this is deleted
  */
    virtual ~ImageButton();
};

#endif
