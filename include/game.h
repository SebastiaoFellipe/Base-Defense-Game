#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "base.h"
#include "player.h"
#include "bullet.h"
#include "interface.h"
#include "enemy.h"

class Game {
private:
    sf::RenderWindow window;
    sf::Font font;
    sf::Texture texture;
    sf::Text text;
    sf::SoundBuffer playerShootingBuffer;
    sf::Sound playerShootingSound;
    bool playerShootingSoundLoaded = true;
    sf::Music backgroundMusic;
    bool backgroundMusicLoaded = true;
    bool onPause = false;
    sf::Clock mainClock;
    float lastEnemySpawnTime = 0.0f;

    Base base;
    Player player;
    std::vector<Enemy*> enemies;
    Interface* interface;

    void processEvents();
    void update(float deltaTime, int elapsedSeconds);
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