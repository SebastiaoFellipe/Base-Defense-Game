#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

class Player {
private:
    int health;
    int ammunition;
    sf::Vector2f position;
    int speed;
    sf::Sprite body;
    sf::Texture texture;

public:
    Player();
    void draw(sf::RenderWindow& window);
    void updatePosition(float deltaTime);
    sf::Vector2f getPosition();
    void setPositionCenter(sf::RenderWindow& window);
    void setBodyTexture(sf::Texture& texture);
    void rotateTowardsMouse(sf::RenderWindow& window);
    void checkWallCollision(float deltaTime, const sf::Vector2u& windowSize);
    // void shoot();
    // void takeDamage(int damage);
    
};

#endif // PLAYER_H