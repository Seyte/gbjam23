CC = g++
CFLAGS = -Wall -Wextra -std=c++11 `sdl2-config --cflags`
SDLFLAGS = `sdl2-config --libs`

all: main

main: main.o DisplayManager.o Color.o
	$(CC) $(CFLAGS) $^ -o $@ $(SDLFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f main *.o
