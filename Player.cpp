#include "Player.h"
#include <iostream>
#include <assert.h>
using namespace std;

///////////////////////////////////////////////////////////////////////////
//////////////////////////////  Player  ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////

vector<Card> Player::getLegalPlay() {
  vector<Card> tableCard = table_->getPlayedCard();
  vector<Card> legalPlay;
  for(int j=0; j<hand_.size(); j++) {
    for(int i=0; i<tableCard.size(); i++){
      if(hand_[j].getSuit() == tableCard[i].getSuit()) {
        if(hand_[j].getRank() - tableCard[i].getRank() == 1 || hand_[j].getRank() - tableCard[i].getRank() == -1){
          legalPlay.push_back(hand_[j]);
          j++;
          if(j == hand_.size()) return legalPlay;
          i = -1;
        }
      } else if (hand_[j].getRank() == SEVEN ) {
        legalPlay.push_back(hand_[j]);
        j++;
        if(j == hand_.size()) return legalPlay;
        i = -1;
      }
    }
  }
  return legalPlay;
}

Player::Player(std::vector<Card> hand, std::vector<Card> discard, int ID, Table * table) : hand_{hand}, discard_{discard}, playerID_{ID}, table_{table}
{
}

Player::~Player()
{
}

void Player::resetHand(vector<Card> hand)
{
  discard_.clear();
  hand_.clear();
  hand_ = hand;
}

void Player::update(Card card)
{
  table_->pushCard(card);
}

std::vector<Card> Player::getHand() {
  return hand_;
}

std::vector<Card> Player::getDiscard() {
  return discard_;
}

///////////////////////////////////////////////////////////////////////////
///////////////////////////  HumanPlayer  /////////////////////////////////
///////////////////////////////////////////////////////////////////////////

HumanPlayer::HumanPlayer(std::vector<Card> hand, std::vector<Card> discard, int ID, Table * table) : Player(hand, discard, ID, table)
{
}

HumanPlayer::~HumanPlayer()
{
}

void HumanPlayer::play() {
  table_->printTableState();
  vector<Card> legalPlay = getLegalPlay();
  cout << "Your hand:";
  for(int i=0; i<hand_.size(); i++){
    cout << " " << hand_[i];
  }
  cout << endl;
  //if 1st player with 7spades
  vector<Card> tableCard = table_->getPlayedCard();
  if(tableCard.size() == 0){
    for(int j=0; j<hand_.size(); j++) {
      if(hand_[j].getRank() == SEVEN && hand_[j].getSuit() == SPADE){
        legalPlay.push_back(hand_[j]);
      }
    }
  }
  cout << "Legal plays:";
  for(int i=0; i<legalPlay.size(); i++){
    cout << " " << legalPlay[i];
  }
  cout << endl;
  bool endturn = false;
  while(!endturn) {
    cout << ">";
    cin >> command_;
    if(command_.type == PLAY) {
      for(int i=0; i<legalPlay.size(); i++) {
        if(command_.card == legalPlay[i]) {
          cout << "Player " << playerID_+1 << " plays " << command_.card << "." << endl;
          endturn = true;
          update(command_.card);
          //delete card from hand_
          for(int j=0; j<hand_.size(); j++) {
            if(command_.card == hand_[j]){
              hand_.erase(hand_.begin() + j);
            }
          }
          break;
        }
      }
      if(!endturn) {
        cout << "This is not a legal play." << endl;
      }

    } else if (command_.type == DISCARD) {
      if(legalPlay.size() == 0) {
        discard_.push_back(command_.card);
        cout << "Player " << playerID_+1 << " discards " << command_.card << "." << endl;
        endturn = true;
        //delete card from hand_
        for(int j=0; j<hand_.size(); j++) {
          if(command_.card == hand_[j]){
            hand_.erase(hand_.begin() + j);
          }
        }
      } else {
        cout << "You have a legal play. You may not discard." << endl;
      }
    } else if (command_.type == DECK) {
      table_->printDeck();
    } else if (command_.type == QUIT) {
      return;
    } else if (command_.type == RAGEQUIT) {
      cout << "Player " << playerID_+1 << " ragequits. A computer will now take over." << endl;
      table_->setConvertPlayerId(playerID_);
      endturn = true;
    } else if (command_.type == BAD_COMMAND) {
      assert(false);
    }
  }
  table_->setTurnPlayer();
}

///////////////////////////////////////////////////////////////////////////
/////////////////////////////  CPUPlayer  /////////////////////////////////
///////////////////////////////////////////////////////////////////////////


CpuPlayer::CpuPlayer(std::vector<Card> hand, std::vector<Card> discard, int ID, Table * table) : Player(hand, discard, ID, table)
{
}

CpuPlayer::~CpuPlayer()
{
}

void CpuPlayer::play()
{
  vector<Card> legalPlay = getLegalPlay();
  //if 1st player with 7spades
  vector<Card> tableCard = table_->getPlayedCard();
  if(tableCard.size() == 0){
    for(int j=0; j<hand_.size(); j++) {
      if(hand_[j].getRank() == SEVEN && hand_[j].getSuit() == SPADE){
        legalPlay.push_back(hand_[j]);
      }
    }
  }
  if(legalPlay.size() == 0) {
    cout << "Player " << playerID_+1 << " discards " << hand_[0] << "." << endl;
    discard_.push_back(hand_[0]);
    hand_.erase(hand_.begin());
  } else {
    cout << "Player " << playerID_+1 << " plays " << legalPlay[0] << "." << endl;
    update(legalPlay[0]);
    //delete card from hand_
    for(int j=0; j<hand_.size(); j++) {
      if(legalPlay[0] == hand_[j]){
        hand_.erase(hand_.begin() + j);
      }
    }
  }
  table_->setTurnPlayer();
}
