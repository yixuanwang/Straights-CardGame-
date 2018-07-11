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
    ImageButton(const std::string& xpm_filename);
    virtual ~ImageButton();
};

#endif
