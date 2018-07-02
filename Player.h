#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "Card.h"
#include "Command.h"
#include "Table.h"

class Player
{
  Subject * table_;
protected:
  std::vector<Card> hand_;
  std::vector<Card> discard_;
  //std::vector<Card> legalCard_;
  int playerID_;
  std::vector<Card> getLegalPlay();
public:
  Player(std::vector<Card>, std::vector<Card>, int);
  virtual ~Player();
  virtual void play() = 0;
  virtual void update() = 0;
}

class HumanPlayer : public Player
{
  Command command_;
public:
  HumanPlayer(std::vector<Card>, std::vector<Card>, int);
  virtual ~HumanPlayer();
  void play() override;
  void update() override;
}

class CpuPlayer : public Player
{
public:
  CpuPlayer(std::vector<Card>, std::vector<Card>, int);
  virtual ~CpuPlayer();
  void play() override;
  void update() override;
}
