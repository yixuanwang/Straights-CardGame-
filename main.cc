#include "Table.h"
#include "Player.h"
#include "MainWindow.h"
#include <gtkmm/application.h>

int main(int argc, char **argv){
	auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example");

  MainWindow window;

  //Shows the window and returns when it is closed.
  return app->run(window);
	/*
	Table table = Table(argc, argv);
	return 0;
	*/
}
