#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

class Player {
private:
    int health;
    int ammunition;
    sf::Vector2f position;
    int speed;
    sf::Sprite sprite;
    sf::Texture texture;

public:
    Player();
    void draw(sf::RenderWindow& window);
    void updatePosition(float deltaTime);
    void setSpriteTexture(sf::Texture& texture);
    void rotateTowardsMouse(sf::RenderWindow& window);
    // void shoot();
    // void takeDamage(int damage);
    // void update();
};

#endif // PLAYER_H