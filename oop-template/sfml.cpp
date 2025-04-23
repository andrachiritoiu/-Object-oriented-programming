#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "Player.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1400, 800), "Game");
    window.setFramerateLimit(60);

    // Fundal scalat și repetabil
    sf::Texture bgTexture;
    if (!bgTexture.loadFromFile("fundal1.png")) {
        std::cerr << "Error\n";
        return -1;
    }
    bgTexture.setRepeated(true);

    // Dimensiuni imagine + scalare
    sf::Vector2u textureSize = bgTexture.getSize();
    float scaleX = (float)window.getSize().x / textureSize.x;
    float scaleY = (float)window.getSize().y / textureSize.y;
    float scaleFinal = std::min(scaleX, scaleY); // imaginea întreagă

    sf::Vector2f scaledSize(textureSize.x * scaleFinal, textureSize.y * scaleFinal);
    sf::RectangleShape background(scaledSize);
    background.setTexture(&bgTexture);
    background.setTextureRect(sf::IntRect(0, 0, textureSize.x, textureSize.y));
    background.setPosition(
        (window.getSize().x - scaledSize.x) / 2.f,
        (window.getSize().y - scaledSize.y) / 2.f
    );

    float bgOffset = 0.f;

    // Patrate
    std::vector<sf::RectangleShape> patratele;
    float patratSize = 60.f;
    float timpIntrePatrate = 2.0f;
    float timer = 0.0f;
    sf::Clock clock;

    // Creare player
    Player player("player.jpg", 100.f, 600.f, 200, "Player1", false, 100.f);
    player.getSkin().setScale(1.f, 1.f);

    while (window.isOpen())
    {
        float dt = clock.restart().asSeconds();
        timer += dt;

        sf::Event event;
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();

        // Scroll fundal
        bgOffset += 200 * dt;
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
            umbra.setPosition(window.getSize().x + 4, window.getSize().y - patratSize - 80 + 4);

            sf::RectangleShape patrat(sf::Vector2f(patratSize, patratSize));
            patrat.setFillColor(sf::Color(64, 64, 80));
            patrat.setPosition(window.getSize().x, window.getSize().y - patratSize - 80);

            patratele.push_back(umbra);
            patratele.push_back(patrat);
        }

        // Muta patratele spre stânga
        for (auto& p : patratele)
            p.move(-200 * dt, 0);

        // Sterge patratele ieșite din ecran
        patratele.erase(std::remove_if(patratele.begin(), patratele.end(),
            [](const sf::RectangleShape& p) {
                return p.getPosition().x + p.getSize().x < 0;
            }),
            patratele.end());

        // Control jucător
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            player.move(-player.getSpeed() * dt, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            player.move(player.getSpeed() * dt, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            player.jump(player.getJumpHeight());
        }

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
