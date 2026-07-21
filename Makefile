# # Compiler
# CXX = g++

# # Compiler flags
# CXXFLAGS = -Wall -g -O3

# wickmake: wickc.o
# 	$(CXX) -o wickmake wickc.o

# blah: AtomicWick.cpp
# 	g++ AtomicWick.cpp -o AtomicWick

# clean:
# 	rm -f AtomicWick

files := file1 file2
some_file: $(files)
	echo "Look at this variable: " $(files)
	touch some_file

file1:
	touch file1

file2: 
	touch file2

clean: 
	rm -f file1 file2 some_file

x := dude

all: 
	echo $(x)
	echo ${x}

print: $(wildcard *.hpp)
	ls -la  $?