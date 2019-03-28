# define libraries
LIB = -lGL -lGLU -lglut -std=c++11

# define g++ flags
CC = g++

GLToolbox: GLToolbox.cpp
	$(CC) -o GLToolbox GLToolbox.cpp $(LIB)