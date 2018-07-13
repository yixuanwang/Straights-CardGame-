#ifndef Table_H
#define Table_H

#include <vector>
#include <sstream>
#include "Player.h"
#include "Card.h"
#include "MainWindow.h"

class MainWindow;
class Player;

class Table
{
  std::vector<Card> playedCards_;
  std::vector<Card> Deck_;
  std::vector<Player*> players_;
  int convertPlayerId;
  int seed;
  std::vector<int> scores_;
  MainWindow * mainWindow_;
  int turnPlayer_;
  std::stringstream ss;

// return decks
  std::vector<Card> initDeck();

// modifies: this->players_
// ensures: convert from humanPlayer to cpuPlayer
// requires: original converPlayerId is (0,3)
  void convertPlayer();

// ensures: print ranks based on suits
  void printRanksOfSuit(Suit);

// return: score of specific player
// requires: the input parameter is in between (0,3)
// ensures: print discard cards
  int printDiscardAndGetPlayerNewScore(int);


  // ensures: print all players' scores
// requires: players_ size is 4
  void printScore();

  // return: the index of player in players_ which has 7spade card
// requires: Deck_ contains 7spade
  int searchFor7spade();

  // return: whether should begin new round or not
// ensures: if should begin new round, cout
  bool beginRound(); // check 7 spade and set turn
public:
  /*
  ensures: updateDiscard of the mainWindow is called
  */
  void updateDiscard(int);
  /*
  ensures: specific player's play function is called
  */
  void playerPlay(int, int);
// // return this->playedCards_
  std::vector<Card> getPlayedCard();

// ensures: player(observers) will be notified to play()
  void notify();

  // bool isValid(int, int);

// ctor
// ensures: this->Deck_ is shuffled, seed is argv[1], this->convertPlayerId is initialized as -1, this->scores_ is initialized as {0,0,0,0}, this->players_ is intialized based on cin
Table(MainWindow *, int argc = 1, char ** argv = nullptr);

// dtor
//modifies: this->players_ and stack
//  ensures: all players are destroyed, stack no longer exist, memory is freed
  virtual ~Table();

// modifies: this->convertPlayerId
  void setConvertPlayerId(int);

  // modifies: this->turnPlayer_
// ensures: after update this->turnPlayer_, notify the specific observer
  void setTurnPlayer();

// ensures: print the whole Deck_
  void printDeck();

  // modifies: this->playedCards_
// ensures: this->playedCards_ add one card at the end
  void pushCard(Card);

// modifies: this->Deck_
  void shuffle();

  // returns: bool whether the game has been reseted or not
// ensures: a new round begin or the game ends
// modifies: this->Deck_ and this->players_ and this->playedCards_
  bool resetGame();

// ensures: print the table state
  void printTableState();

// ensures a new seed is set for shuffling cards
// modifies: seed
  void setSeed(int);

// returns: turnPlayer_'s value
  int getTurnPlayer();

// ensures: mainwindow's errormessage function is called
  void errorMessage(std::string);

};
#endif
