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

## Object files (not needed)
# OBJS := $(SRCS:.cpp=.o)

AtomicWick: AtomicWick.o
	g++-15 AtomicWick.o -o AtomicWick $(CXXFLAGS)
	rm -f AtomicWick.o

AtomicWick.o: AtomicWick.cpp
	$(CXX) -c $(SRCS) -o AtomicWick.o

clean:
	rm -f $(TARGET_DEL)


# # a target called blah (i.e. when this runs it will create a file called blah)
# # it has a dependency of blah.o, so it won't run until blah.o is created (if it doesn't already exist) or is updated
# blah: blah.o
# 	CXX blah.o -o blah

# # a target called blah.o which is a dependency of blah
# # depends on blah.c so won't run until blah.c is created or is updated
# blah.o:  blah.c
# 	CXX -c blah.c -o blah.o

# # this creates a c file called blah.c that is then used to make blah.o and then finally to create the executable blah
# # if this is deleted, all three of the targets will run again
# # if it is just updated, only the top two targets will run
# blah.c:
# 	echo "int main() {return 0;}" > blah.c

