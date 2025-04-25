#ifndef GARBAGE_H
#define GARBAGE_H
#include <SFML/Graphics.hpp>
#include <string>
#include "obstacles.h"

class Garbage : public Obstacles {
    public:
    //constructors
    Garbage()=default;
    Garbage(float x, float y);

    //methods
    void draw(sf::RenderWindow &window) override;
    void update() override;

    //destructor
    ~Garbage() override =default;

};

#endif // GARBAGE_H