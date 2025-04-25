#include "garbage.h"

//constructor
Garbage::Garbage(float x, float y) : Obstacles(x, y+70.f) {
    setTexture("garbage.png");
    shape.setScale(1.f, 1.f); 
}

//methods
void Garbage::draw(sf::RenderWindow &window) {
    window.draw(shape);
}

void Garbage::update() {
    x -= 5.f;
    shape.setPosition(x, y);
}