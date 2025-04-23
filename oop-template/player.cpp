#include "Player.h"


//constructor
Player::Player(const std::string& texturePath, float x, float y, int speed, const std::string &name, bool isJumping, float jumpHeight)  {
        this->x=x;
        this->y=y;
        this->speed=speed;
        this->name=name;
        this->isJumping=isJumping;
        this->jumpHeight=jumpHeight;
    if (!texture.loadFromFile(texturePath)) {
        throw std::runtime_error("Failed to load texture from " + texturePath);
    }
    skin.setTexture(texture);
    skin.setPosition(x, y);
}

//copy constructor
Player::Player(const Player &p){
    this->x=p.x;
    this->y=p.y;
    this->speed=p.speed;
    this->name=p.name;
    this->isJumping=p.isJumping;
    this->jumpHeight=p.jumpHeight;
    this->texture=p.texture;
    this->skin=p.skin;
}

//operator
Player& Player::operator=(const Player &p){
    if(this!=&p){
        this->x=p.x;
        this->y=p.y;
        this->speed=p.speed;
        this->name=p.name;
        this->isJumping=p.isJumping;
        this->jumpHeight=p.jumpHeight;
        this->texture=p.texture;
        this->skin=p.skin;
    }
    return *this;
}
  
//getters
int Player::getX()const{
    return x;
}

int Player::getY()const{
    return y;
}

int Player::getSpeed()const{
    return speed;
}

const std::string& Player::getName()const{
    return name;
}

bool Player::getIsJumping()const{
    return isJumping;
}

float Player::getJumpHeight()const{
    return jumpHeight;
}

sf::Sprite& Player::getSkin() {
    return skin;
}

//setters
void Player::setTexture(const std::string &texturePath){
    if (!texture.loadFromFile(texturePath)) {
        throw std::runtime_error("Failed to load texture from " + texturePath);
    }
    skin.setTexture(texture);
}

void Player::setX(int x){
    this->x=x;
}

void Player::setY(int y){
    this->y=y;
}

void Player::setSpeed(int speed){
    this->speed=speed;
}

void Player::setName(const std::string &name){
    this->name=name;
}

void Player::setIsJumping(bool isJumping){
    this->isJumping=isJumping;
}

void Player::setJumpHeight(float jumpHeight){
    this->jumpHeight=jumpHeight;
}

//methods
void Player::move(float dx, float dy) {
    x += dx*speed;
    y += dy;
    skin.setPosition(x, y);
}

void Player::jump(float height) {
    if (!isJumping) {
        isJumping = true;
        y -= height;
        skin.setPosition(x, y);
    }
}

void Player::draw(sf::RenderWindow &window) {
    window.draw(skin);
}