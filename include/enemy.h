#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include "SFML/Audio.hpp"
#include "bullet.h"
#include <vector>

class Enemy {
private:
    sf::Vector2f position;
    int speed;
    sf::RectangleShape body;
    sf::Texture texture;
    std::vector<Bullet*> bullets;

public:
    Enemy();
    void draw(sf::RenderWindow& window);
    void updatePosition(float deltaTime, sf::Vector2f playerPosition);

};

#endif // ENEMY_H