#include "game.h"
#include "player.h"
#include "bullet.h"
#include "interface.h"
#include <iostream>

Game::Game() {
    // verificar se tera conflito com a textura de fundo do jogo futuramente
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    // calcula a largura e altura da janela de modo que tenha 90% da largura do monitor e mantenha a proporção 1:2
    float width = desktop.width * 0.9f;
    float height = width / 2.0f;
    window.create(sf::VideoMode(width, height), "Base Defense Game");
    interface = new Interface(window);
    initialize();
}

// função para carregar os elementos, imagens e audios do jogo
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
void Game::update(float deltaTime) {
    player.update(deltaTime, onPause, window);
    interface->update(base.getHealth(), player.getHealth(), player.getAmmunition(), player.getKills());
}

// função para renderizar a janela atual do jogo
void Game::render() {
    window.clear(sf::Color(221,221,221));

    base.draw(window);
    player.draw(window);
    interface->draw(window);

    window.display();
}

// função para rodar o jogo
void Game::run() {
    std::cout << "Iniciando Base Defense Game!" << std::endl;
    sf::Clock clock;
    
    while (window.isOpen()) {
        sf::Time deltaTime = clock.restart();
        float deltaTimeSeconds = deltaTime.asSeconds();
        processEvents();
        if (!onPause){
            update(deltaTimeSeconds);
            render();
        }
        
    }
    // sf::Time parada = clock.getElapsedTime();
    // float seconds = parada.asSeconds();
    // std::cout << seconds << std::endl;
    
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