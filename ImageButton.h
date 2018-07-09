#ifndef IMAGEBUTTON_H
#define IMAGEBUTTON_H

#include <string>
#include <gtkmm.h>

class ImageButton : public Gtk::Button
{
protected:

public:
    ImageButton(const std::string& xpm_filename);
    virtual ~ImageButton();
};

#endif
