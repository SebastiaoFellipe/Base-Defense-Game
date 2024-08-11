#ifndef INTERFACE_H
#define INTERFACE_H

#include <SFML/Graphics.hpp>

class Interface {
private:
    sf::Font font;
    sf::Text baseHealthText;
    sf::Text playerHealthText;
    sf::Text ammunitionText;
    sf::Text killsText;
    sf::Text timerText;
    sf::Text pauseText;
    
public:
    Interface(sf::RenderWindow& window);
    void update(int baseHealth, int playerHealth, int ammunition, int kills); // falta adicionar o cronometro
    void draw(sf::RenderWindow& window);
    void drawPauseScreen(sf::RenderWindow& window);
};

#endif // INTERFACE_H