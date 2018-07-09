CXX = g++ -std=c++14
CXXFLAGS = -Wall -O -g -MMD # use -MMD to generate dependencies
GTKFLAGS = `pkg-config gtkmm-3.0 --cflags --libs`
SOURCES = $(wildcard *.cpp) # list of all .cpp files in the current directory
OBJECTS = ${SOURCES:.cpp=.o} # .o files depend upon .cpp files with same names
DEPENDS = ${OBJECTS:.o=.d}  # .d file is list of dependencies for corresponding .cpp file
EXEC=test

# First target in the makefile is the default target.
# Note that the GTKFLAGS must come last in the command
$(EXEC): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(EXEC)  $(GTKFLAGS)

%.o: %.cpp
	$(CXX) -c -o $@ $< $(CXXFLAGS) $(GTKFLAGS)

-include ${DEPENDS}

.PHONY: clean
clean:
	rm  -f $(OBJECTS) $(DEPENDS) $(EXEC)
