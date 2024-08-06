#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "SFML/Audio.hpp"
#include "bullet.h"

class Player {
private:
    int health;
    int ammunition;
    sf::Vector2f position;
    int speed;
    sf::Sprite body;
    sf::Texture texture;
    std::vector<Bullet*> bullets;

public:
    Player();
    void update(float deltaTime, bool onPause, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
    void updatePosition(float deltaTime);
    sf::Vector2f getPosition();
    void setPositionCenter(sf::RenderWindow& window);
    void setBodyTexture(sf::Texture& texture);
    void rotateTowardsMouse(sf::RenderWindow& window);
    void checkWallCollision(float deltaTime, const sf::Vector2u& windowSize);
    void shoot(sf::Sound& playerShootingSound, bool playerShootingSoundLoaded, sf::Vector2f mousePos);
    void deleteBullets();
    // void takeDamage(int damage);
    
};

#endif // PLAYER_H