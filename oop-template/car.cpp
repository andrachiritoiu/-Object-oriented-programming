#include "car.h"

//constructor
Car::Car(float x, float y) : Obstacles(x, y) {
    setTexture("car1.png");
    shape.setScale(0.08f, 0.08f); 
}

//methods
void Car::draw(sf::RenderWindow &window) {
    window.draw(shape);
}

void Car::update() {
    x -= 5.f;
    shape.setPosition(x, y);
}
