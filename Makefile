CC = g++
CXX = $(CC)
DEBUG = -g -Wno-deprecated -fPIC

TARGETS = main
C_SRCS = main.cpp

# debug settings
CFLAGS = $(DEBUG) $(DEFINES) -I/usr/include 
LFLAGS = -g -L/usr/lib -std=c++11

CXXFLAGS = $(CFLAGS)

all: ${TARGETS}

main: main.cpp
	g++ main.cpp -o main ${LFLAGS} 


clean:
	rm -f bin/*

