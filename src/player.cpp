#include "player.h"
#include <cmath>
#include <iostream>

Player::Player():health(100),ammunition(50),position(600.0f,300.0f),speed(400){ 
    body.setOrigin(50.0f,50.0f);
    body.setScale(0.6f, 0.6f);
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
    body.move(direction * (speed * deltaTime));
}

sf::Vector2f Player::getPosition(){
    return body.getPosition();
}

void Player::setPositionCenter(sf::RenderWindow& window){
    body.setPosition(window.getSize().x/2,window.getSize().y/2);
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(body);
}

void Player::setBodyTexture(sf::Texture& texture){
    body.setTexture(texture);
}

void Player::rotateTowardsMouse(sf::RenderWindow& window) {
    const float PI = 3.14;
    sf::Vector2f worldMousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    sf::Vector2f playerPos = body.getPosition();
    sf::Vector2f direction = worldMousePos - playerPos;
    float angle = (std::atan2(direction.y, direction.x) * 180 / PI)-90.0f;
    body.setRotation(angle);
}

void Player::checkWallCollision(float deltaTime, const sf::Vector2u& windowSize) {
    sf::Vector2f position = body.getPosition();
    sf::FloatRect bounds = body.getGlobalBounds();
    sf::Vector2f size(bounds.width, bounds.height);
    if (position.x < 5) {
        position.x = 5;
    }
    if (position.y < 5) {
        position.y = 5;
    }
    if (position.x + size.x/100.0f> windowSize.x-5) {
        position.x = (windowSize.x-size.x/100.0f)-5;
    }
    if (position.y + size.y/100.0f > windowSize.y-5) {
        position.y = (windowSize.y-size.y/100.0f)-5;
    }
    body.setPosition(position);
}