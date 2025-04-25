#ifndef BUILDING_H
#define BUILDING_H
#include <SFML/Graphics.hpp>
#include <string>
#include "obstacles.h"

class Building : public Obstacles {
    public:
    //constructors
    Building()=default;
    Building(float x, float y);

    //methods
    void draw(sf::RenderWindow &window) override;
    void update() override;

    //destructor
    ~Building() override =default;

};

#endif // BUILDING_H