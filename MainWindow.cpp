#include "MainWindow.h"
#include <sstream>
using namespace std;

MainWindow::MainWindow()
: m_Box(Gtk::ORIENTATION_VERTICAL),
  m_ButtonShuffle("Shuffle"),
  m_ButtonQuit("Quit"),
  m_ButtonRage("Rage!"),
  m_FrameHand("Your Hand"),
  m_Frame1("Player 1"),
  m_Frame2("Player 2"),
  m_Frame3("Player 3"),
  m_Frame4("Player 4"),
  m_FrameTurn("Player x's turn"),
  m_FrameTable("Cards on the table")
{
  table = new Table(this);
  for(int i = 0; i < 52; i++){
    m_Images.push_back(new Gtk::Image("img/nothing.png"));
  }
  set_title("Straights");
  add(m_Box);

  //Set Sizes
  m_ButtonShuffle.set_size_request(340, 32);
  m_ButtonQuit.set_size_request(340, 32);
  m_EntrySeed.set_size_request(35, 32);


  //Add buttons
  m_Box.pack_start(m_ButtonBox, Gtk::PACK_SHRINK);
  m_ButtonBox.pack_start(m_ButtonShuffle, Gtk::PACK_SHRINK);
  m_ButtonBox.add(m_EntrySeed);
  m_ButtonBox.pack_start(m_ButtonQuit, Gtk::PACK_SHRINK);
  m_ButtonBox.set_layout(Gtk::BUTTONBOX_END);


  m_Box.pack_start(m_FrameTable, Gtk::PACK_SHRINK);

  m_FrameTable.add(m_Grid);
  for(int i=0; i < 4; i++){
    for(int j=0; j<13; j++){
      m_Grid.attach(*m_Images[i*13+j],j,i,1,1);
      if(j!=12){
        m_Images[i*13+j]->set_margin_right(40);
      }
      m_Images[i*13+j]->set_margin_bottom(10);
    }
  }

  //Rage Button
  m_Box.pack_start(m_FrameTurn);

  m_FrameTurn.add(m_ButtonRage);

  //Players section
  m_Box.pack_start(m_PlayerGrid, Gtk::PACK_EXPAND_WIDGET);
  m_Frame1.set_size_request(300,50);
  m_PlayerGrid.attach(m_Frame1,0,0,10,1);
  // m_Box.pack_start(m_Frame1, Gtk::PACK_SHRINK);
  m_Point1.set_label("0 points\n0 discards");
  m_Frame1.add(m_Point1);

  m_PlayerGrid.attach(m_Frame2,12,0,1,1);
  m_Frame2.set_size_request(300,50);
  // m_Box.pack_start(m_Frame2, Gtk::PACK_SHRINK);
  m_Point2.set_label("0 points\n0 discards");
  m_Frame2.add(m_Point2);

  m_PlayerGrid.attach(m_Frame3,13,0,1,1);
  m_Frame3.set_size_request(300,50);
  // m_Box.pack_start(m_Frame3, Gtk::PACK_SHRINK);
  m_Point3.set_label("0 points\n0 discards");
  m_Frame3.add(m_Point3);

  m_PlayerGrid.attach(m_Frame4,14,0,1,1);
  m_Frame4.set_size_request(300,50);
  // m_Box.pack_start(m_Frame4, Gtk::PACK_SHRINK);
  m_Point4.set_label("0 points\n0 discards");
  m_Frame4.add(m_Point4);

  m_Box.pack_start(m_FrameHand, Gtk::PACK_EXPAND_WIDGET);
  m_FrameHand.add(m_Hand);
  for(int i=0; i<13; i++){
    ImageButton *temp = new ImageButton("img/nothing.png");
    hand_.push_back(temp);
    m_Hand.pack_start(*hand_[i]);
  }
  m_Hand.set_layout(Gtk::BUTTONBOX_START);

  //Connect signal
  m_ButtonShuffle.signal_clicked().connect(sigc::mem_fun(*this,
              &MainWindow::onButtonShuffle) );
  m_ButtonQuit.signal_clicked().connect(sigc::mem_fun(*this,
              &MainWindow::onButtonQuit) );
  m_ButtonRage.signal_clicked().connect(sigc::mem_fun(*this,
              &MainWindow::onButtonRage) );

  hand_[0]->signal_clicked().connect(sigc::mem_fun(*this,
              &MainWindow::onButtonHand0) );
  hand_[1]->signal_clicked().connect(sigc::mem_fun(*this,
                &MainWindow::onButtonHand1) );
  hand_[2]->signal_clicked().connect(sigc::mem_fun(*this,
                &MainWindow::onButtonHand2) );
  hand_[3]->signal_clicked().connect(sigc::mem_fun(*this,
                &MainWindow::onButtonHand3) );
  hand_[4]->signal_clicked().connect(sigc::mem_fun(*this,
                &MainWindow::onButtonHand4) );
  hand_[5]->signal_clicked().connect(sigc::mem_fun(*this,
                &MainWindow::onButtonHand5) );
  hand_[6]->signal_clicked().connect(sigc::mem_fun(*this,
                &MainWindow::onButtonHand6) );
  hand_[7]->signal_clicked().connect(sigc::mem_fun(*this,
                &MainWindow::onButtonHand7) );
  hand_[8]->signal_clicked().connect(sigc::mem_fun(*this,
                &MainWindow::onButtonHand8) );
  hand_[9]->signal_clicked().connect(sigc::mem_fun(*this,
                &MainWindow::onButtonHand9) );
  hand_[10]->signal_clicked().connect(sigc::mem_fun(*this,
                &MainWindow::onButtonHand10) );
  hand_[11]->signal_clicked().connect(sigc::mem_fun(*this,
                &MainWindow::onButtonHand11) );
  hand_[12]->signal_clicked().connect(sigc::mem_fun(*this,
                &MainWindow::onButtonHand12) );

  show_all_children();
}

MainWindow::~MainWindow() {
  //delete table
  //delete vector of hand button
}

void MainWindow::onButtonShuffle()
{
  // cout << "clicked or not? ";
  // cout << m_ButtonShuffle.clicked;
  string seed = m_EntrySeed.get_text();
  stringstream geek(seed);
  int x = 0;
  geek >> x;
  table->setSeed(x);
}

void MainWindow::onButtonQuit()
{
  hide();
}

void MainWindow::onButtonRage()
{
  table->setConvertPlayerId(playerTurn_);
  table->setTurnPlayer();
}

void MainWindow::onButtonHand0(){
  table->playerPlay(playerTurn_, 0);
}
void MainWindow::onButtonHand1(){
  table->playerPlay(playerTurn_, 1);
}
void MainWindow::onButtonHand2(){
  table->playerPlay(playerTurn_, 2);
}
void MainWindow::onButtonHand3(){
  table->playerPlay(playerTurn_, 3);
}
void MainWindow::onButtonHand4(){
  table->playerPlay(playerTurn_, 4);
}
void MainWindow::onButtonHand5(){
  table->playerPlay(playerTurn_, 5);
}
void MainWindow::onButtonHand6(){
  table->playerPlay(playerTurn_, 6);
}
void MainWindow::onButtonHand7(){
  table->playerPlay(playerTurn_, 7);
}
void MainWindow::onButtonHand8(){
  table->playerPlay(playerTurn_, 8);
}
void MainWindow::onButtonHand9(){
  table->playerPlay(playerTurn_, 9);
}
void MainWindow::onButtonHand10(){
  table->playerPlay(playerTurn_, 10);
}
void MainWindow::onButtonHand11(){
  table->playerPlay(playerTurn_, 11);
}
void MainWindow::onButtonHand12(){
  table->playerPlay(playerTurn_, 12);
}

void MainWindow::updateHand(vector<Card> playerHand, int turnPlayer_){
  playerTurn_ = turnPlayer_;
  m_FrameTurn.set_label("Player "+ to_string(turnPlayer_+1) +"'s turn");
  for(int i=0; i<hand_.size(); i++){
    delete hand_[i];
  }
  hand_.clear();
  for(int i=0; i<playerHand.size(); i++){
    ImageButton *temp = new ImageButton("img/"+playerHand[i].getString()+".png");
    hand_.push_back(temp);
    m_Hand.pack_start(*hand_[i]);
  }
  for(int i = playerHand.size(); i < 13; i++){
    ImageButton *temp = new ImageButton("img/nothing.png");
    hand_.push_back(temp);
    m_Hand.pack_start(*hand_[i]);
  }
  m_Hand.set_layout(Gtk::BUTTONBOX_START);

  hand_[0]->signal_clicked().connect(sigc::mem_fun(*this,
              &MainWindow::onButtonHand0) );
  hand_[1]->signal_clicked().connect(sigc::mem_fun(*this,
                &MainWindow::onButtonHand1) );
  hand_[2]->signal_clicked().connect(sigc::mem_fun(*this,
                &MainWindow::onButtonHand2) );
  hand_[3]->signal_clicked().connect(sigc::mem_fun(*this,
                &MainWindow::onButtonHand3) );
  hand_[4]->signal_clicked().connect(sigc::mem_fun(*this,
                &MainWindow::onButtonHand4) );
  hand_[5]->signal_clicked().connect(sigc::mem_fun(*this,
                &MainWindow::onButtonHand5) );
  hand_[6]->signal_clicked().connect(sigc::mem_fun(*this,
                &MainWindow::onButtonHand6) );
  hand_[7]->signal_clicked().connect(sigc::mem_fun(*this,
                &MainWindow::onButtonHand7) );
  hand_[8]->signal_clicked().connect(sigc::mem_fun(*this,
                &MainWindow::onButtonHand8) );
  hand_[9]->signal_clicked().connect(sigc::mem_fun(*this,
                &MainWindow::onButtonHand9) );
  hand_[10]->signal_clicked().connect(sigc::mem_fun(*this,
                &MainWindow::onButtonHand10) );
  hand_[11]->signal_clicked().connect(sigc::mem_fun(*this,
                &MainWindow::onButtonHand11) );
  hand_[12]->signal_clicked().connect(sigc::mem_fun(*this,
                &MainWindow::onButtonHand12) );

  show_all_children();
}

void MainWindow::updatePlayer(int player, int discard, int score) {

}

string MainWindow::humanCpu(int i){
  Gtk::MessageDialog dialog(*this, "Human or Computer?",
          false /* use_markup */, Gtk::MESSAGE_QUESTION,
          Gtk::BUTTONS_YES_NO);
  string temp = "Is player " + to_string(i+1) + " a human?";
  dialog.set_secondary_text(temp);

  int result = dialog.run();

  //Handle the response:
  switch(result) {
    case(Gtk::RESPONSE_YES): {
      return "h";
      break;
    }
    case(Gtk::RESPONSE_NO): {
      return "c";
      break;
    }
    default: {
      return "";
      break;
    }
  }
}

void MainWindow::errorMessage(string e){
  Gtk::MessageDialog dialog(*this, "Ilegal play",
          false /* use_markup */, Gtk::MESSAGE_ERROR);
  dialog.set_secondary_text(e);
  dialog.run();
}

// int MainWindow::getClickedCard(){
//   return clickedCard_;
// }

int rankToInts(Rank r){
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

int suitToInt(Suit s){
  switch(s){
    case CLUB:
    return 0;
    case DIAMOND:
    return 1;
    case HEART:
    return 2;
    case SPADE:
    return 3;
  }
}

void MainWindow::updateImageGrid(vector<Card> playedCards_){
  int c = 0;
  if(m_Images.size() == 0){
    for(int i = 0; i < 52; i++){
      m_Images.push_back(new Gtk::Image("img/nothing.png"));
    }
  }
  for(int i = 0; i< playedCards_.size(); i++){
    cout << c++ << endl;
    int x = rankToInts(playedCards_[i].getRank()) -1;
    int y = suitToInt(playedCards_[i].getSuit());
    string s = "img/"+playedCards_[i].getString()+".png";
    cout << m_Images.size() << endl;
    delete m_Images[y*13+x];
    m_Images[y*13+x] = new Gtk::Image(s);
    m_Grid.attach(*m_Images[y*13+x],x,y,1,1);
    if(x!=12){
      m_Images[y*13+x]->set_margin_right(40);
    }
    m_Images[y*13+x]->set_margin_bottom(10);
  }
  // for(int i=0; i < 4; i++){
  //   for(int j=0; j<13; j++){
  //     m_Grid.attach(*m_Images[i*13+j],j,i,1,1);
  //     if(j!=12){
  //       m_Images[i*13+j]->set_margin_right(40);
  //     }
  //     m_Images[i*13+j]->set_margin_bottom(10);
  //   }
  // }
  show_all_children();
}

void MainWindow::printMessage(string s) {
  Gtk::MessageDialog dialog(*this, "Score");
  dialog.set_secondary_text(s);
  dialog.run();
}
