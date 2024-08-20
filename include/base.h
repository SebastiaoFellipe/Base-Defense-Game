#ifndef BASE_H
#define BASE_H

#include <SFML/Graphics.hpp>

class Base {
private:
    int health;
    sf::RectangleShape body;
    sf::Vector2f position;

public:
    Base();
    void draw(sf::RenderWindow& window);
    void setPositionCenter(sf::RenderWindow& window);
    int getHealth();
    sf::FloatRect getBody();
    void takeDamage(int damage);
};

#endif // BASE_H