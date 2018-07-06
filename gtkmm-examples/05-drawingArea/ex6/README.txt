Replace the path in myarea.cc and image.gresources.xml with the appropriate path to where
you've copied the example before you compile.

https://developer.gnome.org/gtkmm-tutorial/stable/sec-draw-images.html.en

"Here is an example of a simple program that draws an image. The program loads the image 
from a resource file. See the Gio::Resource and glib-compile-resources section. Use 
glib-compile-resources to compile the resources into a C source file that can be 
compiled and linked with the C++ code. E.g.

$ glib-compile-resources --target=resources.c --generate-source image.gresource.xml"
