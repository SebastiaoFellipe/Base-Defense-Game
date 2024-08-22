#ifndef LOOT_H
#define LOOT_H

#include <SFML/Graphics.hpp>
#include <chrono>

class Loot {
private:
    sf::Vector2f position;
    std::chrono::steady_clock::time_point timer;
    sf::RectangleShape body;

public:
    Loot(sf::Vector2f& position);
    void draw(sf::RenderWindow& window);
    bool isExpired();
    sf::Vector2f getPosition();
    std::chrono::steady_clock::time_point getTimer();
    sf::FloatRect getBody();
};

#endif // LOOT_H
