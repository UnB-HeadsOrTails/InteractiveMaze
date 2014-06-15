MAIN = lib/main.cpp 
LIB  = lib/vector.cpp
ENGINE = engine/classes/*
ENGINE_I = engine/classes/

all: 
	g++ -o prog -W -Wall -pedantic -ansi -lSDL2 -lGL -lGLU $(MAIN) $(LIB) $(ENGINE) -I $(ENGINE_I)
clean:
	rm prog




