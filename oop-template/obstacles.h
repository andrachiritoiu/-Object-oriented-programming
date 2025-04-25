#ifndef OBSTACLES_H
#define OBSTACLES_H
#include <SFML/Graphics.hpp>
#include <string>

class Obstacles {
    protected:
        sf::Texture texture; 
        sf::Sprite shape; 
        float x, y; 
        static int count;
      
    public:
    //constructors
        Obstacles()=default;
        Obstacles(float x, float y);
        Obstacles(const std::string& texturePath, float x, float y);

    //operator
        Obstacles& operator=(const Obstacles &o);

    //getters
        float getX() const;
        float getY() const;   

    //setters
        void setTexture(const std::string &texturePath);
        void setX(float x);
        void setY(float y);

    //methods
        virtual void draw(sf::RenderWindow &window)=0; //metoda virtuala pura
        virtual void update()=0;  
        static int getCount();

    //destructor
        virtual ~Obstacles()=default;

};

#endif // OBSTACLES_H