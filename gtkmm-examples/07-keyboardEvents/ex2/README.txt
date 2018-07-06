"In this example there are three event handlers that are called after Gtk::Window's 
default event handler, one in the Gtk::Entry, one in the Gtk::Grid and one in the 
Gtk::Window.

In the Gtk::Window, we have also the default handler overridden 
(on_key_release_event()), and another handler being called before the default 
handler (windowKeyReleaseBefore()).

The purpose of this example is to show the steps the event takes when it is emitted.

When you write in the entry, a key release event will be emitted, which will go 
first to the toplevel window (Gtk::Window), since we have one event handler set to 
be called before, that's what is called first (windowKeyReleaseBefore()). Then the 
default handler is called (which we have overridden), and after that the event is 
sent to the widget that has focus, the Entry in our example and, depending on 
whether we let it propagate, it can reach the Grid's and the Window's event handlers. 
If it propagates, the text you're writing will appear in the Label above the Entry."