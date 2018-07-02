#include <vector>
#include "Table.h"
#include <random>
#include <algorithm>
#include <assert.h>
#include <iostream>
using namespace std;

vector<Card> Table::initDeck(){
	vector<Suit> suits = {CLUB, DIAMOND, HEART, SPADE};
	vector<Rank> ranks = {ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING};
	vector<Card> decks;
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 13; j++){
			decks.push_back(Card(suits[i], ranks[j]));
		}
	}
	return decks;
}

Table::~Table() {
  for(int i=0; i<players_.size(); i++) {
    delete players_[i];
    players_[i] == nullptr;
  }
}

void Table::setConvertPlayerId(int c){
	convertPlayerId = c;
}

Table::Table(char **argv):Deck_{initDeck()}, seed{strtol(argv[1], NULL, 10)}, convertPlayerId{-1}{
	vector<Card> v;
	playedCards_ = v;
	vector<int> score = {0,0,0,0};
	scores_ = score;
	shuffle();
	for(int i = 0; i < 4; i++){
		cout << "Is player " << i+1 << " a human(h) or a computer(c)?" << endl;
		string c;
		cout << ">";
		cin >> c;
		vector <Card> initHand (Deck_.begin()+i*13, Deck_.begin()+13+i*13);
		if(c=="h"){
			HumanPlayer *temp = new HumanPlayer(initHand, v, i, this);
			players_.push_back(temp);
		} else if (c=="c"){
			CpuPlayer *temp = new CpuPlayer(initHand, v, i, this);
			players_.push_back(temp);
		} else {
			assert(false);
		}
	}
	cout << "A new round begins. It's player " << searchFor7spade() << "'s turn to play." << endl;
	notify();
}

void Table::shuffle(){
    static mt19937 rng(seed);

	int n = 52;

	while ( n > 1 ) {
		int k = (int) (rng() % n);
		--n;
		Card c = Deck_[n];
		Deck_[n] = Deck_[k];
		Deck_[k] = c;
	}
}

vector<Card> Table::getPlayedCard(){
	return playedCards_;
}


void Table::notify(){
	// TODO add parameters for update
	if(players_[turnPlayer_]->getHand().size() == 0){
		if(!beginRound()) {
			return;
		}

	}
	players_[turnPlayer_]->play();
}

void Table::setTurnPlayer(){
	if(convertPlayerId != -1){
		convertPlayer();
	}
	else{
		(turnPlayer_ == 3) ? (turnPlayer_ = 0) : (turnPlayer_++);
	}
	notify();
}


int rankToInt(Rank r){
	switch(r){
		case ACE:
			return 1;
		case TWO:
			return 2;
		case THREE:
			return 3;
		case FOUR:
			return 4;
		case FIVE:
			return 5;
		case SIX:
			return 6;
		case SEVEN:
			return 7;
		case EIGHT:
			return 8;
		case NINE:
			return 9;
		case TEN:
			return 10;
		case JACK:
			return 11;
		case QUEEN:
			return 12;
		case KING:
			return 13;
	}
}

string intToRankName(int c){
	switch(c){
		case 1:
		return "A";
		case 11:
		return "J";
		case 12:
		return "Q";
		case 13:
		return "K";
		default:
		return to_string(c);
	}
}

// will be used in print?? get the corresponsing suit, like spades, clubs based on the coresponding string
void Table::printRanksOfSuit(Suit s){
	vector<int> played_rank;
	for(int i = 0; i < playedCards_.size(); i++){
		if(playedCards_[i].getSuit() == s){
			played_rank.push_back(rankToInt(playedCards_[i].getRank()));
		}
	}
	sort(played_rank.begin(),played_rank.end());
	// vector<string> played_rank_output;
	for(int i = 0; i <played_rank.size(); i++){
		cout << " " << intToRankName(played_rank[i]);
		// played_rank_output.append(intToRankName(played_rank[i]));
	}
	// return played_rank_output;
}

void Table::printTableState(){
	cout << "Cards on the table:" << endl;
	cout << "Clubs:";
	printRanksOfSuit(CLUB);
	cout << endl;
	cout << "Diamonds:";
	printRanksOfSuit(DIAMOND);
	cout << endl;
	cout << "Hearts:";
	printRanksOfSuit(HEART);
	cout << endl;
	cout << "Spades:";
	printRanksOfSuit(SPADE);
	cout << endl;
}

void Table::convertPlayer() {
  Player * del = players_[convertPlayerId];
  CpuPlayer * temp = new CpuPlayer(del->getHand(), del->getDiscard(), convertPlayerId, this);
  delete del;
  del = nullptr;
  players_[convertPlayerId] = temp;
  convertPlayerId = -1;
}

void Table::pushCard(Card c) {
  playedCards_.push_back(c);
}


void Table::printDeck(){
	assert(Deck_.size() == 52);
	for(int i = 0 ; i < Deck_.size(); i++){
		cout << Deck_[i];
		if(i%13 == 12){
			cout << endl;
		}
		else{
			cout<< " ";
		}
	}
}

int Table::printDiscardAndGetPlayerNewScore(int c){
	int sum = 0;
	for(int i = 0; i < players_[c]->getDiscard().size(); i++){
		sum += rankToInt(players_[c]->getDiscard()[i].getRank());
		cout << " " << players_[c]->getDiscard()[i];
	}
	return sum;
}

void Table::printScore(){
	assert(players_.size()==4);
	for(int i = 0; i < players_.size(); i++){
		cout << "Player " << i+1 << "'s discards:";
		int newScore = printDiscardAndGetPlayerNewScore(i);
		cout << endl;
		cout << "Player " << i+1 << "'s score is " << scores_[i] << " + " << newScore << " = " << (scores_[i] + newScore) << endl;
		scores_[i] = scores_[i] + newScore;
	}

}


bool Table::resetGame() {
  printScore();
  bool end = false;
  int smallest = scores_[0];
  for(int i=0; i<scores_.size(); i++) {
    if(scores_[i] < smallest) {
      smallest = scores_[i];
    }
    if(scores_[i] >=80) {
      end = true;
    }
  }
  if(end){
    for(int i=0; i<scores_.size(); i++) {
      if(scores_[i] == smallest) {
        cout << "Player " << i+1 << " wins!" << endl;
      }
    }
    return false;
  }
  shuffle();
  playedCards_.clear();
  for(int i=0; i<players_.size(); i++) {
    vector<Card> temp(Deck_.begin()+i*13, Deck_.begin()+i*13+13);
    players_[i]->resetHand(temp);
  }
  return true;
}

int Table::searchFor7spade(){
	for(int i = 0; i < Deck_.size(); i++){
		if (Deck_[i].getRank() == SEVEN && Deck_[i].getSuit() == SPADE){
			turnPlayer_ = i/13;
			return i/13;
		}
	}
}

bool Table::beginRound(){
	if(resetGame() == true){
		cout << "A new round begins. It's player " << searchFor7spade()+1 << "'s turn to play." << endl;
		turnPlayer_ = searchFor7spade();
		return true;
	} else {
		return false;
	}
}
