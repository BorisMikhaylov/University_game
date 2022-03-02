#include <SFML/Graphics.hpp>
#include "structure.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "University game");
    university_game::game my_game;
    my_game.setPosition(40.f, 40.f);
    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                // NOLINTNEXTLINE
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                }
                if (event.key.code == sf::Keyboard::Right) {
                    my_game.move(1);
                }
                if (event.key.code == sf::Keyboard::Up) {
                    my_game.move(2);
                }
                if (event.key.code == sf::Keyboard::Left) {
                    my_game.move(3);
                }
                if (event.key.code == sf::Keyboard::Down) {
                    my_game.move(4);
                }
                /*if (event.key.code == sf::Keyboard::F2)
                {
                    game.Init();
                    move_counter = 100;
                }
                */
            }
        }

        window.clear();
        window.draw(my_game);
        window.display();
    }

    return 0;
}