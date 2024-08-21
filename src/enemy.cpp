#include "enemy.h"
#include <cmath>
#include <memory>

Enemy::Enemy() : speed(50) {
    body.setSize(sf::Vector2f(30.0f, 30.0f));
    body.setFillColor(sf::Color::Red);
    body.setOrigin(15.0f,15.0f);
}

void Enemy::update(float deltaTime, int elapsedSeconds, bool onPause, sf::Sound& shootingSound, bool shootingSoundLoaded, sf::Vector2f playerPosition){
    updatePosition(deltaTime, playerPosition);
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    int interval = std::rand() % 3 + 4;
    if (elapsedSeconds-lastBulletFired >= interval) {
        lastBulletFired = elapsedSeconds;
        shoot(shootingSound, shootingSoundLoaded, playerPosition);
    }
    for (auto bullet = bullets.begin(); bullet != bullets.end();) {
        if (*bullet) {
            (*bullet)->update(deltaTime);
            if ((*bullet)->checkBulletDistanceLimit()) {
                bullet = bullets.erase(bullet);
            } else {
                bullet++;
            }
        } else {
            bullet = bullets.erase(bullet);
        }
    }
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
    for (auto bullet : bullets) {
        bullet->draw(window);
    }
    window.draw(body);
}

void Enemy::setPosition(sf::Vector2f position){
    body.setPosition(position);
}

void Enemy::shoot(sf::Sound& shootingSound, bool shootingSoundLoaded, sf::Vector2f playerPos){
    if (shootingSoundLoaded) {
        shootingSound.play();
    }
    sf::Vector2f enemyPos = body.getPosition();
    bullets.push_back(std::make_shared<Bullet>(enemyPos, playerPos));
}

sf::FloatRect Enemy::getBody(){
    return body.getGlobalBounds();
}

std::vector<std::shared_ptr<Bullet>>& Enemy::getBullets(){
    return bullets;
}

sf::Vector2f Enemy::getPosition(){
    return body.getPosition();
}