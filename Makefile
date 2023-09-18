CC = g++
CFLAGS = -Wall -Wextra -std=c++11 `sdl2-config --cflags`
SDLFLAGS = `sdl2-config --libs`

main: main.cpp
	$(CC) $(CFLAGS) main.cpp -o main $(SDLFLAGS)

clean:
	rm main
