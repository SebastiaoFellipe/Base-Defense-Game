#include "enemy.h"
#include <cmath>

Enemy::Enemy() : speed(50) {
    body.setSize(sf::Vector2f(30.0f, 30.0f));
    body.setFillColor(sf::Color::Red);
    body.setPosition(10.0f,10.0f);
    body.setOrigin(15.0f,15.0f);
}

void Enemy::updatePosition(float deltaTime, sf::Vector2f playerPosition) {
    sf::Vector2f direction = playerPosition - body.getPosition();
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length != 0) {
        direction /= length;
    }
    body.move(direction * (speed * deltaTime));
}

void Enemy::draw(sf::RenderWindow& window) {
    window.draw(body);
}
