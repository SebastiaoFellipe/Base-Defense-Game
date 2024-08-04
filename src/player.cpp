#include "player.h"
#include <cmath>
#include <iostream>

Player::Player():health(100),ammunition(50),position(600.0f,300.0f),speed(200){ 
    sprite.setPosition(position);
    sprite.setOrigin(50.0f,50.0f);
    sprite.setScale(0.6f, 0.6f);
}

void Player::updatePosition(float deltaTime) {
    sf::Vector2f direction(0.0f, 0.0f); 
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        direction.y -= 1.0f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        direction.y += 1.0f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        direction.x -= 1.0f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        direction.x += 1.0f;
    }
    if (direction.x != 0.0f || direction.y != 0.0f) {
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        direction /= length;
    }
    sprite.move(direction * (speed * deltaTime));
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

void Player::setSpriteTexture(sf::Texture& texture){
    sprite.setTexture(texture);
}

void Player::rotateTowardsMouse(sf::RenderWindow& window) {
    const float PI = 3.14;
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f playerPos = sprite.getPosition();
    sf::Vector2f direction = sf::Vector2f(mousePos.x, mousePos.y) - playerPos;
    float angle = (std::atan2(direction.y, direction.x) * 180 / PI)-90.0f;
    sprite.setRotation(angle);
}