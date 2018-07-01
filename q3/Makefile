CXX = g++-5 -std=c++14
CXXFLAGS = -Wall -O -g -MMD # use -MMD to generate dependencies
LIBFLAGS = -ljsoncpp # link in boost's date and time library and JSON cpp 
SOURCES = $(wildcard *.cc)  # list of all .cc files in the current directory
OBJECTS = $(SOURCES:.cc=.o) # .o files depend upon .cc files with same names
DEPENDS = ${OBJECTS:.o=.d}   # .d file is list of dependencies for corresponding .cc file
EXEC=network

# First target in the makefile is the default target.
# Note that the LIBFLAGS must come last in the command
$(EXEC): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(EXEC)  $(LIBFLAGS)

%.o: %.cc 
	$(CXX) -c -o $@ $< $(CXXFLAGS) $(LIBFLAGS)

-include ${DEPENDS}

.PHONY: clean
clean:
	rm  -f $(OBJECTS) $(DEPENDS) $(EXEC)
