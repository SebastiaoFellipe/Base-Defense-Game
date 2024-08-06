#include "game.h"
#include "player.h"
#include "bullet.h"
#include <iostream>

Game::Game() {
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    // calcula a largura e altura da janela de modo que tenha 90% da largura do monitor e mantenha a proporção 1:2
    float width = desktop.width * 0.9f;
    float height = width / 2.0f;
    window.create(sf::VideoMode(width, height), "Base Defense Game");
    initialize();
}

// função para carregar os elementos, fontes, imagens e audios do jogo
void Game::initialize() {
    if (!font.loadFromFile("assets/fonts/Minecraftia-Regular.ttf")) {
        std::cerr << "Erro ao carregar a fonte." << std::endl;
        std::exit(1);
    }
    text.setFont(font);
    text.setFillColor(sf::Color::Black);
    text.setString("PAUSE");
    text.setCharacterSize(40);
    text.setStyle(sf::Text::Bold);
    text.setOrigin(text.getGlobalBounds().width/2,0.0f);
    text.setPosition((window.getSize().x/2.0f), 100.0f);

    if (!texture.loadFromFile("assets/img/player.png")) {
        std::cerr << "Erro ao carregar a textura do player." << std::endl;
        std::exit(1);
    }
    player.setBodyTexture(texture);
    player.setPositionCenter(window);

    if (!buffer.loadFromFile("assets/sounds/gun_pistol_silenced.wav")) {
        std::cerr << "Erro ao carregar o som do disparo. Efeito desabilitado." << std::endl;
        playerShootingSoundLoaded = false;
    } else {
        playerShootingSound.setBuffer(buffer);
    }
    
    base.setPositionCenter(window);
    
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
                player.shoot(playerShootingSound, playerShootingSoundLoaded);
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
        if (!onPause) {
            (*bulletIterator)->update(deltaTime);
        }
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
        if (!onPause){
            update(deltaTimeSeconds);
            render();
        }
        processEvents();
    }
    std::cout << "Jogo encerrado." << std::endl;
}

// função para pegar posição do mouse
sf::Vector2f Game::getMouseClickPosition() {
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    return sf::Vector2f(mousePosition);
}

void Game::closeGame(){
    for (Bullet* bullet : bullets) {
        delete bullet;
    }
    bullets.clear();
    window.close();
}

void Game::pause(){
    if (onPause){
        window.clear(sf::Color(221,221,221));
        onPause = false;
    } else {
        window.draw(text);
        window.display();
        onPause = true; 
    }
    std::cout << "pause: " << onPause << std::endl;
}