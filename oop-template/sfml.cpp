#include <SFML/Graphics.hpp>
#include <vector>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1400, 800), "Game");
    window.setFramerateLimit(60); //fps - cadre pe secundă

    // Fundal
    sf::Texture bgTexture;
    bgTexture.loadFromFile("fundal1.jpg"); 
    sf::Sprite bg1(bgTexture);
    sf::Sprite bg2(bgTexture);

    // Setăm pozițiile inițiale ale fundalurilor
    bg1.setPosition(0, 0);
    bg2.setPosition(bgTexture.getSize().x, 0);  

    // Scalarea fundalului pentru a umple toata ferestra 
    float scaleX = window.getSize().x / (float)bgTexture.getSize().x;
    float scaleY = window.getSize().y / (float)bgTexture.getSize().y;

    bg1.setScale(scaleX, scaleY);
    bg2.setScale(scaleX, scaleY);

    // Patrate
    std::vector<sf::RectangleShape> patratele;
    float patratSize = 60.f; //.f=float
    float timpIntrePatrate = 2.0f;
    float timer = 0.0f;
    sf::Clock clock;

    while (window.isOpen())
    {
        //dt =cat timp a trecut de la ultimul frame
        float dt = clock.restart().asSeconds();
        timer += dt;

        sf::Event event;
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();

        // Scroll fundal
        bg1.move(-200 * dt, 0);
        bg2.move(-200 * dt, 0);

        // Repozitionare fundal 
        if (bg1.getPosition().x + bgTexture.getSize().x < 0) //calculeaza pozitia capatului din dreapta a imaginii si verifica daca a trecut complet de marginea din stanga
            bg1.setPosition(bg2.getPosition().x + bgTexture.getSize().x, 0);
        if (bg2.getPosition().x + bgTexture.getSize().x < 0)
            bg2.setPosition(bg1.getPosition().x + bgTexture.getSize().x, 0);

        // Generare patrate
        if (timer >= timpIntrePatrate)
        {
            timer = 0.f;
            sf::RectangleShape umbra(sf::Vector2f(patratSize, patratSize));
            umbra.setFillColor(sf::Color(30, 30, 30, 150)); // culoare închisă, semi-transparentă
            umbra.setPosition(window.getSize().x + 4, window.getSize().y - patratSize - 220 + 4);

            sf::RectangleShape patrat(sf::Vector2f(patratSize, patratSize));
            patrat.setFillColor(sf::Color(64, 64, 80)); 

            // Ridicăm patratele mai sus de marginea de jos
            patrat.setPosition(window.getSize().x, window.getSize().y - patratSize - 220); //-220 este distanta de la marginea de jos a ferestrei

            patratele.push_back(umbra);  // umbra se desenează prima
            patratele.push_back(patrat);
        }

        // Muta patratele spre stânga
        for (auto& p : patratele)
            p.move(-200 * dt, 0);

        // Ștergem patratele care ies din ecran
        patratele.erase(std::remove_if(patratele.begin(), patratele.end(),
            [](const sf::RectangleShape& p) { return p.getPosition().x + p.getSize().x < 0; }),
            patratele.end());

        window.clear();
        window.draw(bg1);
        window.draw(bg2);

        for (auto& p : patratele)
            window.draw(p);

        window.display();
    }

    return 0;
}
