#include "interface.h"
#include <iostream>

Interface::Interface(sf::RenderWindow& window) {
    if (!font.loadFromFile("assets/fonts/NotoSansMono.ttf")) {
        std::cerr << "Erro ao carregar a fonte." << std::endl;
        std::exit(1);
    }

    int fontSize = 20;
    float sideMargin = window.getSize().x-200.0f;
    
    baseHealthText.setFont(font);
    baseHealthText.setCharacterSize(fontSize);
    baseHealthText.setFillColor(sf::Color::Black);
    baseHealthText.setPosition(sideMargin,fontSize*1.0f);

    playerHealthText.setFont(font);
    playerHealthText.setCharacterSize(fontSize);
    playerHealthText.setFillColor(sf::Color::Black);
    playerHealthText.setPosition(sideMargin,fontSize*2.2f);

    ammunitionText.setFont(font);
    ammunitionText.setCharacterSize(fontSize);
    ammunitionText.setFillColor(sf::Color::Black);
    ammunitionText.setPosition(sideMargin,fontSize*3.4f);
    
    killsText.setFont(font);
    killsText.setCharacterSize(fontSize);
    killsText.setFillColor(sf::Color::Black);
    killsText.setPosition(sideMargin,fontSize*4.6f);

    pauseText.setFont(font);
    pauseText.setCharacterSize(46);
    pauseText.setFillColor(sf::Color::Black);
    pauseText.setString("PAUSE");
    pauseText.setStyle(sf::Text::Bold);
    pauseText.setOrigin(pauseText.getGlobalBounds().width/2,0.0f);
    pauseText.setPosition((window.getSize().x/2.0f), 50.0f);

    timerText.setFont(font);
    timerText.setCharacterSize(fontSize);
    timerText.setFillColor(sf::Color::Black);
    timerText.setString("TEMPO: 01:20");
    timerText.setOrigin(timerText.getGlobalBounds().width/2,0.0f);
    timerText.setPosition((window.getSize().x/2.0f), 20.0f);
}

void Interface::update(int baseHealth, int playerHealth, int ammunition, int kills, int elapsedSeconds){
    baseHealthText.setString("BASE: " + std::to_string(baseHealth));
    playerHealthText.setString("VIDA: " + std::to_string(playerHealth));
    ammunitionText.setString("MUNICAO: " + std::to_string(ammunition));
    killsText.setString("KILLS: " + std::to_string(kills));

    int seconds = elapsedSeconds < 20 ? 20 : 80;
    int remainingSeconds = seconds - elapsedSeconds;
    std::string minutePart = elapsedSeconds < 20 ? "01:" : "00:";
    std::string secondPart = remainingSeconds < 10 ? "0" + std::to_string(remainingSeconds) : std::to_string(remainingSeconds);

    timerText.setString("TEMPO: " + minutePart + secondPart);
}

void Interface::draw(sf::RenderWindow& window) {
    window.draw(baseHealthText);
    window.draw(playerHealthText);
    window.draw(ammunitionText);
    window.draw(killsText);
    window.draw(timerText);
}

void Interface::drawPauseScreen(sf::RenderWindow& window) {
    window.draw(pauseText);
    window.display();
}
