CC     = g++
CFLAGS = -c -Wall 
LINKER_FLAGS = -lSDL2 $(pkg-config --cflags --libs sdl2)

all: maze

maze: main.o griid.o 
	$(CC) main.o griid.o -o maze $(LINKER_FLAGS)

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

griid.o: griid.cpp Griid.h
	$(CC) $(CFLAGS) $(LINKER_FLAGS) griid.cpp

clean:
	rm -rf *o hello
