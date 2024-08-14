#include "game.h"
#include "player.h"
#include "bullet.h"
#include "interface.h"
#include <iostream>
#include <cmath>
#include <chrono>

Game::Game() {
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    // calcula a largura e altura da janela de modo que tenha 90% da largura do monitor sendo o máximo 1600:900
    float width = desktop.width * 0.9f;
    width = width>1600 ? 1600 : width;
    float height = (width / 2.0f) + 100;
    window.create(sf::VideoMode(width, height), "Base Defense Game");
    interface = new Interface(window);
    startTime = std::chrono::steady_clock::now();
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
    if (!playerShootingBuffer.loadFromFile("assets/sounds/gun_pistol_silenced.wav")) {
        std::cerr << "Erro ao carregar o som do disparo. Efeito desabilitado." << std::endl;
        playerShootingSoundLoaded = false;
    } else {
        playerShootingSound.setBuffer(playerShootingBuffer);
        playerShootingSound.setVolume(20.0f);
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
void Game::processEvents() {
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
            if (event.key.code == sf::Keyboard::P){
                pause();
            }
            break;
        case sf::Event::MouseButtonPressed:
            if (!onPause && event.mouseButton.button == sf::Mouse::Left) {
                player.shoot(playerShootingSound, playerShootingSoundLoaded, getMouseClickPosition());
            }
            break;
        default:
            break;
        }
    }
}

// função para atualizar a janela do jogo
void Game::update(float deltaTime, int elapsedSeconds) {
    player.update(deltaTime, onPause, window);
    createEnemies(elapsedSeconds, 2, window);
    for (Enemy* enemy : enemies){
        enemy->update(deltaTime, player.getPosition());
    }
    interface->update(base.getHealth(), player.getHealth(), player.getAmmunition(), player.getKills(), elapsedSeconds);
}

// função para renderizar a janela atual do jogo
void Game::render() {
    window.clear(sf::Color(221,221,221));

    base.draw(window);
    player.draw(window);
    interface->draw(window);
    for (Enemy* enemy : enemies){
        enemy->draw(window);
    }

    window.display();
}

// função para rodar o jogo
void Game::run() {
    std::cout << "Iniciando Base Defense Game!" << std::endl;
    sf::Clock deltaTimeClock;
    
    while (window.isOpen()) {
        sf::Time deltaTime = deltaTimeClock.restart();
        float deltaTimeSeconds = deltaTime.asSeconds();
        int totalTimeInSeconds = 81;
        processEvents();
        if (!onPause) {
            auto now = std::chrono::steady_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - startTime) - totalPausedTime;
            elapsedSeconds = static_cast<int>(elapsed.count());
            if (elapsedSeconds < totalTimeInSeconds) {
                update(deltaTimeSeconds, elapsedSeconds);
                render();
            } else {
                std::cout << "Acabou o tempo." << std::endl;
                break;
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
    player.deleteBullets();
    for (Enemy* enemy : enemies) {
        delete enemy;
    }
    enemies.clear();
    delete interface;
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
        enemies.push_back(new Enemy());
    }
    if (elapsedSeconds-lastEnemySpawnTime >= interval) {
        enemies.push_back(new Enemy());
        lastEnemySpawnTime = elapsedSeconds;
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