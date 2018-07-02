#ifndef Table_H
#define Table_H

#include <vector>
#include "Player.h"
#include "Card.h"

class Table
{
  std::vector<Card> cards_;
  std::vector<Player> players_;
  int turn_;
public:
  void notify();
  void setTurn();
  void getDeck();
  void pushCard(Card);
}
