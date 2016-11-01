
CC = g++
FLAGS = `sdl-config --cflags` -Wall -c -ggdb

OBJ = main.o
EXE = run

$(EXE): $(OBJ)
	$(CC) $(OBJ) -o $(EXE)
	
clean:
	 rm -rf *.o $(EXE)

