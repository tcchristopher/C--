#include <SFML/Graphics.hpp>
int main()
{
    sf::RenderWindow window(sf::VideoMode(640, 360), "SFML 2.6 smoke test");
    window.setFramerateLimit(60);
    sf::CircleShape dot(40.f);
    dot.setFillColor(sf::Color::Green);
    float x = 0.f;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();
        x += 2.f;
        if (x > 640.f) x = -80.f;
        dot.setPosition(x, 160.f);
        window.clear(sf::Color(20, 20, 30));
        window.draw(dot);
        window.display();
    }
    return 0;
}