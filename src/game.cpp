#include "game.h"
#include "player.h"
#include <iostream>

Game::Game():window(sf::VideoMode(1200, 600), "Base Defense Game") {
    window.setVerticalSyncEnabled(true);
    initialize();
}

// função para carregar fontes, imagens e audios do jogo
void Game::initialize() {
    if (!font.loadFromFile("assets/fonts/Minecraftia-Regular.ttf")) {
        std::cerr << "Erro ao carregar a fonte." << std::endl;
        std::exit(1);
    }
    if (!texture.loadFromFile("assets/img/player.png")) {
        std::cerr << "Erro ao carregar a textura do player." << std::endl;
        std::exit(1);
    }
    player.setSpriteTexture(texture);
}

// função para processar os eventos na janela do jogo
void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        switch (event.type){
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Escape){
                window.close();
            }
            if (event.key.code == sf::Keyboard::P){
                // pausar
            }
            break;
        case sf::Event::MouseButtonPressed:
            if (event.mouseButton.button == sf::Mouse::Left) {
                getMouseClickPosition();
            }
            break;
        default:
            break;
        }
    }
}

// função para atualizar a janela do jogo
void Game::update(float deltaTime) {
    player.updatePosition(deltaTime);
    player.rotateTowardsMouse(window);
}

// função para renderizar a janela atual do jogo
void Game::render() {
    sf::Color customColor(221, 221, 221); 
    window.clear(customColor);

    base.draw(window);
    player.draw(window);

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
        update(deltaTimeSeconds);
        render();
    }
    std::cout << "Jogo encerrado." << std::endl;
}

// função para pegar posição do mouse
void Game::getMouseClickPosition() {
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    std::cout << "Mouse clicado na posição (" << mousePosition.x << ", " << mousePosition.y << ")" << std::endl;
}