#include "obstacles.h"

//constructor
Obstacles::Obstacles(float x, float y) {
    this->x=x;
    this->y=y;
    count++;
}

Obstacles::Obstacles(const std::string& texturePath, float x, float y) {
    this->x=x;
    this->y=y;

    if (!texture.loadFromFile(texturePath)) {
        throw std::runtime_error("Failed to load texture from " + texturePath);
    }
    shape.setTexture(texture);
    shape.setPosition(x, y);

    count++;
}

//operator
Obstacles& Obstacles::operator=(const Obstacles& o){
    if(this!=&o){
        this->x=o.x;
        this->y=o.y;
        this->texture=o.texture;
        this->shape.setTexture(this->texture);
        this->shape.setPosition(o.x, o.y);
    }

    count++;

    return *this;
}

//getters
float Obstacles::getX()const{
    return x;
}

float Obstacles::getY()const{
    return y;
}

//setters
void Obstacles::setTexture(const std::string &texturePath){
    if (!texture.loadFromFile(texturePath)) {
        throw std::runtime_error("Failed to load texture from " + texturePath);
    }
    shape.setTexture(texture);
}

void Obstacles::setX(float x){
    this->x=x;
}

void Obstacles::setY(float y){
    this->y=y;
}

//methods
int Obstacles::getCount(){
    return count;
}

