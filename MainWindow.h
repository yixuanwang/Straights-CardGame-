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
  std::string humanCpu(int i);
  void errorMessage(std::string);
  void updateDiscard(int, int, int);
  void resetGrid();
protected:
  Table *table;
  int playerTurn_;
  // int clickedCard_;
  //Signal handlers
  void onButtonShuffle();

  void on_hand_clicked(int);
  void onButtonQuit();
  void onButtonRage();


  //Child widgets
  Gtk::Box m_Box;
  Gtk::ButtonBox m_ButtonBox;
  Gtk::Button m_ButtonShuffle, m_ButtonQuit;

  Gtk::Entry m_EntrySeed;
  std::vector <Gtk::Image*> m_Images;
  Gtk::Grid m_Grid;
  Gtk::Grid m_PlayerGrid;


  Gtk::ButtonBox m_Hand;
  Gtk::Button m_ButtonRage;

  //frame
  Gtk::Frame m_FrameHand, m_Frame1, m_Frame2, m_Frame3, m_Frame4, m_FrameTurn, m_FrameTable;

  //labels
  Gtk::Label m_Point1, m_Point2, m_Point3, m_Point4;

  //Playerhand
  std::vector<ImageButton*> hand_;

  public:
    void updateHand(std::vector<Card>, int, std::vector<bool>);
    void updateImageGrid(std::vector<Card>);
    void updatePlayer(int, int, int);
    void printMessage(std::string);

    // int getClickedCard();
};

#endif
