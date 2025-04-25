#include "player.h"


//constructor
Player::Player(const std::string& texturePath, float x, float y, int speed, const std::string& name, float jumpHeight, float velocityY, float gravity) {
        this->x=x;
        this->y=y;
        this->speed=speed;
        this->name=name;
        this->isJumping=false;
        this->jumpHeight=jumpHeight;
        this->velocityY=velocityY;
        this->gravity=gravity;
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
    this->velocityY=p.velocityY;
    this->gravity=p.gravity;

    this->texture=p.texture;
    this->skin.setTexture(this->texture);
    this->skin.setPosition(p.x, p.y);
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
        this->velocityY=p.velocityY;
        this->gravity=p.gravity;

        this->texture=p.texture;
        this->skin.setTexture(this->texture);  
        this->skin.setPosition(p.x, p.y); 
    }
    return *this;
}
  
//getters
float Player::getX()const{
    return x;
}

float Player::getY()const{
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
void Player::move(float dx, float dy, const sf::RenderWindow &window) {
    x += dx;
    //mariginea la dreapta
    if (x+skin.getGlobalBounds().width > window.getSize().x) { 
        x = window.getSize().x - skin.getGlobalBounds().width;
    }
    //marginea la stanga
    if (x < 0) { 
        x = 0;
    }
    
    y += dy;
    if (y+skin.getGlobalBounds().height > window.getSize().y) { 
        y = window.getSize().y - skin.getGlobalBounds().height;
    }
    
    if (y < 0) { 
        y= 0;
    }
    skin.setPosition(x, y);
}

void Player::jump(float height) {
    if (!isJumping) {
        isJumping = true;
        velocityY = -height;
    }
}

void Player::update(){
    if (isJumping) {
        velocityY += gravity; 
        y += velocityY;
        if (y >= 380.f) { // inaltimea solului
            y = 380.f;
            isJumping = false;
            velocityY = 0; 
        }
        x += 50.f * 0.04f; //0.04f este dt-ul, adica timpul scurs intre frame-uri
        skin.setPosition(x, y);
    }

}

void Player::handleInput(const sf::RenderWindow &window) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        move(-speed, 0, window); 
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        move(speed, 0, window); 
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !isJumping) {
        jump(jumpHeight); 
    }

    if (isJumping) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            move(-speed / 2, 0, window); // Mișcare redusă în timpul săriturii
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            move(speed / 2, 0, window); // Mișcare redusă în timpul săriturii
        }
    }
}

void Player::draw(sf::RenderWindow &window) {
    window.draw(skin);
}