#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <iostream>
#include <gtkmm.h>
#include <vector>
#include "ImageButton.h"
#include "Table.h"

class Table;

class MainWindow : public Gtk::Window {
<<<<<<< HEAD
=======
  bool reset;
public:
  MainWindow();
  virtual ~MainWindow();
  std::string humanCpu(int i);
  void errorMessage(std::string);
  void updateDiscard(int, int, int);
  void resetGrid();
>>>>>>> 13b2443cc31c584e1bf75c0c37ee7c902175e0e3
protected:
  Table *table;
  int playerTurn_;

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

  //Signal handlers

  //ensures: updating seed
  void onButtonShuffle();

  //ensures: handle 13 image buttons
  void on_hand_clicked(int);

  //ensures: handle the quite button
  void onButtonQuit();
  
  //ensure: handle the Rage button
  void onButtonRage();


  public:
  // ctor
  // ensures: all widgets are initialized, and contruct a table class
  MainWindow();

  //dtor
  //modifies: this->m_Images, this-<hands_, this->table, and stack
  //ensures: all images and hands and table are destroyed, stack no longer exist, memory is freed
  virtual ~MainWindow();

  // ensures: based on the user reply in the dialogue, get the corresponding player type(human or cpu)
  // return: the corresponding string to symbolize the player type
  std::string humanCpu(int i);

  // ensures: pop out the message to notify the user has played an illegal card
  void errorMessage(std::string);

  // ensures: update the showing discard number after a certain player discard a card
  // modifies: this-discard
  void updateDiscard(int, int, int);

  // ensures: reset the Grid to the initial state
  // modifies: this->grid
  void resetGrid();

  //ensures: ensures: update the hands of the player
  //modifies: this->hands
  void updateHand(std::vector<Card>, int, std::vector<bool>);
 
  //ensures: based on the newly played card, update the image grid by chaging the nothing image to the played card image
  //modifies: this->Grid
  void updateImageGrid(std::vector<Card>);
  
  // ensures: print the player scores and winner
  void printMessage(std::string);

};

#endif
