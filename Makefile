MAIN = lib/main.cpp 
LIB  = lib/vector.cpp
ENGINE = engine/classes/* engine/interfaces/* engine/state_machine/*
INCLUDE = includes

all: 
	g++ -o prog -W -Wall -pedantic -ansi -lSDL2 -lGL -lGLU -lGLEW $(MAIN) $(LIB) $(ENGINE) -I $(INCLUDE)
clean:
	rm prog




