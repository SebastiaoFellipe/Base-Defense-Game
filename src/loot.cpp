#include "loot.h"

Loot::Loot(sf::Vector2f& position) : position(position) {
    timer = std::chrono::steady_clock::now();
    body.setPosition(position);
    body.setSize(sf::Vector2f(20.0f, 20.0f));
    body.setOrigin(10.0f,10.0f);
    body.setFillColor(sf::Color(92,64,51));
}

void Loot::draw(sf::RenderWindow& window){
    window.draw(body);
}

bool Loot::isExpired(){
    auto now = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - timer).count();
    return elapsed > 10;
}

sf::Vector2f Loot::getPosition(){
    return position;
}

std::chrono::steady_clock::time_point Loot::getTimer(){
    return timer;
}

sf::FloatRect Loot::getBody(){
    return body.getGlobalBounds();
}
