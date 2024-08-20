#include "base.h"

const float SHAPE_WIDHT = 300.0f, SHAPE_HEIGHT = 150.0f;

Base::Base():health(100) {
    body.setSize(sf::Vector2f(SHAPE_WIDHT, SHAPE_HEIGHT));
    body.setFillColor(sf::Color(141, 153, 174));
    body.setOutlineColor(sf::Color::Green);
    body.setOutlineThickness(10.0f);  
}

void Base::draw(sf::RenderWindow& window){
    window.draw(body);
}

void Base::setPositionCenter(sf::RenderWindow& window){
    sf::Vector2u position = window.getSize();
    body.setPosition((position.x/2)-(SHAPE_WIDHT/2),(position.y/2)-(SHAPE_HEIGHT/2));
}

int Base::getHealth(){
    return health;
}

sf::FloatRect Base::getBody(){
    return body.getGlobalBounds();
}