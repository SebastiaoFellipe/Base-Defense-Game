#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "SFML/Audio.hpp"
#include "bullet.h"
#include <memory>

class Player {
private:
    int health;
    int ammunition;
    sf::Vector2f position;
    int speed;
    sf::Sprite body;
    sf::Texture texture;
    std::vector<std::shared_ptr<Bullet>> bullets;
    int kills;

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
    void shoot(sf::Sound& shootingSound, bool shootingSoundLoaded, sf::Vector2f mousePos);
    int getHealth();
    int getAmmunition();
    int getKills();
    sf::FloatRect getBody();
    std::vector<std::shared_ptr<Bullet>>& getBullets();
    void takeDamage(int damage);
    void incrementKills();
    void addAmmunition(int ammunition);
};

#endif // PLAYER_H