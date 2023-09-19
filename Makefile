CC = g++
CPPFLAGS = -Wall -g -Wextra -std=c++11 `sdl2-config --cflags`
SDLFLAGS = `sdl2-config --libs`
OBJDIR = ./build/

all: main

main: $(OBJDIR)main.o $(OBJDIR)DisplayManager.o $(OBJDIR)Color.o $(OBJDIR)Position.o $(OBJDIR)GameObject.o $(OBJDIR)Player.o
	$(CC) $(CPPFLAGS) $^ -o $@ $(SDLFLAGS)

$(OBJDIR)%.o: %.cpp
	$(CC) $(CPPFLAGS) -c $< -o $@

clean:
	rm -f main $(OBJDIR)*.o
