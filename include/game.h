#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <chrono>
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
    int elapsedSeconds;
    std::chrono::steady_clock::time_point startTime;
    std::chrono::steady_clock::time_point pauseStartTime;
    std::chrono::seconds totalPausedTime{0};
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
    void createEnemies(int elapsedSeconds, int interval, sf::RenderWindow& window);

public:
    Game();
    void run();
};

#endif // GAME_H