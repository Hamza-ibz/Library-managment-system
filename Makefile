CXX = g++
CXXFLAGS = -g -Wall -Wextra
.PHONY: all
all : library
library: main_library.cpp library_functions.o
	$(CXX) $(CXXFLAGS) -o $@ $^
library_functions.o: library_functions.cpp  hashtable.h
	$(CXX) $(CXXFLAGS) -c $<
.PHONY : clean
clean:
	rm *~ *.o library
