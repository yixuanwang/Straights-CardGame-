Documentation
=============
GTKmm API documentation: https://developer.gnome.org/gtkmm/stable/pages.html
GTKmm 3 reference manual: https://developer.gnome.org/gtkmm/stable/
GTKmm 3 tutorial: https://developer.gnome.org/gtkmm-tutorial/stable/
Glade: https://developer.gnome.org/glade/stable/index.html.en_GB


Versions of GTKmm
=================
ubuntu1404-0NN.student.cs.uwaterloo has gtkmm 2.24.4 installed globally, with
gtkmm 3.18.1 installed under /u/cs_build/gtkmm, which means you need to put

      export PKG_CONFIG_PATH=/u/cs_build/gtkmm/lib/pkgconfig/
      export LD_LIBRARY_PATH=/u/cs_build/gtkmm/lib

in your .profile file to ensure the correct paths are searched when compiling
and linking.

ubuntu1604-000.student.cs.uwaterloo.ca has gtkmm 3.18.0 installed globally.

You can use dpkg to search for what version of gtkmm is installed:

% dpkg -l "*gtkmm*"

Desired=Unknown/Install/Remove/Purge/Hold
| Status=Not/Inst/Conf-files/Unpacked/halF-conf/Half-inst/trig-aWait/Trig-pend
|/ Err?=(none)/Reinst-required (Status,Err: uppercase=bad)
||/ Name                Version        Architecture   Description
+++-===================-==============-==============-===========================================
ii  libgtkmm-2.4-1c2a:a 1:2.24.4-1ubun amd64          C++ wrappers for GTK+ (shared libraries)
ii  libgtkmm-2.4-dbg:am 1:2.24.4-1ubun amd64          C++ wrappers for GTK+ (debug symbols)
ii  libgtkmm-2.4-dev:am 1:2.24.4-1ubun amd64          C++ wrappers for GTK+ (development files)
un  libgtkmm-2.4-doc    <none>         <none>         (no description available)
ii  libgtkmm-3.0-1:amd6 3.10.1-0ubuntu amd64          C++ wrappers for GTK+ (shared libraries)
ii  libgtkmm-3.0-dbg:am 3.10.1-0ubuntu amd64          C++ wrappers for GTK+ (debug symbols)
ii  libgtkmm-3.0-dev:am 3.10.1-0ubuntu amd64          C++ wrappers for GTK+ (development files)
un  libgtkmm-3.0-doc    <none>         <none>         (no description available)

Known Glade Issue
=================
"I investigated the issue and the problem happens when you use the new gtk+ that I installed in the 
cs_build account. There's some version incompatibility, and the glade that's installed globally on 
Ubuntu 14.04 is too old to use the new gtk stuff I installed (it complains about a missing 
'sort-directories-first' key which newer gtk has).

If you unset the PKG_CONFIG_PATH and LD_LIBRARY_PATH environment variables, glade should run. But I
know it's annoying unsetting and setting them back every time you use glade.

Alternatively, you should be able to start glade on ubuntu1604-000.student.cs, with those environment 
variables set.

I'll try and upgrade gtkmm later this week, and at the same time see if I can install a newer version 
of glade that's usable from ubuntu1404."
