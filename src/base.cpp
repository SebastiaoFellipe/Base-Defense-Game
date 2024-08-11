#include "base.h"

const float SHAPE_WIDHT = 300.0f, SHAPE_HEIGHT = 150.0f;

Base::Base():health(100) {
    shape.setSize(sf::Vector2f(SHAPE_WIDHT, SHAPE_HEIGHT));
    shape.setFillColor(sf::Color(141, 153, 174));
    shape.setOutlineColor(sf::Color::Green);
    shape.setOutlineThickness(10.0f);  
}

void Base::draw(sf::RenderWindow& window){
    window.draw(shape);
}

void Base::setPositionCenter(sf::RenderWindow& window){
    sf::Vector2u position = window.getSize();
    shape.setPosition((position.x/2)-(SHAPE_WIDHT/2),(position.y/2)-(SHAPE_HEIGHT/2));
}

int Base::getHealth(){
    return health;
}