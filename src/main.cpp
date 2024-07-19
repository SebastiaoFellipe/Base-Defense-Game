#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    std::cout << "Iniciando Base Defense Game!" << std::endl;
    std::cout << "Em execução..." << std::endl;

    sf::RenderWindow window(sf::VideoMode(1600, 800), "Base Defense Game");

    sf::Font font;
    if (!font.loadFromFile("assets/fonts/Minecraftia-Regular.ttf")) {
        std::cerr << "Erro ao carregar a fonte!" << std::endl;
        return 1;
    }

    sf::Text text;
    text.setFont(font);
    text.setString("Hello, World!");
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setPosition(100, 100);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape)
                    window.close();
            }
        }

        window.clear(sf::Color::Black);
        window.draw(text);
        window.display();
    }

    std::cout << "Jogo encerrado." << std::endl;
    return 0;
}