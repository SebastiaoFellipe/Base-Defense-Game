#include "interface.h"
#include <iostream>

Interface::Interface(sf::RenderWindow& window) {
    if (!font.loadFromFile("assets/fonts/NotoSansMono.ttf")) {
        std::cerr << "Erro ao carregar a fonte." << std::endl;
        std::exit(1);
    }

    int fontSize = 20;
    float sideMargin = window.getSize().x-200.0f;
    
    configText(baseHealthText, font, "", fontSize);
    baseHealthText.setPosition(sideMargin,fontSize*1.0f);

    configText(playerHealthText, font, "", fontSize);
    playerHealthText.setPosition(sideMargin,fontSize*2.2f);

    configText(ammunitionText, font, "", fontSize);
    ammunitionText.setPosition(sideMargin,fontSize*3.4f);
    
    configText(killsText, font, "", fontSize);
    killsText.setPosition(sideMargin,fontSize*4.6f);

    configText(pauseText, font, "PAUSE", 46);
    pauseText.setStyle(sf::Text::Bold);
    pauseText.setOrigin(pauseText.getGlobalBounds().width/2,0.0f);
    pauseText.setPosition((window.getSize().x/2.0f), 50.0f);

    configText(timerText, font, "TEMPO: 01:20", fontSize);
    timerText.setOrigin(timerText.getGlobalBounds().width/2,0.0f);
    timerText.setPosition((window.getSize().x/2.0f), 20.0f);

    configText(exitText, font, "Pressione \"esc\" para sair", 16);
    exitText.setStyle(sf::Text::Bold);
    exitText.setOrigin(exitText.getGlobalBounds().width/2, exitText.getGlobalBounds().height/2);
    exitText.setPosition(window.getSize().x/2.0f, window.getSize().y - 30.0f);
}

void Interface::configText(sf::Text& text, sf::Font& font, std::string str, int size) {
    text.setFont(font);
    text.setCharacterSize(size);
    text.setString(str);
    text.setFillColor(sf::Color::Black);
}

void Interface::update(int baseHealth, int playerHealth, int ammunition, int kills, int elapsedSeconds){
    baseHealthText.setString("BASE: " + std::to_string(baseHealth));
    playerHealthText.setString("VIDA: " + std::to_string(playerHealth));
    ammunitionText.setString("MUNICAO: " + std::to_string(ammunition));
    killsText.setString("KILLS: " + std::to_string(kills));

    int seconds = elapsedSeconds < 21 ? 20 : 80;
    int remainingSeconds = seconds - elapsedSeconds;
    std::string minutePart = elapsedSeconds < 21 ? "01:" : "00:";
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

void Interface::drawVictoryScreen(sf::RenderWindow& window, int playerKills){
    configText(endScreenText, font, "Parabens!", 46);
    endScreenText.setStyle(sf::Text::Bold);
    endScreenText.setOrigin(endScreenText.getGlobalBounds().width/2, endScreenText.getGlobalBounds().height/2);
    endScreenText.setPosition(window.getSize().x/2.0f, window.getSize().y/2.0f - 90.0f);

    configText(endScreenPhraseText, font, "Voce protegeu a base dentro do tempo!", 32);
    endScreenPhraseText.setStyle(sf::Text::Bold);
    endScreenPhraseText.setOrigin(endScreenPhraseText.getGlobalBounds().width/2, endScreenPhraseText.getGlobalBounds().height/2);
    endScreenPhraseText.setPosition(window.getSize().x/2.0f, window.getSize().y/2.0f - 30.0f);

    configText(endScreenKillsText, font, "", 32);
    endScreenKillsText.setStyle(sf::Text::Bold);
    endScreenKillsText.setPosition(window.getSize().x/2.0f, window.getSize().y/2.0f + 16.0f);

    endScreenKillsText.setString("Kills: " + std::to_string(playerKills));
    endScreenKillsText.setOrigin(endScreenKillsText.getGlobalBounds().width/2, endScreenKillsText.getGlobalBounds().height/2);

    window.draw(endScreenText);
    window.draw(endScreenPhraseText);
    window.draw(endScreenKillsText);
    window.draw(exitText);
    window.display();
}

void Interface::drawDefeatScreen(sf::RenderWindow& window, int playerKills){
    configText(endScreenText, font, "Derrota!", 46);
    endScreenText.setStyle(sf::Text::Bold);
    endScreenText.setOrigin(endScreenText.getGlobalBounds().width/2, endScreenText.getGlobalBounds().height/2);
    endScreenText.setPosition(window.getSize().x/2.0f, window.getSize().y/2.0f - 90.0f);

    configText(endScreenPhraseText, font, "mais sorte na proxima!", 32);
    endScreenPhraseText.setStyle(sf::Text::Bold);
    endScreenPhraseText.setOrigin(endScreenPhraseText.getGlobalBounds().width/2, endScreenPhraseText.getGlobalBounds().height/2);
    endScreenPhraseText.setPosition(window.getSize().x/2.0f, window.getSize().y/2.0f - 30.0f);

    configText(endScreenKillsText, font, "", 32);
    endScreenKillsText.setStyle(sf::Text::Bold);
    endScreenKillsText.setPosition(window.getSize().x/2.0f, window.getSize().y/2.0f + 16.0f);

    endScreenKillsText.setString("Kills: " + std::to_string(playerKills));
    endScreenKillsText.setOrigin(endScreenKillsText.getGlobalBounds().width/2, endScreenKillsText.getGlobalBounds().height/2);

    window.draw(endScreenText);
    window.draw(endScreenPhraseText);
    window.draw(endScreenKillsText);
    window.draw(exitText);
    window.display();
}