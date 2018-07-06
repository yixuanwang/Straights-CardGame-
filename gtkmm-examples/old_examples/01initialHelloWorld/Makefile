CXX= g++
CXXFLAGS = -Wall -O -g `pkg-config gtkmm-3.0 --cflags --libs`
OBJS = hello.o
EXEC = hello

hello: hello.o
	$(CXX) $(OBJS) $(CXXFLAGS) -o $(EXEC)

hello.o: hello.cc
