#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <iostream>
#include <gtkmm.h>

class MainWindow : public Gtk::Window {
public:
  MainWindow();
  virtual ~MainWindow();

protected:

  //Signal handlers
  void onButtonShuffle();
  void onButtonQuit();

  //Child widgets
  Gtk::Box m_Box;
  Gtk::ButtonBox m_ButtonBox;
  Gtk::Button m_ButtonShuffle, m_ButtonQuit;

  Gtk::Entry m_EntrySeed;
  // Gtk::ButtonBox m_ImageBox;
  std::vector <Gtk::Image> m_Images;
  Gtk::Image m_Image2;
  Gtk::Grid m_Grid;
};

#endif
