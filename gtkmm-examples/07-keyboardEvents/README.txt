https://developer.gnome.org/gtkmm-tutorial/stable/sec-keyboardevents-overview.html.en

"Whenever you press or release a key, an event is emitted. You can connect a signal 
handler to handle such events.

To receive the keyboard events, you must first call the Gtk::Widget::add_events() 
function with a bit mask of the events you're interested in. The event signal handler 
will receive an argument that depends on the type of event. For keyboard events it's 
a GdkEventKey*. As discribed in the appendix, the event signal handler returns a bool 
value, to indicate that the signal is fully handled (true) or allow event propagation 
(false).

To determine which key was pressed or released, you read the value of GdkEventKey::keyval 
and compare it with a constant in the <gdk/gdkkeysyms.h> header file. The states of 
modifier keys (shift, ctrl, etc.) are available as bit-flags in GdkEventKey::state.

Here's a simple example:

bool on_key_press_or_release_event(GdkEventKey* event)
{
  if (event->type == GDK_KEY_PRESS &&
    event->keyval == GDK_KEY_1 &&
    (event->state & (GDK_SHIFT_MASK | GDK_CONTROL_MASK | GDK_MOD1_MASK)) == GDK_MOD1_MASK)
  {
    handle_alt_1_press(); // GDK_MOD1_MASK is normally the Alt key
    return true;
  }
  return false;
}

Gtk::Entry m_entry; // in a class definition

// in the class constructor
m_entry.signal_key_press_event().connect( sigc::ptr_fun(&on_key_press_or_release_event) );
m_entry.signal_key_release_event().connect( sigc::ptr_fun(&on_key_press_or_release_event) );
m_entry.add_events(Gdk::KEY_PRESS_MASK | Gdk::KEY_RELEASE_MASK);"
