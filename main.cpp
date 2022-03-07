#include <SFML/Graphics.hpp>
#include "structure.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "University game");

    sf::Font text_font;
    text_font.loadFromFile("C:/Users/bonda/cppgame/University_game/fonts/arial.ttf");

    sf::Text head_text;
    head_text.setFont(text_font);
    head_text.setString("University game");
    head_text.setCharacterSize(50);
    head_text.setFillColor(sf::Color::Cyan);
    head_text.setStyle(sf::Text::Bold);
    head_text.setPosition(450, 40);

    sf::Text new_game_button_text;
    new_game_button_text.setFont(text_font);
    new_game_button_text.setString("Start a new game");
    new_game_button_text.setCharacterSize(25);
    new_game_button_text.setFillColor(sf::Color::Cyan);
    new_game_button_text.setStyle(sf::Text::Italic);
    new_game_button_text.setPosition(530, 200);

    sf::RectangleShape new_game_button_shape;
    new_game_button_shape.setSize(sf::Vector2f(300, 50));
    new_game_button_shape.setPosition(490, 195);
    new_game_button_shape.setOutlineThickness(3.f);
    new_game_button_shape.setFillColor(sf::Color::Transparent);
    new_game_button_shape.setOutlineColor(sf::Color::Cyan);

    university_game::item first_required("algebra book", "you need this for 'first_quest'", 10, 2);
    university_game::item first_award("gold medal", "be proud of yourself", 0, 0);
    university_game::quest first_quest("first_quest", "1st description", 1,
                                       first_required, first_award);
    university_game::quest second_quest("second_quest", "2nd description", 2,
                                        university_game::item("", "", 0, 0),
                                        university_game::item("", "", 0, 0));
    university_game::quest third_quest("third_quest", "3rd description", 1,
                                        university_game::item("", "", 0, 0),
                                        university_game::item("", "", 0, 0));
    third_quest.mark_as_completed();
    std::vector<university_game::quest> initial_quests = {first_quest, second_quest, third_quest};
    std::vector<university_game::item> initial_items{};
    university_game::player player_1("You", initial_quests, initial_items);
    university_game::teacher teacher_1("Mr. Antipoff", 2, 1, 1,
                             {"Hey! Wanna mark? Bring me my algebra book.",
                              "Did you actually find it?", "Alright, here we go."}, first_quest.get_name());
    university_game::teacher teacher_2("Mr. Khrabroff", 3, 12, 5,
                                       {"1",
                                        "2", "3"}, third_quest.get_name());

    university_game::game my_game(&window, text_font, player_1);
    my_game.setPosition(40.f, 40.f);
    bool game_started = false;
    bool inventory_and_quests_opened = false;
    bool teacher_speaking = false;
    int executing_id = 0;
    int id = 0;

    while (window.isOpen()) {
        if (game_started) {
            sf::Event event{};
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Escape) {
                        window.close();
                    }
                    if (event.key.code == sf::Keyboard::Right && !inventory_and_quests_opened) {
                        my_game.move(1);
                    }
                    if (event.key.code == sf::Keyboard::Up && !inventory_and_quests_opened) {
                        my_game.move(2);
                    }
                    if (event.key.code == sf::Keyboard::Left && !inventory_and_quests_opened) {
                        my_game.move(3);
                    }
                    if (event.key.code == sf::Keyboard::Down && !inventory_and_quests_opened) {
                        my_game.move(4);
                    }
                    if (event.key.code == sf::Keyboard::X && !inventory_and_quests_opened) {
                        id = my_game.check_presence_of_teacher();
                        if (id > 0 && (executing_id == 0 || executing_id == id || my_game.get_teachers()[executing_id - 2].get_quest_stage() > 2)) {
                            executing_id = id;
                            teacher_speaking = true;
                        }
                        my_game.take_item_if_possible();
                    }
                    if (event.key.code == sf::Keyboard::E && !inventory_and_quests_opened) {
                        inventory_and_quests_opened = true;
                    } else if (event.key.code == sf::Keyboard::E && inventory_and_quests_opened) {
                        inventory_and_quests_opened = false;
                    }
                }
            }
            window.clear();
            window.draw(my_game);

            if (inventory_and_quests_opened) {
                window.draw(my_game.get_player());
            }
            if (teacher_speaking) {
                const sf::Time freezeLength{ sf::seconds(3.f) };
                sf::Clock freezeClock;
                while (freezeClock.getElapsedTime() < freezeLength) {
                    window.draw(my_game.get_teachers()[id - 2]);
                    window.display();
                }
                teacher_speaking = false;
                my_game.get_teachers()[id - 2].satisfy_quest(my_game.get_player());
            }
            window.display();
        } else {
            sf::Event event{};
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Escape) {
                        window.close();
                    }
                }
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (event.mouseButton.x > 490 && event.mouseButton.x < 790
                        && event.mouseButton.y > 195 && event.mouseButton.y < 245) {

                        game_started = true;

                        university_game::game new_game(&window, text_font, player_1);
                        my_game = new_game;
                        my_game.setPosition(40.f, 40.f);

                        my_game.get_teachers()[0] = teacher_1;
                        my_game.get_teachers()[1] = teacher_2;
                        first_required.set_displayed(true);
                        my_game.get_displayed_items()[0] = first_required;
                    }
                }
            }
            window.clear();
            window.draw(head_text);
            window.draw(new_game_button_text);
            window.draw(new_game_button_shape);
            window.display();
        }
    }

    return 0;
}