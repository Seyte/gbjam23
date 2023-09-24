#include "StaticSprites.hpp"
#include "DisplayManager.hpp"

StaticSprites::StaticSprites(Position p, string filename,DisplayManager & dm) : GameObject(p,dm), _filename(filename){
}
void StaticSprites::update(float deltaTime){
    (void) deltaTime;
}
void StaticSprites::render(){
    getDisplayManager().setTexture(_filename, (uint)getPosition().getX(),(uint)getPosition().getY());
}
void StaticSprites::bounce(int direction){(void) direction;}