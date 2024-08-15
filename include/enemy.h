#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include "SFML/Audio.hpp"
#include "bullet.h"
#include <vector>
#include <memory>

class Enemy {
private:
    sf::Vector2f position;
    int speed;
    sf::RectangleShape body;
    sf::Texture texture;
    std::vector<std::shared_ptr<Bullet>> bullets;
    int lastBulletFired = 0;

public:
    Enemy();
    void update(float deltaTime, int elapsedSeconds, bool onPause, sf::Sound& shootingSound, bool shootingSoundLoaded, sf::Vector2f playerPosition);
    void draw(sf::RenderWindow& window);
    void updatePosition(float deltaTime, sf::Vector2f playerPosition);
    void setPosition(sf::Vector2f position);
    void shoot(sf::Sound& shootingSound, bool shootingSoundLoaded, sf::Vector2f playerPos);

};

#endif // ENEMY_H