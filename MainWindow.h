#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <iostream>
#include <gtkmm.h>
#include <vector>
#include "ImageButton.h"
#include "Table.h"

class Table;

class MainWindow : public Gtk::Window {
public:
  MainWindow();
  virtual ~MainWindow();

protected:
  Table *table;
  //Signal handlers
  void onButtonShuffle();
  void onButtonQuit();
  void onButtonRage();
  void updateHand(vector<Card>);

  //Child widgets
  Gtk::Box m_Box;
  Gtk::ButtonBox m_ButtonBox;
  Gtk::Button m_ButtonShuffle, m_ButtonQuit;

  Gtk::Entry m_EntrySeed;
  std::vector <Gtk::Image> m_Images;
  Gtk::Grid m_Grid;
  Gtk::Grid m_PlayerGrid;


  Gtk::ButtonBox m_Hand;
  Gtk::Button m_ButtonRage;

  //frame
  Gtk::Frame m_FrameHand, m_Frame1, m_Frame2, m_Frame3, m_Frame4, m_FrameTurn;

  //labels
  Gtk::Label m_Point1, m_Point2, m_Point3, m_Point4;

  //Playerhand
  std::vector<ImageButton*> hand_;
};

#endif
