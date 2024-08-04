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
    // void takeDamage(int damage);
    // void regenerate();
};

#endif // BASE_H