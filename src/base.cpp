#include "base.h"

Base::Base() : health(100) {
    float shapeWidth = 300.0f, shapeLenght = 150.0f;
    shape.setSize(sf::Vector2f(shapeWidth, shapeLenght));
    shape.setFillColor(sf::Color(0, 0, 0, 0));
    shape.setPosition(600.0f-(shapeWidth/2),300.0f-(shapeLenght/2));
    shape.setOutlineColor(sf::Color::Green);
    shape.setOutlineThickness(10.0f);  
}

void Base::draw(sf::RenderWindow& window){
    window.draw(shape);
}

void Base::takeDamage(int amount) {
    health -= amount;
    if (health < 0) {
        health = 0;
    }
}

void Base::regenerate() {
    if (health < 100) {
        health += 1;
    }
}


