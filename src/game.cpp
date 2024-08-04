#include "game.h"
#include "player.h"
#include "bullet.h"
#include <iostream>

Game::Game() {
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    // calcula a largura e altura da janela de modo que tenha 90% da largura do monitor e mantenha a proporção 1:2
    float width = desktop.width * 0.9f;
    float height = width / 2.0f;
    window.create(sf::VideoMode(width, height), "Base Defense Game", sf::Style::Titlebar | sf::Style::Close);
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
    player.setBodyTexture(texture);
    player.setPositionCenter(window);
    base.setPositionCenter(window);
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
                sf::Vector2f playerPos = player.getPosition();
                sf::Vector2f mousePos = getMouseClickPosition();
                bullets.push_back(new Bullet(playerPos, mousePos)); // Adiciona nova bala
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
    player.checkWallCollision(deltaTime, window.getSize());

    for (auto bulletIterator = bullets.begin(); bulletIterator != bullets.end();) {
        (*bulletIterator)->update(deltaTime);
        if ((*bulletIterator)->checkBulletDistanceLimit()) {
            delete *bulletIterator;
            bulletIterator = bullets.erase(bulletIterator);
        } else {
            bulletIterator++;
        }
    }
}

// função para renderizar a janela atual do jogo
void Game::render() {
    window.clear(sf::Color(221,221,221));

    base.draw(window);
    for (Bullet* bullet : bullets) {
        bullet->draw(window);
    }
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
sf::Vector2f Game::getMouseClickPosition() {
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    return sf::Vector2f(mousePosition);
}