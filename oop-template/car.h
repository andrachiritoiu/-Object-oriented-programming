#ifndef CAR_H
#define CAR_H
#include <SFML/Graphics.hpp>
#include <string>
#include "obstacles.h"

class Car : public Obstacles{
public:
    //constructors
    Car()=default;
    Car(float x, float y);

    //methods
    void draw(sf::RenderWindow &window) override; 
    void update() override;

    //destructor
    ~Car() override =default;

};


#endif // CAR_H