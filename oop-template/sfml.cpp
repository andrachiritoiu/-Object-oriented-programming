#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "Player.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1400, 700), "Game");
    window.setFramerateLimit(60);

    // Fundal repetabil
    sf::Texture bgTexture;
    if (!bgTexture.loadFromFile("fundal.jpg")) {
        std::cerr << "Error\n";
        return -1;
    }
    bgTexture.setRepeated(true);

    // Dimensiuni imagine
    sf::Vector2u textureSize = bgTexture.getSize();
    float scaleX = (float)window.getSize().x / textureSize.x; //textureSize.x -latimea imaginii de fundal
    float scaleY = (float)window.getSize().y / textureSize.y;
    float scaleFinal = std::min(scaleX, scaleY); 

    sf::Vector2f scaledSize(textureSize.x * scaleFinal, textureSize.y * scaleFinal); //dimensiunile imaginii de fundal dupa scalare

    sf::RectangleShape background(scaledSize);
    background.setTexture(&bgTexture);

    background.setTextureRect(sf::IntRect(0, 0, textureSize.x, textureSize.y));
    
    //cat de mult se muta fundalul pe axa x
    float bgOffset = 0.f;

    // Patrate
    std::vector<sf::RectangleShape> patratele;
    float patratSize = 60.f;
    float timpIntrePatrate = 2.0f;
    float timer = 0.0f;
    sf::Clock clock;

    // Creare player
    Player player("playergirl.png", 100.f, 380.f, 10, "Player1", 50.f, 0.f, 4.f);
    player.getSkin().setScale(0.5f, 0.5f);

    while (window.isOpen())
    {
        float dt = clock.restart().asSeconds();
        timer += dt; //pt timpul intre patrate

        sf::Event event;
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();

        // Scroll fundal - se deplaseaza cu 150 de pixeli pe secunda
        bgOffset += 150 * dt;
        if (bgOffset >= textureSize.x)
            bgOffset -= textureSize.x;

        // Actualizează dreptunghiul texturii (pentru scroll)
        background.setTextureRect(sf::IntRect(bgOffset, 0, textureSize.x, textureSize.y));

        // Generare patrate
        if (timer >= timpIntrePatrate)
        {
            timer = 0.f;

            sf::RectangleShape umbra(sf::Vector2f(patratSize, patratSize));
            umbra.setFillColor(sf::Color(30, 30, 30, 150));
            umbra.setPosition(window.getSize().x + 4, window.getSize().y - patratSize - 100 + 4);

            sf::RectangleShape patrat(sf::Vector2f(patratSize, patratSize));
            patrat.setFillColor(sf::Color(64, 64, 80));
            patrat.setPosition(window.getSize().x, window.getSize().y - patratSize - 100);

            patratele.push_back(umbra);
            patratele.push_back(patrat);
        }

        // Muta patratele spre stânga
        for (auto& p : patratele)
            p.move(-200 * dt, 0);

        // Sterge patratele ieșite din ecran
        for (size_t i = 0; i < patratele.size();)
        {
         if (patratele[i].getPosition().x + patratele[i].getSize().x < 0)
            {
            patratele.erase(patratele.begin() + i); 
            }
        else i++; 
        }

        // Control jucător
        player.handleInput(window);
        player.update(); 

        // Render
        window.clear();
        window.draw(background);
        for (auto& p : patratele)
            window.draw(p);
        player.draw(window); 

        window.display();
    }

    return 0;
}
