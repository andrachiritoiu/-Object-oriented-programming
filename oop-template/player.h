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
        float velocityY; //viteza verticala a jucatorului
        float gravity; 

    public:
    //constructors
    Player()=default;
    Player(const std::string& texturePath, float x, float y, int speed, const std::string &name, float jumpHeight,float velocityY, float gravity);

    //copy constructor
    Player(const Player &p);

    //operator 
    //& - referinta catre obiectul curent *this
    Player& operator=(const Player &p);

    //getters
    //const - nu modifica obiectul curent
    float getX() const;
    float getY() const;
    int getSpeed() const;
    const std::string& getName() const;
    bool getIsJumping() const;
    float getJumpHeight() const;
    sf::Sprite& getSkin() ;

    //setters
    void setTexture(const std::string &texturePath);
    void setX(int x);
    void setY(int y);
    void setSpeed(int speed);
    void setName(const std::string &name);
    void setIsJumping(bool isJumping);
    void setJumpHeight(float jumpHeight);

    //methods
    void move(float dx, float dy, const sf::RenderWindow &window); 
    void jump(float height); 
    void update(); 
    void handleInput(const sf::RenderWindow &window);
    void draw(sf::RenderWindow &window);


    //destructor
    ~Player()=default;
};

#endif // PLAYER_H