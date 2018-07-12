#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "Card.h"
#include "Command.h"
#include "Table.h"

class Table;

class Player
{
protected:
  Table * table_;
  std::vector<Card> hand_;
  std::vector<Card> discard_;
  //std::vector<Card> legalCard_;
  int playerID_;
  //helper functions
  /*
  returns: a vector containing a list of legal plays of the player
  */
  std::vector<Card> getLegalPlay();
public:
  virtual bool isHuman() =0;
  /*
  Constructor
  ensures: Player is initialized with handcard, discardcards, playerID and a table
  */
  Player(std::vector<Card>, std::vector<Card>, int, Table *);
  /*
  Destructor
  modifies: stack
  ensures: stack no longuer exist, memory is freed
  */
  virtual ~Player();
  /*
  Accessor
  returns: Players current hand card
  */
  std::vector<Card> getHand();
  /*
  Accessor
  returns: Players current discard pile
  */
  std::vector<Card> getDiscard();
  /*
  modifies: this->hand_ and this->discard_
  ensures: this->discard is emptied and a new hand is distributed
  */
  void resetHand(std::vector<Card>);
  /*
  modifies: this->table_
  ensures: a card get added to the table pile
  */
  void update(Card card);

  virtual void play(int) =0;
};

class HumanPlayer : public Player
{
  Command command_;
public:
  bool isHuman() override;

  /*
  Constructor
  ensures: HumanPlayer is initialized with handcard, discardcards, playerID and a table
  */
  HumanPlayer(std::vector<Card>, std::vector<Card>, int, Table *);
  /*
  Destructor
  modifies: stack
  ensures: stack no longuer exist, memory is freed
  */
  virtual ~HumanPlayer();
  /*
  modifies: this->hand_, this->discard-, this->table_, cin
  ensures: a valid play has been made and this player's turn is ended
  requires: hand_ is not empty
  */
  void play(int) override;

};

class CpuPlayer : public Player
{
public:
  bool isHuman() override;

  /*
  Constructor
  ensures: CpuPlayer is initialized with handcard, discardcards, playerID and a table
  */
  CpuPlayer(std::vector<Card>, std::vector<Card>, int, Table *);
  /*
  Destructor
  modifies: stack
  ensures: stack no longuer exist, memory is freed
  */
  virtual ~CpuPlayer();
  /*
  modifies: this->hand_, this->discard-, this->table_
  ensures: a valid play has been made and this player's turn is ended
  requires: hand_ is not empty
  */
  void play(int) override;
};

#endif
