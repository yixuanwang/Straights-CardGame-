#include "Player.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////
//////////////////////////////  Player  ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////

vector<Card> Player::getLegalPlay() {
  vector<Card> tableCard = table->getPlayedCard();
  vector<Card> legalPlay;
  for(int i=0; i<tableCard.size(); i++){
    for(int j=0; j<hand_.size(); j++) {
      if(hand_[j].getSuit() == tableCard[i].getSuit()) {
        if(hand_[j].getRank() == tableCard[i].getRank() || hand_[j].getRank() == tableCard[i].getRank() +1 || hand_[j].getRank() == tableCard[i].getRank() -1){
          legalPlay.push_back(hand_[j]);
        }
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
  table->pushCard(card);
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
  table->printTableState();
  vector<Card> legalPlay = getLegalPlay();
  cout << "Your hand:";
  for(int i=0; i<hand_; i++){
    cout << " " << hand_[i];
  }
  cout << endl;
  cout << "Legal plays:";
  for(int i=0; i<legalPlay; i++){
    cout << " " << legalPlay[i];
  }
  cout << endl;
  bool endturn = false;
  while(!endturn) {
    cin >> command_;
    if(command_.type == PLAY) {
      for(int i=0; i<legalPlay.size(); i++) {
        if(command_.card == legalPlay[i]) {
          cout << "Player " << playerID_ << " plays " << command_.card << "." << endl;
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
        cout << "Player " << playerID_ << " discards " << command_.card << "." << endl;
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
      table->printDeck();
    } else if (command_.type == QUIT) {
      return;
    } else if (command_.type == RAGEQUIT) {
      cout << "Player " << playerID_ << " ragequits. A computer will now take over." << endl;
      table->setConvertPlayerId(playerID_);
      endturn = true;
    } else if (command_.type == BAD_COMMAND) {
      assert(false);
    }
  }
  table->setTurnPlayer();
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
  if(legalPlay.size() == 0) {
    cout << "Player " << playerID_ << " discards " << hand_[0] << "." << endl;
    update(hand_[0]);
    discard_.push_back(hand_[0]);
    hand_.erase(hand_.begin());
  } else {
    cout << "Player " << playerID_ << " plays " << legalPlay[0] << "." << endl;
    //delete card from hand_
    for(int j=0; j<hand_.size(); j++) {
      if(legalPlay[0] == hand_[j]){
        hand_.erase(hand_.begin() + j);
      }
    }
  }
}
