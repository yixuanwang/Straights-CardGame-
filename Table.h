#ifndef Table_H
#define Table_H

#include <vector>
#include "Player.h"
#include "Card.h"

class Player;

class Table
{
  std::vector<Card> playedCards_;
  std::vector<Card> Deck_;
  std::vector<Player*> players_;
  int turnPlayer_;
  int convertPlayerId;
  int seed;
  std::vector<Card> initDeck();
  std::vector<int> scores_;

  void convertPlayer();
  void printRanksOfSuit(Suit);
  int printDiscardAndGetPlayerNewScore(int);
  void printScore();
  int searchFor7spade();
  bool beginRound(); // check 7 spade and set turn
public:
  std::vector<Card> getPlayedCard();
  void notify();
  Table(char **);
  virtual ~Table();
  void setConvertPlayerId(int);
  void setTurnPlayer(); // UPDATE turnPlayer
  void printDeck();
  void pushCard(Card);
  void shuffle();
  bool resetGame(); //when
  void printTableState();
};
#endif
