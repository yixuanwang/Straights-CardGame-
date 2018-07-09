#include "MainWindow.h"

using namespace std;

MainWindow::MainWindow()
: m_Box(Gtk::ORIENTATION_VERTICAL),
  m_ButtonShuffle("Shuffle"),
  m_ButtonQuit("Quit")

{
  // m_Image = Gtk::Image("img/0_4.png");
  // m_Image2 = Gtk::Image("img/1_4.png");

  for(int i = 0; i < 52; i++){
    m_Images.push_back(Gtk::Image("img/nothing.png"));
  }

  set_title("Straights");
  add(m_Box);

  //Set Sizes
  m_ButtonShuffle.set_size_request(305, 32);
  m_ButtonQuit.set_size_request(305, 32);
  m_EntrySeed.set_size_request(35, 32);


  //Add buttons
  m_Box.pack_start(m_ButtonBox, Gtk::PACK_SHRINK);
  m_ButtonBox.pack_start(m_ButtonShuffle, Gtk::PACK_SHRINK);
  m_ButtonBox.add(m_EntrySeed);
  m_ButtonBox.pack_start(m_ButtonQuit, Gtk::PACK_SHRINK);
  m_ButtonBox.set_layout(Gtk::BUTTONBOX_END);

  m_Box.pack_start(m_Grid, Gtk::PACK_SHRINK);

  // m_Grid.attach(m_Images[0],0,0,1,1);
  // // m_Images[0].set_margin_left(25);
  // m_Grid.attach(m_Images[1],1,0,1,1);
  // m_Images[1].set_margin_left(25);
  // m_Grid.attach(m_Images[3],0,1,1,1);
  // m_Images[3].set_margin_top(25);
  for(int i=0; i < 4; i++){
    for(int j=0; j<13; j++){
      m_Grid.attach(m_Images[i*13+j],j,i,1,1);
      if(j!=12){
        m_Images[i*13+j].set_margin_right(25);
      }
      m_Images[i*13+j].set_margin_bottom(10);    
    }
  }
  // int i = 0;
  // m_Grid.add(m_Images[0]);
  // m_Images[0].set_margin_left(23);
  // for(int j = 0; j < 4; j++){  
  //   if(j!=0){
  //     m_Grid.attach_next_to(m_Images[j*13], m_Images[(j-1)*13], Gtk::POS_BOTTOM, 2,1);
  //   }
  //   for(i = 1; i<13; i++){
  //     if(i!=12){
  //       m_Images[i-1+j*13].set_margin_right(25);
  //     }
  //     m_Grid.attach_next_to(m_Images[i+j*13], m_Images[i-1+j*13], Gtk::POS_RIGHT, 2,1);
  //   }
  // }
    // m_Grid.attach_next_to(m_Image2, m_Image, Gtk::POS_RIGHT, 2,1);
  // m_Grid.attach_next_to(m_Image, m_Image2, Gtk::POS_RIGHT, 2,1);



  //Connect signal
  m_ButtonShuffle.signal_clicked().connect(sigc::mem_fun(*this,
              &MainWindow::onButtonShuffle) );
  m_ButtonQuit.signal_clicked().connect(sigc::mem_fun(*this,
              &MainWindow::onButtonQuit) );

  show_all_children();
}

MainWindow::~MainWindow() {
}

void MainWindow::onButtonShuffle()
{
  string seed = m_EntrySeed.get_text();
  cout << seed << endl;
}

void MainWindow::onButtonQuit()
{
  hide();
}
