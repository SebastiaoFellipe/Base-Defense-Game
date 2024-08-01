#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>

class Game {
public:
    Game();
    void run();

private:
    sf::RenderWindow Window;
    sf::Font Font;
    sf::Text Text;

    void processEvents();
    void update();
    void render();
    void initialize();
    void getKeyboardEvent(const sf::Event& event);
    void getMouseClickPosition();
};

#endif // GAME_H
