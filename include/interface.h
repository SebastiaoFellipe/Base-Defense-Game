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
    sf::Text endScreenText;
    sf::Text endScreenPhraseText;
    sf::Text endScreenKillsText;
    sf::Text exitText;

    void configText(sf::Text& text, sf::Font& font, std::string str, int size);
    
public:
    Interface(sf::RenderWindow& window);
    void update(int baseHealth, int playerHealth, int ammunition, int kills, int elapsedSeconds);
    void draw(sf::RenderWindow& window);
    void drawPauseScreen(sf::RenderWindow& window);
    void drawVictoryScreen(sf::RenderWindow& window, int playerKills);
    void drawDefeatScreen(sf::RenderWindow& window, int playerKills);
};

#endif // INTERFACE_H