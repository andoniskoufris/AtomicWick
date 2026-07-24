#### Makefile

## C++ compiler
CXX := g++-15

## compiler flags
CXXFLAGS := -Wall -g -O3

## name of target to delete when cleaning
TARGET_DEL = AtomicWick

## source directory
SRCDIR := ./

## source .cpp files
SRCS := $(shell find $(SRCDIR) -name "*.cpp")

## Object files 
OBJS := $(SRCS:.cpp=.o)

AtomicWick: $(OBJS)
	g++-15 $^ -o AtomicWick $(CXXFLAGS)
	rm -f $^

## This generates a .o file for every .cpp file
#  the $^ automatically gets the prerequisite and the $@ automatically gets the target name
$(OBJS): %.o: %.cpp
	$(CXX) -c $^

clean:
	rm -f $(TARGET_DEL)
