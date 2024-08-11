#ifndef BASE_H
#define BASE_H

#include <SFML/Graphics.hpp>

class Base {
private:
    int health;
    sf::RectangleShape shape;
    sf::Vector2f position;

public:
    Base();
    void draw(sf::RenderWindow& window);
    void setPositionCenter(sf::RenderWindow& window);
    int getHealth();
};

#endif // BASE_H