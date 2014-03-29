MAIN = lib/main.cpp 
LIB  = lib/vector.cpp lib/dot.cpp

all: 
	g++ -o prog -W -Wall -pedantic -ansi -lSDL2 -lGL -lGLU $(MAIN) $(LIB)
clean:
	rm prog




