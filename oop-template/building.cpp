#include "building.h"

//constructor
Building::Building(float x, float y) : Obstacles(x, y+90.f) {
    setTexture("building.png");
    shape.setScale(1.f, 1.f); 
}

//methods
void Building::draw(sf::RenderWindow &window) {
    window.draw(shape);
}

void Building::update() {
    x -= 5.f;
    shape.setPosition(x, y);
}