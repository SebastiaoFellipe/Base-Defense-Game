#include "game.h"
#include "player.h"
#include "bullet.h"
#include "interface.h"
#include "collision.h"
#include <iostream>
#include <cmath>
#include <chrono>
#include <memory>

Game::Game():shootingSoundLoaded(true), getLootSoundLoaded(true), backgroundMusicLoaded(true), onPause(false), elapsedSeconds(0), totalPausedTime(0), lastEnemySpawnTime(0), endGame(false) {
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    // calcula a largura e altura da janela de modo que tenha 90% da largura do monitor sendo o máximo 1600:900
    float width = desktop.width * 0.9f;
    width = width>1600 ? 1600 : width;
    float height = (width / 2.0f) + 100;
    window.create(sf::VideoMode(width, height), "Base Defense Game");
    interface = std::make_unique<Interface>(window);
    startTime = std::chrono::steady_clock::now();
    regenStartTime = std::chrono::steady_clock::now();
    initialize();
}

// função para carregar e posicionar os elementos, imagens e audios do jogo
void Game::initialize() {
    if (!texture.loadFromFile("assets/textures/player.png")) {
        std::cerr << "Erro ao carregar a textura do player." << std::endl;
        std::exit(1);
    }
    player.setBodyTexture(texture);
    player.setPositionCenter(window);
    base.setPositionCenter(window);
    if (!shootingBuffer.loadFromFile("assets/sounds/gun_pistol_silenced.wav")) {
        std::cerr << "Erro ao carregar o som do disparo. Efeito desabilitado." << std::endl;
        shootingSoundLoaded = false;
    } else {
        shootingSound.setBuffer(shootingBuffer);
        shootingSound.setVolume(20.0f);
    }
    if (!getLootBuffer.loadFromFile("assets/sounds/ammunition_box.wav")) {
        std::cerr << "Erro ao carregar o som de pegar munição. Efeito desabilitado." << std::endl;
        getLootSoundLoaded = false;
    } else {
        getLootSound.setBuffer(getLootBuffer);
        getLootSound.setVolume(20.0f);
    }
    if (!backgroundMusic.openFromFile("assets/sounds/8-Bit-Hideout!-Dark-Chiptune-Game-Music-By-HeatleyBros.wav")) {
        std::cerr << "Erro ao carregar a música de fundo." << std::endl;
        backgroundMusicLoaded = false;
    } else {
        backgroundMusic.setLoop(true);
        backgroundMusic.setVolume(20.0f);
        backgroundMusic.play();
    }
}

// função para processar os eventos na janela do jogo
void Game::processEvents(bool endGame) {
    sf::Event event;
    while (window.pollEvent(event)) {
        switch (event.type){
        case sf::Event::Closed:
            closeGame();
            break;
        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Escape){
                closeGame();
            }
            if (event.key.code == sf::Keyboard::P && !endGame){
                pause();
            }
            break;
        case sf::Event::MouseButtonPressed:
            if (!onPause && event.mouseButton.button == sf::Mouse::Left && !endGame) {
                player.shoot(shootingSound, shootingSoundLoaded, getMouseClickPosition());
            }
            break;
        default:
            break;
        }
    }
}

// função para atualizar a janela do jogo
void Game::update(float deltaTime, int elapsedSeconds) {
    checkCollisions();
    player.update(deltaTime, onPause, window);
    createEnemies(elapsedSeconds, 5, window);
    for (auto enemy : enemies){
        enemy->update(deltaTime, elapsedSeconds, onPause, shootingSound, shootingSoundLoaded, player.getPosition());
    }
    auto now = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - regenStartTime);
    if (elapsed.count() >= 1) {
        base.regeneration();
        regenStartTime = now;
    }
    lootUpdate();
    interface->update(base.getHealth(), player.getHealth(), player.getAmmunition(), player.getKills(), elapsedSeconds);
}

// função para renderizar a janela atual do jogo
void Game::render() {
    window.clear(sf::Color(221,221,221));

    base.draw(window);
    player.draw(window);
    for (auto loot : loots){
        loot->draw(window);
    }
    for (auto enemy : enemies){
        enemy->draw(window);
    }
    interface->draw(window);

    window.display();
}

// função para rodar o jogo
void Game::run() {
    std::cout << "Iniciando Base Defense Game!" << std::endl;
    auto lastTime = std::chrono::steady_clock::now();
    
    while (window.isOpen()) {
        auto now = std::chrono::steady_clock::now();
        std::chrono::duration<float> elapsedTime = now - lastTime;
        lastTime = now;
        float deltaTimeSeconds = elapsedTime.count();
        processEvents(endGame);
        if (!onPause) {
            auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - startTime) - totalPausedTime;
            elapsedSeconds = static_cast<int>(elapsed.count());
            if (elapsedSeconds < totalTimeInSeconds) {
                if (base.getHealth() == 0 || player.getHealth() == 0) {
                    endGame = true;
                    backgroundMusic.pause();
                    renderDefeatScreen(player.getKills());
                } else {
                    update(deltaTimeSeconds, elapsedSeconds);
                    render();
                }
            } else if (!endGame){
                endGame = true;
                backgroundMusic.pause();
                renderVictoryScreen(player.getKills());
            }
        }
    }

    std::cout << "Jogo encerrado." << std::endl;
}

// função para pegar posição do mouse
sf::Vector2f Game::getMouseClickPosition() {
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    return sf::Vector2f(mousePosition);
}

void Game::closeGame(){
    enemies.clear();
    loots.clear();
    window.close();
}

void Game::pause(){
    if (onPause){
        auto now = std::chrono::steady_clock::now();
        totalPausedTime += std::chrono::duration_cast<std::chrono::seconds>(now - pauseStartTime);

        backgroundMusic.play();
        window.clear(sf::Color(221,221,221));
        onPause = false;
    } else {
        pauseStartTime = std::chrono::steady_clock::now();

        backgroundMusic.pause();
        interface->drawPauseScreen(window);
        onPause = true; 
    }
}

void Game::createEnemies(int elapsedSeconds, int interval, sf::RenderWindow& window){
    if (enemies.empty()){  
        enemies.push_back(std::make_shared<Enemy>());
    }
    if (elapsedSeconds-lastEnemySpawnTime >= interval) {
        enemies.push_back(std::make_shared<Enemy>());
        lastEnemySpawnTime = elapsedSeconds;
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        int side = rand()%4+1;
        switch (side){
            case 1: {
                int positionX = rand() % window.getSize().x;
                sf::Vector2f position(static_cast<float>(positionX), 0.0f);
                enemies.back()->setPosition(position);
                break;
            }
            case 2: {
                int positionY = rand()%window.getSize().y;
                sf::Vector2f position(static_cast<float>(window.getSize().x), positionY);
                enemies.back()->setPosition(position);
                break;
            }
            case 3: {
                int positionX = rand()%window.getSize().x;
                sf::Vector2f position(static_cast<float>(positionX), static_cast<float>(window.getSize().y));
                enemies.back()->setPosition(position);
                break;
            }
            case 4: {
                int positionY = rand()%window.getSize().y;
                sf::Vector2f position(0.0f, positionY);
                enemies.back()->setPosition(position);
                break;
            }
            default:
                break;
        }
    }
}

void Game::checkCollisions() {
    // referência ao vetor de balas do jogador
    auto& playerBullets = player.getBullets();
    for (auto enemyIt = enemies.begin(); enemyIt != enemies.end(); ) {
        // referência ao vetor de balas do inimigo atual
        auto& enemyBullets = (*enemyIt)->getBullets();
        // verifica colisão entre as balas do player com o inimigo atual
        for (auto bulletIt = playerBullets.begin(); bulletIt != playerBullets.end(); ) {
            if (Collision::checkPlayerBulletHitEnemy(*bulletIt, **enemyIt)) {
                bulletIt = playerBullets.erase(bulletIt);
                dropLoot((*enemyIt)->getPosition());
                enemyBullets.clear();
                enemyIt = enemies.erase(enemyIt);
                player.incrementKills();
                break;
            } else {
                bulletIt++;
            }
        }
        // se o inimigo atual foi removido continua para o próximo
        if (enemyIt == enemies.end()) continue;
        // verifica colisão entre a bala do inimigo atual com o player ou a base
        for (auto bulletIt = enemyBullets.begin(); bulletIt != enemyBullets.end(); ) {
            if (Collision::checkBulletHitPlayer(*bulletIt, player)) {
                bulletIt = enemyBullets.erase(bulletIt);
                player.takeDamage(3);
            } else if (Collision::checkBulletHitBase(*bulletIt, base)) {
                bulletIt = enemyBullets.erase(bulletIt);
                base.takeDamage(3);
            } else {
                bulletIt++;
            }
        }
        // verifica colisão entre o inimigo atual e o player
        if (Collision::checkEnemyHitPlayer(**enemyIt, player)) {
            enemyIt = enemies.erase(enemyIt);
            player.takeDamage(5);
            continue;
        }
        // verifica colisão entre o inimigo atual e a base
        if (Collision::checkEnemyHitBase(**enemyIt, base)) {
            enemyIt = enemies.erase(enemyIt);
            base.takeDamage(5);
            continue;
        }
        enemyIt++;
    }
    for (auto loot = loots.begin(); loot != loots.end(); ) {
        if (Collision::checkPlayerGetsLoot(player, **loot)) {
            player.addAmmunition(10);
            getLootSound.play();
            loot = loots.erase(loot);
        } else {
            loot++;
        }
    }
}

void Game::dropLoot(sf::Vector2f position) {
    // 50% de chance de dropar loot
    if (rand()%2 == 0) {
        loots.push_back(std::make_shared<Loot>(position));
    }
}

void Game::lootUpdate(){
    auto now = std::chrono::steady_clock::now();
    for (auto loot = loots.begin(); loot != loots.end(); ) {
        auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - (*loot)->getTimer()).count();
        if (elapsed>10) {
            loot = loots.erase(loot);
        } else {
            loot++;
        }
    }
}

void Game::renderVictoryScreen(int playerKills){
    window.clear(sf::Color(221,221,221));
    interface->drawVictoryScreen(window, playerKills);
}

void Game::renderDefeatScreen(int playerKills){
    window.clear(sf::Color(221,221,221));
    interface->drawDefeatScreen(window, playerKills);
}