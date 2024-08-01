#include "game.h"
#include <iostream>

Game::Game():Window(sf::VideoMode(1200, 600), "Base Defense Game") {
    initialize();
}

void Game::initialize() {
    if (!Font.loadFromFile("assets/fonts/Minecraftia-Regular.ttf")) {
        std::cerr << "Erro ao carregar a fonte!" << std::endl;
        std::exit(1);  // Encerrar o programa se a fonte não puder ser carregada
    }

    Text.setFont(Font);
    Text.setString("Hello, World!");
    Text.setCharacterSize(24);
    Text.setFillColor(sf::Color::White);
    Text.setPosition(100, 100);
}

// função para processar os eventos na janela do jogo
void Game::processEvents() {
    sf::Event event;
    while (Window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            Window.close();
        }
        if (event.type == sf::Event::KeyPressed) {
            getKeyboardEvent(event);
        }
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                getMouseClickPosition();
            }
        }
    }
}

// função para atualizar a janela do jogo
void Game::update() {
    // Atualizar o estado do jogo, se necessário
}

// função para renderizar a janela do jogo
void Game::render() {
    sf::Color customColor(221, 221, 221); 
    Window.clear(customColor);
    Window.draw(Text);
    Window.display();
}

// função para rodar o jogo
void Game::run() {
    std::cout << "Iniciando Base Defense Game!" << std::endl;
    while (Window.isOpen()) {
        processEvents();
        update();
        render();
    }
    std::cout << "Jogo encerrado." << std::endl;
}

// função para pegar posição do mouse
void Game::getMouseClickPosition() {
    sf::Vector2i mousePosition = sf::Mouse::getPosition(Window);
    std::cout << "Mouse clicado na posição (" << mousePosition.x << ", " << mousePosition.y << ")" << std::endl;
}

// função para verificar qual tecla foi pressionada
void Game::getKeyboardEvent(const sf::Event& event) {
    switch (event.key.code) {
        case sf::Keyboard::Escape:
            Window.close();
            break;
        case sf::Keyboard::W:
            std::cout << "Letra W" << std::endl;
            break;
        case sf::Keyboard::A:
            std::cout << "Letra A" << std::endl;
            break;
        case sf::Keyboard::S:
            std::cout << "Letra S" << std::endl;
            break;
        case sf::Keyboard::D:
            std::cout << "Letra D" << std::endl;
            break;
        case sf::Keyboard::P:
            std::cout << "Letra P" << std::endl;
            break;
        default:
            break;
    }
}