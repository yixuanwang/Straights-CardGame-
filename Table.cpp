#include <vector>
#include "Table.h"
#include <random>
#include <algorithm>
using namespace std;

vector<Card> Table::initDeck(){
	vector<Suit> suits[4] = {CLUB, DIAMOND, HEART, SPADE};
	vector<Rank> ranks[13] = {ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING};
	vector<Card> decks;
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 13; j++){
			decks.append(Card(suits[i], ranks[j])); 
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

Table::Table(char **argv):playedCards_{null}, Deck_{initDeck()}, seed{(int)argv[1]-48}, convertPlayerId{-1}, scores_{vector<int> v(4,0)}{
	shuffle();
	for(int i = 0; i < 4; i++){
		vector<Card> temp ( Deck_.begin()+i*13, Deck_.begin()+i*13+12);
		vecrtor<Card> n; 
		players_.append(new Player(temp, n, i));
	}
}

void Table::shuffle(){
    static mt19937 rng(seed);

	int n = 52;

	while ( n > 1 ) {
		int k = (int) (rng() % n);
		--n;
		Card c = Deck_;
		Deck_[n] = Deck_[k];
		Deck_[k] = c;
	}
}

vector<Card> Table::getPlayedCard(){
	return playedCards_;
}


void Table::notify(){
	// TODO add parameters for update
	players_[turnPlayer_].play();
}
static void Table::setTurnPlayer(){
	if(convertPlayerId != -1){
		convertPlayer();
	}
	else{
		(turnPlayer_ == 3) ? (turnPlayer_ = 0) : (turnPlayer_++);
	}
	
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
			return 7:
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
void printRanksOfSuit(Suit s){
	vector<int> played_rank; 
	for(int i = 0; i < playedCards_.size(); i++){
		if(playedCards_[i].getSuit() == s){
			played_rank.append(rankToInt(playedCards_[i].getRank()));
		}
	}
	sort(played_rank.begin(),played_rank.end());
	// vector<string> played_rank_output;
	for(i = 0; i <played_rank.size(); i++){
		cout << " " << intToRankName(played_rank[i]);
		// played_rank_output.append(intToRankName(played_rank[i]));
	}
	// return played_rank_output;
}

void Table::printTableState(){
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
  HumanPlayer * del = players_[convertPlayerId];
  CpuPlayer * temp = new CpuPlayer(del->getHand(), del->getDiscard(), convertPlayerId, this);
  delete del;
  del = nullptr;
  players_[convertPlayerId] = temp;
  convertPlayerId = -1;
}

void Table::pushCard(Card c) {
  playedCards_.push_back(c);
}


void printDeck(){
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
	
int printDiscardAndGetPlayerNewScore(int c){
	int sum = 0;
	for(int i = 0; i < players_[c]->getDiscard().size(); i++){
		sum += rankToInt(players_[c]->getDiscard()[i]);
		cout << " " << players_[c]->getDiscard()[i];
	}
	return sum;
}

void printScore(){
	assert(players_.size()==4);
	for(int i = 0; i < players_.size(); i++){
		cout << "Player" << i << "'s discards: ";
		int newScore = printDiscardAndGetPlayerNewScore(i);
		cout << endl;
		cout << "Player" << i << "'s score is " << scores_[i] << " + " << newScore << " = " << (scores_[i] + newScore) << endl;
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
        cout << "Player " << i << " wins!" << endl;
      }
    }
    return false;
  }
  shuffle();
  playedCards_.clear();
  for(int i=0; i<players_.size(); i++) {
    vector<Card> temp(Deck_.begin()+i, Deck_.begin()+1+12);
    players_[i].resetHand(temp);
  }
  return true;
}

int searchFor7spade(){
	for(int i = 0; i < Deck_.size(); i++){
		if (Deck_[i].getRank() == SEVEN && Deck_[i].getSuit() == SPADE){
			turnPlayer_ = i/13;
			return i/13;
		}
	}
}

void beginRound(){
	if(resetGame() == True){
		cout << "A new round begins. It's player " << searchFor7spade() << "'s turn to play." << endl;
		turnPlayer_ = 0;
	}
}