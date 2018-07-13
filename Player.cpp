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


bool Player::isValid(int n) {
  if(n>=hand_.size()) {
    return false;
  }
  //get legal plays
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
  if(legalPlay.size() == 0){
    return true;
  }
  for(int i=0; i<legalPlay.size(); i++) {
    if(hand_[n] == legalPlay[i]) {
      return true;
    }
  }
  return false;
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

void HumanPlayer::play(int n) {
  //get legal plays
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
  bool endturn = false;
  // while(!endturn) {
  if(legalPlay.size() != 0){
    for(int i=0; i<legalPlay.size(); i++) {
      if(hand_[n] == legalPlay[i]) {
        endturn = true;
        update(hand_[n]);
        //delete card from hand_
        hand_.erase(hand_.begin() + n);
        break;
      }
    }
    if(!endturn) {
      table_->errorMessage("This is not a legal play");
    }
  } else if(legalPlay.size() == 0) {
    discard_.push_back(hand_[n]);
    endturn = true;
    //delete card from hand_
    hand_.erase(hand_.begin() + n);
    //update discard number on GUI
    table_->updateDiscard(discard_.size());
  }
  if(endturn){
    table_->setTurnPlayer();
  }
}

bool HumanPlayer::isHuman(){
  return true;
}

// bool HumanPlayer::isValid(int n) {
//   //get legal plays
//   vector<Card> legalPlay = getLegalPlay();
//   //if 1st player with 7spades
//   vector<Card> tableCard = table_->getPlayedCard();
//   if(tableCard.size() == 0){
//     for(int j=0; j<hand_.size(); j++) {
//       if(hand_[j].getRank() == SEVEN && hand_[j].getSuit() == SPADE){
//         legalPlay.push_back(hand_[j]);
//       }
//     }
//   }

//   for(int i=0; i<legalPlay.size(); i++) {
//     if(hand_[n] == legalPlay[i]) {
//       return true;
//     }
//   }
//   return false;
// }
///////////////////////////////////////////////////////////////////////////
/////////////////////////////  CPUPlayer  /////////////////////////////////
///////////////////////////////////////////////////////////////////////////


CpuPlayer::CpuPlayer(std::vector<Card> hand, std::vector<Card> discard, int ID, Table * table) : Player(hand, discard, ID, table)
{
}

CpuPlayer::~CpuPlayer()
{
}

void CpuPlayer::play(int n)
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
    //cout << "Player " << playerID_+1 << " discards " << hand_[0] << "." << endl;
    discard_.push_back(hand_[0]);
    hand_.erase(hand_.begin());
    table_->updateDiscard(discard_.size());
  } else {
    //cout << "Player " << playerID_+1 << " plays " << legalPlay[0] << "." << endl;
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

bool CpuPlayer::isHuman(){
  return false;
}
