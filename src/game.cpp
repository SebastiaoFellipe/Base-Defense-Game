#include "game.h"
#include "player.h"
#include "bullet.h"
#include "interface.h"
#include <iostream>
#include <cmath>

Game::Game() {
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    // calcula a largura e altura da janela de modo que tenha 90% da largura do monitor sendo o máximo 1600:900
    float width = desktop.width * 0.9f;
    width = width>1600 ? 1600 : width;
    float height = (width / 2.0f) + 100;
    window.create(sf::VideoMode(width, height), "Base Defense Game");
    interface = new Interface(window);
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
    if (elapsedSeconds-lastEnemySpawnTime >= 10.0f) {
        enemies.push_back(new Enemy());
        lastEnemySpawnTime = elapsedSeconds;
    }
    for (Enemy* enemy : enemies){
        enemy->updatePosition(deltaTime, player.getPosition());
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
        int elapsedSeconds = static_cast<int>(mainClock.getElapsedTime().asSeconds());
        int totalTimeInSeconds = 80;
        processEvents();
        if (!onPause) {
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
    window.close();
}

void Game::pause(){
    if (onPause){
        backgroundMusic.play();
        window.clear(sf::Color(221,221,221));
        onPause = false;
    } else {
        backgroundMusic.pause();
        interface->drawPauseScreen(window);
        onPause = true; 
    }
}