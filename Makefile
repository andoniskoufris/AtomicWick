# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -g -O3

wickmake: wickc.o
	$(CXX) -o wickmake wickc.o