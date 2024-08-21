#ifndef LOOT_H
#define LOOT_H

#include <SFML/Graphics.hpp>

class Loot {
private:
    sf::Vector2f position;
    sf::Clock timer;
    sf::RectangleShape body;

public:
    Loot(sf::Vector2f& position);
    void draw(sf::RenderWindow& window);
    bool isExpired();
    sf::Vector2f getPosition();
    sf::Clock getTimer();
};

#endif // LOOT_H
