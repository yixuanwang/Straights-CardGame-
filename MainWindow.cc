#include "MainWindow.h"
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
  m_Frame4("Player 4")
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

  for(int i=0; i < 4; i++){
    for(int j=0; j<13; j++){
      m_Grid.attach(m_Images[i*13+j],j,i,1,1);
      if(j!=12){
        m_Images[i*13+j].set_margin_right(25);
      }
      m_Images[i*13+j].set_margin_bottom(10);    
    }
  }

  //Rage Button
  m_Box.add(m_ButtonRage);

  //Players section
  m_Box.pack_start(m_Frame1, Gtk::PACK_SHRINK);
  m_Point1.set_label("0 points\n0 discards");
  m_Frame1.add(m_Point1);

  m_Box.pack_start(m_Frame2, Gtk::PACK_SHRINK);
  m_Point2.set_label("0 points\n0 discards");
  m_Frame2.add(m_Point2);

  m_Box.pack_start(m_Frame3, Gtk::PACK_SHRINK);
  m_Point3.set_label("0 points\n0 discards");
  m_Frame3.add(m_Point3);

  m_Box.pack_start(m_Frame4, Gtk::PACK_SHRINK);
  m_Point4.set_label("0 points\n0 discards");
  m_Frame4.add(m_Point4);

  m_Box.pack_start(m_FrameHand, Gtk::PACK_EXPAND_WIDGET);
  m_FrameHand.add(m_Hand);
  for(int i=0; i<13; i++){
    ImageButton *temp = new ImageButton("img/nothing.png");
    emptyHand.push_back(temp);
    m_Hand.pack_start(*emptyHand[i]);
  }
  m_Hand.set_layout(Gtk::BUTTONBOX_START);

  //Connect signal
  m_ButtonShuffle.signal_clicked().connect(sigc::mem_fun(*this,
              &MainWindow::onButtonShuffle) );
  m_ButtonQuit.signal_clicked().connect(sigc::mem_fun(*this,
              &MainWindow::onButtonQuit) );
  m_ButtonRage.signal_clicked().connect(sigc::mem_fun(*this,
              &MainWindow::onButtonRage) );

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

void MainWindow::onButtonRage()
{
}
