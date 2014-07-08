all:
	g++ main.cpp -o prog -W -Wall -pedantic -ansi -lSDL2 -lGL -lGLU
	
run:
	cat start_objects.txt | ./prog