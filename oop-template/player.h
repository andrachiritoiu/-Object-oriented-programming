#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>
#include <string>

class Player{
    private:
        sf::Texture texture; //imaginea jucatorului
        sf::Sprite skin; //obiectul care va fi afisat pe ecran
        float x, y;
        int speed;
        std::string name; 
        bool isJumping;
        float jumpHeight;

    public:
    //constructors
    Player()=default;
    Player(const std::string& texturePath, float x, float y, int speed, const std::string &name, bool isJumping, float jumpHeight);

    //copy constructor
    Player(const Player &p);
    //operator 
    Player& operator=(const Player &p);
    //getters
    int getX() const;
    int getY() const;
    int getSpeed() const;
    const std::string& getName() const;
    const sf::Texture& getTexture() const;
    const sf::Sprite& getSprite() const;
    //setters
    void setX(int x);
    void setY(int y);
    void setSpeed(int speed);
    //methods

    //destructor
    ~Player()=default;
};

#endif // PLAYER_H