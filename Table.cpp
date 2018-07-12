#include <vector>
#include "Table.h"
#include <random>
#include <algorithm>
#include <assert.h>
#include <iostream>
using namespace std;

// return decks
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

// dtor
//modifies: vector<player> players_ and stack
//  ensures: all players are destroyed, stack no longuer exist, memory is freed
Table::~Table() {
  for(int i=0; i<players_.size(); i++) {
    delete players_[i];
    players_[i] == nullptr;
  }
}

// modifies: convertPlayerId
void Table::setConvertPlayerId(int c){
	convertPlayerId = c;
}

void Table::setSeed(int i){
	seed = i;
}

// ctor
// requires: argc is at least 2, argv[1] exists
// ensures: Deck_ is shuffled, seed is argv[1], convertPlayerId is initialized as -1, score is initialized as {0,0,0,0}, players_ is intialized based on cin
Table::Table(MainWindow * m, int argc, char **argv):Deck_{initDeck()}, convertPlayerId{-1}, mainWindow_{m}{
	if(argc != 1){
		seed = strtol(argv[1], NULL, 10);
	}else{
		seed = 0;
	}
	vector<Card> v;
	playedCards_ = v;
	vector<int> score = {0,0,0,0};
	scores_ = score;
	shuffle();
	for(int i = 0; i < 4; i++){
		string c = mainWindow_->humanCpu(i);
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
	cout << "A new round begins. It's player " << searchFor7spade()+1 << "'s turn to play." << endl;
	notify();
}

// modifies: Deck_
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

// // return playedCards_
vector<Card> Table::getPlayedCard(){
	return playedCards_;
}

// ensures: player(observers) will be notified to play()
void Table::notify(){
	// TODO add parameters for update
	if(players_[turnPlayer_]->getHand().size() == 0){
		if(!beginRound()) {
			return;
		}

	}
	//if human player
	if(players_[turnPlayer_]->isHuman()){
		printTableState();
		mainWindow_->updateHand(players_[turnPlayer_]->getHand(), turnPlayer_);
	}else{//if cmoputer player
		players_[turnPlayer_]->play(0);
	}
}

// modifies: turnPlayer_
// ensures: after update turnPlayer_, notify the specific observer
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

// ensures: print ranks based on suits
void Table::printRanksOfSuit(Suit s){
	vector<int> played_rank;
	for(int i = 0; i < playedCards_.size(); i++){
		if(playedCards_[i].getSuit() == s){
			played_rank.push_back(rankToInt(playedCards_[i].getRank()));
		}
	}
	sort(played_rank.begin(),played_rank.end());
	for(int i = 0; i <played_rank.size(); i++){
		cout << " " << intToRankName(played_rank[i]);
	}
}

// ensures: print the table state
void Table::printTableState(){
	mainWindow_->updateImageGrid(playedCards_);
}

// modifies: vector<player> players_
// ensures: convert from humanPlayer to cpuPlayer
// requires: original converPlayerId is (0,3)
void Table::convertPlayer() {
  Player * del = players_[convertPlayerId];
  CpuPlayer * temp = new CpuPlayer(del->getHand(), del->getDiscard(), convertPlayerId, this);
  delete del;
  del = nullptr;
  players_[convertPlayerId] = temp;
  convertPlayerId = -1;
}

// modifies: playedCards_
// ensures: playedCards_ add one card at the end
void Table::pushCard(Card c) {
  playedCards_.push_back(c);
}

// ensures: print the whole Deck_
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

// return: score of specific player
// requires: the input parameter is in between (0,3)
// ensures: print discard cards
int Table::printDiscardAndGetPlayerNewScore(int c){
	int sum = 0;
	for(int i = 0; i < players_[c]->getDiscard().size(); i++){
		sum += rankToInt(players_[c]->getDiscard()[i].getRank());
		ss << " " << players_[c]->getDiscard()[i];
	}
	return sum;
}

// ensures: print all players' scores
// requires: players_ size is 4
void Table::printScore(){
	assert(players_.size()==4);
	ss.clear();
	ss.str(string());
	for(int i = 0; i < players_.size(); i++){
		ss << "Player " << i+1 << "'s discards:\n";
		int newScore = printDiscardAndGetPlayerNewScore(i);
		ss << "\n";
		ss << "Player " << i+1 << "'s score: " << scores_[i] << " + " << newScore << " = " << (scores_[i] + newScore) << "\n";
		scores_[i] = scores_[i] + newScore;
	}
	string s = ss.str();
	ss.clear();
	ss.str(string());
	mainWindow_->printMessage(s);
}

// returns: bool whether the game has been reseted or not
// ensures: a new round begin or the game ends
// modifies: Deck_ and players_ and playedCards_
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
      	ss.clear();
		ss.str(string());
        ss << "Player " << i+1 << " wins!";
        string s = ss.str();
        mainWindow_->printMessage(s);
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

// return: the index of player in players_ which has 7spade card
// requires: Deck_ contains 7spade
int Table::searchFor7spade(){
	for(int i = 0; i < Deck_.size(); i++){
		if (Deck_[i].getRank() == SEVEN && Deck_[i].getSuit() == SPADE){
			turnPlayer_ = i/13;
			return i/13;
		}
	}
}

// return: whether should begin new round or not
// ensures: if should begin new round, cout
bool Table::beginRound(){
	if(resetGame() == true){
		cout << "A new round begins. It's player " << searchFor7spade()+1 << "'s turn to play." << endl;
		turnPlayer_ = searchFor7spade();
		return true;
	} else {
		return false;
	}
}


int Table::getTurnPlayer(){
	cout << "in table";
	cout << turnPlayer_<<endl;
	return turnPlayer_;
}

void Table::errorMessage(string e){
	mainWindow_->errorMessage(e);
}

void Table::playerPlay(int n, int card) {
	players_[n]->play(card);
}