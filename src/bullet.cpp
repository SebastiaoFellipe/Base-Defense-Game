#include "bullet.h"
#include <cmath>

Bullet::Bullet(sf::Vector2f& startPosition, sf::Vector2f& mousePosition): speed(400), maxDistance(1000.0f), traveledDistance(0.0f) {
    body.setRadius(3.0f);
    body.setFillColor(sf::Color::Black);
    body.setPosition(startPosition);
    this->startPosition = startPosition;
    direction = mousePosition - startPosition;
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length != 0.0f) {
        direction /= length;
    }
}

void Bullet::update(float deltaTime) {
    sf::Vector2f movement = direction * speed * deltaTime;
    body.move(movement);
}

void Bullet::draw(sf::RenderWindow& window) {
    window.draw(body);
}

bool Bullet::checkBulletDistanceLimit() {
    float distanceFromStart = std::sqrt(std::pow(body.getPosition().x - startPosition.x, 2)+std::pow(body.getPosition().y-startPosition.y, 2));
    return distanceFromStart >= maxDistance;
}

sf::FloatRect Bullet::getBody(){
    return body.getGlobalBounds();
}