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
#include <memory>

class Game {
private:
    sf::RenderWindow window;
    sf::Font font;
    sf::Texture texture;
    sf::Text text;
    sf::SoundBuffer shootingBuffer;
    sf::Sound shootingSound;
    bool shootingSoundLoaded = true;
    sf::Music backgroundMusic;
    bool backgroundMusicLoaded = true;
    bool onPause = false;
    int elapsedSeconds;
    std::chrono::steady_clock::time_point startTime;
    std::chrono::steady_clock::time_point pauseStartTime;
    std::chrono::seconds totalPausedTime{0};
    int lastEnemySpawnTime = 0;
    sf::Clock regenClock;

    Base base;
    Player player;
    std::vector<std::shared_ptr<Enemy>> enemies;
    std::unique_ptr<Interface> interface;

    void processEvents();
    void update(float deltaTime, int elapsedSeconds);
    void render();
    void initialize();
    sf::Vector2f getMouseClickPosition();
    void closeGame();
    void pause();
    void createEnemies(int elapsedSeconds, int interval, sf::RenderWindow& window);
    void checkCollisions();

public:
    Game();
    void run();
};

#endif // GAME_H