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
    sf::View view;

    Base base;
    Player player;
    // std::vector<Enemy> enemies;
    // std::vector<Bullet> bullets;
    // Interface interface;

    void processEvents();
    void update(float deltaTime);
    void render();
    void initialize();
    void getMouseClickPosition();

public:
    Game();
    void run();
};

#endif // GAME_H