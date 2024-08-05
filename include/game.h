#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "base.h"
#include "player.h"
#include "bullet.h"

class Game {
private:
    sf::RenderWindow window;
    sf::Font font;
    sf::Texture texture;
    sf::Text text;
    bool onPause = false;

    Base base;
    Player player;
    // std::vector<Enemy> enemies;
    std::vector<Bullet*> bullets;
    // Interface interface;

    void processEvents();
    void update(float deltaTime);
    void render();
    void initialize();
    sf::Vector2f getMouseClickPosition();
    void closeGame();
    void pause();

public:
    Game();
    void run();
};

#endif // GAME_H