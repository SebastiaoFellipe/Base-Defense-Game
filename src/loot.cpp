#include "loot.h"

Loot::Loot(sf::Vector2f& position) : position(position) {
    timer.restart();
    body.setPosition(position);
    body.setSize(sf::Vector2f(20.0f, 20.0f));
    body.setOrigin(10.0f,10.0f);
    body.setFillColor(sf::Color(92,64,51));
}

void Loot::draw(sf::RenderWindow& window){
    window.draw(body);
}

bool Loot::isExpired(){
    return timer.getElapsedTime().asSeconds() > 10.0f;
}

sf::Vector2f Loot::getPosition(){
    return position;
}

sf::Clock Loot::getTimer(){
    return timer;
}
