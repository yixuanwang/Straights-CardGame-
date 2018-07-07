#include "MainWindow.h"

using namespace std;

MainWindow::MainWindow()
: m_Box(Gtk::ORIENTATION_HORIZONTAL),
  m_ButtonShuffle("Shuffle"),
  m_ButtonQuit("Quit")
{
  set_title("Straights");
  add(m_Box);

  //Set Sizes
  m_ButtonShuffle.set_size_request(400, 32);
  m_ButtonQuit.set_size_request(400, 32);
  m_EntrySeed.set_size_request(32, 32);

  //Add buttons
  m_Box.pack_start(m_ButtonBox, Gtk::PACK_SHRINK);
  m_ButtonBox.pack_start(m_ButtonShuffle, Gtk::PACK_SHRINK);
  m_ButtonBox.add(m_EntrySeed);
  m_ButtonBox.pack_start(m_ButtonQuit, Gtk::PACK_SHRINK);
  m_ButtonBox.set_layout(Gtk::BUTTONBOX_END);

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
