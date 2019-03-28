# define libraries
LIB = -lGL -lGLU -lglut -std=c++11

# define g++ flags
CC = g++

project4: project4.cpp
	$(CC) -o project4 project4.cpp $(LIB)