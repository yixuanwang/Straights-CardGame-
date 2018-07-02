#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "Card.h"
#include "Command.h"
#include "Table.h"

class Player
{
  Table * table_;
protected:
  std::vector<Card> hand_;
  std::vector<Card> discard_;
  //std::vector<Card> legalCard_;
  int playerID_;
  std::vector<Card> getLegalPlay();
public:
  Player(std::vector<Card>, std::vector<Card>, int, Table *);
  virtual ~Player();
  void resetHand(std::vector<Card>);
  virtual void play() = 0;
  void update(Card card);
}

class HumanPlayer : public Player
{
  Command command_;
public:
  HumanPlayer(std::vector<Card>, std::vector<Card>, int, Table *);
  virtual ~HumanPlayer();
  void play() override;
}

class CpuPlayer : public Player
{
public:
  CpuPlayer(std::vector<Card>, std::vector<Card>, int, Table *);
  virtual ~CpuPlayer();
  void play() override;
}
