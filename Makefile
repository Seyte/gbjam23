CC = g++
CPPFLAGS = -Wall -g -Wextra -std=c++11 `sdl2-config --cflags`
SDLFLAGS = `sdl2-config --libs`
DSTFILE = ./build/

all: main

main: main.o DisplayManager.o Color.o
	$(CC) $(CPPFLAGS) $^ -o $(DSTFILE)$@ $(SDLFLAGS)

%.o: %.cpp
	$(CC) $(CPPFLAGS) -c $< -o $@

clean:
	rm -f main *.o
