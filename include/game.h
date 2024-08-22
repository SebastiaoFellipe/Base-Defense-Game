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
#include "loot.h"
#include <memory>

class Game {
private:
    sf::RenderWindow window;
    sf::Font font;
    sf::Texture texture;
    sf::Text text;
    sf::SoundBuffer shootingBuffer;
    sf::Sound shootingSound;
    bool shootingSoundLoaded;
    sf::SoundBuffer getLootBuffer;
    sf::Sound getLootSound;
    bool getLootSoundLoaded;
    sf::Music backgroundMusic;
    bool backgroundMusicLoaded;
    bool onPause;
    int elapsedSeconds;
    int totalTimeInSeconds = 81;
    std::chrono::steady_clock::time_point startTime;
    std::chrono::steady_clock::time_point pauseStartTime;
    std::chrono::seconds totalPausedTime;
    int lastEnemySpawnTime;
    std::chrono::steady_clock::time_point regenStartTime;
    bool endGame;

    Base base;
    Player player;
    std::vector<std::shared_ptr<Enemy>> enemies;
    std::vector<std::shared_ptr<Loot>> loots;
    std::unique_ptr<Interface> interface;

    void processEvents(bool endGame);
    void update(float deltaTime, int elapsedSeconds);
    void render();
    void initialize();
    sf::Vector2f getMouseClickPosition();
    void closeGame();
    void pause();
    void createEnemies(int elapsedSeconds, int interval, sf::RenderWindow& window);
    void checkCollisions();
    void dropLoot(sf::Vector2f position);
    void lootUpdate();
    void renderVictoryScreen(int playerKills);
    void renderDefeatScreen(int playerkills);

public:
    Game();
    void run();
};

#endif // GAME_H