CXX=g++
STD=c++20
OPT=-O0
CXXFLAGS=-g $(OPT) -std=$(STD) -I.
BINARY=bin
FILENAME=futurespromises.cpp
OBJECTS=futurespromises.o

all: $(BINARY)

$(BINARY): $(OBJECTS)
	$(CXX) -o $@ $^

%.o:	%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $^

clean:
	rm -rf $(BINARY) *.o
