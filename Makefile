CC = g++
CPPFLAGS = -Wall -g -Wextra -std=c++17 `sdl2-config --cflags` -lSDL2_image -lSDL2_ttf
SDLFLAGS = `sdl2-config --libs`
OBJDIR = ./build/

all: main

main: $(OBJDIR)main.o $(OBJDIR)Sprite.o $(OBJDIR)DisplayManager.o $(OBJDIR)Color.o $(OBJDIR)Position.o $(OBJDIR)GameObject.o $(OBJDIR)Player.o $(OBJDIR)utils.o $(OBJDIR)StaticSprites.o $(OBJDIR)CollisionBox.o $(OBJDIR)SpaceShip.o $(OBJDIR)AnimatedSprites.o $(OBJDIR)InvisibleWall.o $(OBJDIR)Interactable.o $(OBJDIR)SpaceShipPart.o $(OBJDIR)DynamicGameObject.o $(OBJDIR)Asteroid.o $(OBJDIR)StaticText.o
	$(CC) $(CPPFLAGS) $^ -o $@ $(SDLFLAGS)

$(OBJDIR)%.o: %.cpp
	$(CC) $(CPPFLAGS) -c $< -o $@

clean:
	rm -f main $(OBJDIR)*.o
