#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "player.h"
#include "obstacles.h"
#include "car.h"
#include "building.h"
#include "garbage.h"

int Obstacles::count = 0; // static

int main()
{
    sf::RenderWindow window(sf::VideoMode(1400, 700), "Game");
    window.setFramerateLimit(60);

    // Fundal repetabil
    sf::Texture bgTexture;
    if (!bgTexture.loadFromFile("fundal2.png")) {
        std::cerr << "Error loading background\n";
        return -1;
    }
    bgTexture.setRepeated(true);

    // Dimensiuni imagine
    sf::Vector2u textureSize = bgTexture.getSize();
    float scaleX = static_cast<float>(window.getSize().x) / textureSize.x;
    float scaleY = static_cast<float>(window.getSize().y) / textureSize.y;
    float scaleFinal = std::min(scaleX, scaleY);

    sf::Vector2f scaledSize(textureSize.x * scaleFinal, textureSize.y * scaleFinal);
    sf::RectangleShape background(scaledSize);
    background.setTexture(&bgTexture);
    background.setTextureRect(sf::IntRect(0, 0, textureSize.x, textureSize.y));

    float bgOffset = 0.f;

    // Obstacole
    std::vector<Obstacles*> obstacole;
    float timpIntreObstacole = 2.5f;
    float timer = 0.0f;
    sf::Clock clock;
    srand(static_cast<unsigned>(time(nullptr)));

    // Player
    Player player("playerboy.png", 100.f, 380.f, 10, "Player1", 50.f, 0.f, 4.f);
    player.getSkin().setScale(0.5f, 0.5f);

    while (window.isOpen())
    {
        float dt = clock.restart().asSeconds();
        timer += dt;

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Scroll fundal
        bgOffset += 150 * dt;
        if (bgOffset >= textureSize.x)
            bgOffset -= textureSize.x;
        background.setTextureRect(sf::IntRect(static_cast<int>(bgOffset), 0, textureSize.x, textureSize.y));

        // Generare obstacole
        if (timer >= timpIntreObstacole)
        {
            timer = 0.f;
            int random = rand() % 3;
            Obstacles* obstacol = nullptr;

            float xStart = window.getSize().x;
            float yPos = window.getSize().y - 240.f;

            switch (random)
            {
                case 0: obstacol = new Car(xStart, yPos); break;
                case 1: obstacol = new Building(xStart, yPos); break;
                case 2: obstacol = new Garbage(xStart, yPos); break;
            }

            if (obstacol)
                obstacole.push_back(obstacol);
        }

        // Update obstacole (mișcare)
        for (auto& obstacol : obstacole)
            obstacol->update();

        // Șterge obstacolele ieșite din ecran
        for (size_t i = 0; i < obstacole.size(); )
        {
            if (obstacole[i]->getX() + 100.f < 0)
            {
                delete obstacole[i];
                obstacole.erase(obstacole.begin() + i);
            }
            else ++i;
        }

        // Player logic
        player.handleInput(window);
        player.update();

        for (auto& obstacol : obstacole)
        {
            //-> =la pointeri
            if (player.getBounds().intersects(obstacol->getBounds()))
            {
                player.setX(obstacol->getBounds().left); 
                player.getSkin().setPosition(obstacol->getBounds().left-player.getBounds().width, player.getY());
            }
        }

        // Render
        window.clear();
        window.draw(background);
        for (auto& obstacol : obstacole)
            obstacol->draw(window);
        player.draw(window);
        window.display();
    }

    // Cleanup
    for (auto& obstacol : obstacole)
        delete obstacol;

    return 0;
}
