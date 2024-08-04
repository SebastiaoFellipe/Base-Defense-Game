#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>

class Bullet {
private:
    sf::CircleShape body;
    sf::Vector2f direction;
    float speed;
    sf::Vector2f startPosition;
    float maxDistance;
    float traveledDistance;

public:
    Bullet(sf::Vector2f& startPosition, sf::Vector2f& mousePosition);
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
    bool checkBulletDistanceLimit();
};

#endif // BULLET_H
