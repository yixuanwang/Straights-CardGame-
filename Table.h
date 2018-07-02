#ifndef Table_H
#define Table_H

#include <vector>
#include "Player.h"
#include "Card.h"

class Table
{
  std::vector<Card> playedCards_;
  std::vector<Card> Deck_;
  std::vector<Player*> players_;
  static int turnPlayer_;
  int convertPlayerId;
  int seed;
  std::vector<Card> initDeck();
  std::vector<int> scores_;

  void convertPlayer();
public:
  std::vector<Card> getPlayedCard();
  void notify();

  void setConvertPlayerId(int);
  static void setTurnPlayer(); // UPDATE turnPlayer
  void printDeck();
  void pushCard(Card);
  void shuffle();
  void printScore();
  void resetGame(); //when 
  void beginRound(); // check 7 spade and set turn
  void printTableState();
}
