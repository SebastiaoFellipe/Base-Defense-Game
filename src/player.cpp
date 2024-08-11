#include "player.h"
#include <cmath>
#include <iostream>
#include <SFML/Audio.hpp>

Player::Player():health(100),ammunition(50),position(600.0f,300.0f),speed(200),kills(0){ 
    body.setOrigin(50.0f,50.0f);
    body.setScale(0.6f, 0.6f);
}

void Player::update(float deltaTime, bool onPause, sf::RenderWindow& window){
    updatePosition(deltaTime);
    rotateTowardsMouse(window);
    checkWallCollision(deltaTime, window.getSize());
    for (auto bulletIterator = bullets.begin(); bulletIterator != bullets.end();) {
        if (!onPause) {
            (*bulletIterator)->update(deltaTime);
        }
        if ((*bulletIterator)->checkBulletDistanceLimit()) {
            delete *bulletIterator;
            bulletIterator = bullets.erase(bulletIterator);
        } else {
            bulletIterator++;
        }
    }
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
    float length = direction.x * direction.x + direction.y * direction.y;
    if (length != 0.0f) {
        direction /= std::sqrt(length);
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
    for (Bullet* bullet : bullets) {
        bullet->draw(window);
    }
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

void Player::shoot(sf::Sound& playerShootingSound, bool playerShootingSoundLoaded, sf::Vector2f mousePos){
    if (ammunition > 0) {
        if (playerShootingSoundLoaded) {
            playerShootingSound.play();
        }
        sf::Vector2f playerPos = getPosition();
        bullets.push_back(new Bullet(playerPos, mousePos));
        ammunition--;
    }
}

void Player::deleteBullets(){
    for (Bullet* bullet : bullets) {
        delete bullet;
    }
    bullets.clear();
}

int Player::getHealth(){
    return health;
}

int Player::getAmmunition(){
    return ammunition;
}

int Player::getKills(){
    return kills;
}