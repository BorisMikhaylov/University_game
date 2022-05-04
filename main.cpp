#include <SFML/Graphics.hpp>
#include "structure.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "University game");

    sf::View standard_view(sf::FloatRect(0, 0,
                                         window.getSize().x, window.getSize().y));
    standard_view.setCenter(640, 360);

    sf::Font text_font;
    text_font.loadFromFile("C:/Users/Serge/CLionProjects/University_game/fonts/arial.ttf");

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

    sf::Text settings_button_text;
    settings_button_text.setFont(text_font);
    settings_button_text.setString("Settings");
    settings_button_text.setCharacterSize(25);
    settings_button_text.setFillColor(sf::Color::Cyan);
    settings_button_text.setStyle(sf::Text::Italic);
    settings_button_text.setPosition(580, 300);

    sf::RectangleShape settings_button_shape;
    settings_button_shape.setSize(sf::Vector2f(300, 50));
    settings_button_shape.setPosition(490, 295);
    settings_button_shape.setOutlineThickness(3.f);
    settings_button_shape.setFillColor(sf::Color::Transparent);
    settings_button_shape.setOutlineColor(sf::Color::Cyan);

    sf::Text copyright_text;
    copyright_text.setFont(text_font);
    copyright_text.setString("by Bondar, Mikhaylov, Shimanskiy, HSE AMI 2022.");
    copyright_text.setCharacterSize(15);
    copyright_text.setFillColor(sf::Color::Cyan);
    copyright_text.setPosition(475, 650);

    sf::Text settings_head_text;
    settings_head_text.setFont(text_font);
    settings_head_text.setString("Settings");
    settings_head_text.setCharacterSize(50);
    settings_head_text.setFillColor(sf::Color::Cyan);
    settings_head_text.setStyle(sf::Text::Bold);
    settings_head_text.setPosition(530, 40);

    sf::Text settings_main_text;
    settings_main_text.setFont(text_font);
    settings_main_text.setString("Keyboard bindings: \n\n"
                                 "~ Interact with objects/characters:        X\n"
                                 "~ Open/close inventory/list of quests:   E\n"
                                 "~ Start/end sudoku game:  S\n"
                                 "~ Leave game:                                       ESC\n");
    settings_main_text.setCharacterSize(25);
    settings_main_text.setFillColor(sf::Color::Cyan);
    settings_main_text.setPosition(50, 195);

    sf::Text settings_back_button_text;
    settings_back_button_text.setFont(text_font);
    settings_back_button_text.setString("Back");
    settings_back_button_text.setCharacterSize(25);
    settings_back_button_text.setFillColor(sf::Color::Cyan);
    settings_back_button_text.setStyle(sf::Text::Italic);
    settings_back_button_text.setPosition(610, 600);

    sf::RectangleShape settings_back_button_shape;
    settings_back_button_shape.setSize(sf::Vector2f(100, 50));
    settings_back_button_shape.setPosition(590, 595);
    settings_back_button_shape.setOutlineThickness(3.f);
    settings_back_button_shape.setFillColor(sf::Color::Transparent);
    settings_back_button_shape.setOutlineColor(sf::Color::Cyan);

    sf::RectangleShape victory_shape(sf::Vector2f(450, 50));
    victory_shape.setOutlineThickness(3.f);
    victory_shape.setFillColor(sf::Color::White);
    victory_shape.setOutlineColor(sf::Color::Cyan);

    sf::Text victory_text;
    victory_text.setFont(text_font);
    victory_text.setString("CONGRATULATIONS!");
    victory_text.setCharacterSize(40);
    victory_text.setFillColor(sf::Color::Red);
    victory_text.setStyle(sf::Text::Bold);

    university_game::item first_required("algebra book", "you need this for 'Trickster' \nquest", 10, 2);
    university_game::item first_award("well-rated assignment", "you've completed 'Trickster', \nhooray!", 0, 0);
    university_game::quest first_quest("Trickster", "Go to Mr. Antipoff and try to get a \ngood mark "
                                                    "in algebra without doing it.", 1,
                                       first_required, first_award);
    university_game::quest second_quest("Talkative friend", "Have a little chat with Mr. Khrabroff.", 2,
                                        university_game::item("none", "", 0, 0),
                                        university_game::item("none", "", 0, 0));
    /*university_game::quest third_quest("third_quest", "3rd description", 1,
                                        university_game::item("", "", 0, 0),
                                        university_game::item("", "", 0, 0));
    third_quest.mark_as_completed();*/
    std::vector<university_game::quest> initial_quests = {first_quest, second_quest};
    std::vector<university_game::item> initial_items{};
    university_game::player player_1("You", initial_quests, initial_items);
    university_game::teacher teacher_1("Mr. Antipoff", 2, 1, 1,
                                       {"Hey! Wanna mark? Bring me my algebra book.",
                                        "Did you actually find it?", "Alright, here we go."}, first_quest.get_name());
    university_game::teacher teacher_2("Mr. Khrabroff", 3, 12, 5,
                                       {"Hey!",
                                        "I've heard that you're a trickster now.",
                                        "Good job! See you later."}, second_quest.get_name());

    university_game::game my_game(&window, text_font, player_1);
    my_game.setPosition(40.f, 40.f);

    university_game::minigame_bugs mg_bugs;
    university_game::sudoku_game sudoku;

    bool game_started = false;
    bool settings_opened = false;
    bool inventory_and_quests_opened = false;
    bool teacher_speaking = false;
    bool bugs_game_started = false;
    bool sudoku_started = false;
    bool sudoku_victory = false;
    int executing_id = 0;
    int id = 0;
    static bool lock_click;
    std::srand(std::time(nullptr));

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
                    if (event.key.code == sf::Keyboard::M && !bugs_game_started && !sudoku_started) {                                 //MINIGAME
                        bugs_game_started = true;
                        mg_bugs.add_bug();
                        mg_bugs.add_bug();
                        mg_bugs.add_bug();
                        mg_bugs.add_bug();
                        mg_bugs.add_bug();
                        mg_bugs.add_bug();
                        mg_bugs.add_bug();
                        mg_bugs.add_bug();
                        mg_bugs.add_bug();
                    } else if (event.key.code == sf::Keyboard::M && bugs_game_started){
                        bugs_game_started = false;
                    }
                    if (event.key.code == sf::Keyboard::S && !bugs_game_started &&
                        !sudoku_started && !inventory_and_quests_opened) {
                        sudoku_started = true;
                        sudoku.new_sudoku(my_game.get_player().get_v_compare(), my_game.get_player().get_h_compare());
                    } else if (event.key.code == sf::Keyboard::S && sudoku_started) {
                        sudoku_started = false;
                    }
                    if (bugs_game_started) {
                        if (mg_bugs.count_bugs <= 0) {
                            bugs_game_started = false;
                            continue;
                        }
                        if (event.type == sf::Event::MouseButtonPressed) {
                            if (event.mouseButton.button == sf::Mouse::Left && !lock_click) {
                                int mouse_pos_x = sf::Mouse::getPosition(window).x;
                                int mouse_pos_y = sf::Mouse::getPosition(window).y;
                                for (int ids_bugs: mg_bugs.bugs_id) {
                                    university_game::bug cur_bug = mg_bugs.id_bug[ids_bugs];
                                    if (std::abs(mouse_pos_x - cur_bug.active_x) <= 5 &&
                                        std::abs(mouse_pos_y - cur_bug.active_y) <= 5) {
                                        mg_bugs.remove_bug(ids_bugs);
                                    }
                                }
                                lock_click = true;
                            }
                        }
                        if (event.type == sf::Event::MouseButtonReleased) {
                            if (event.mouseButton.button == sf::Mouse::Left) {
                                lock_click = false;
                            }
                        }
                        if (rand() % 100 == 50) {
                            mg_bugs.add_bug();
                        }
                        continue;
                    }
                    if (sudoku_started) {
                        if (event.key.code == sf::Keyboard::Num1) {
                            if (sudoku.set_value(1)) {
                                sudoku_started = false;
                                sudoku_victory = true;
                            }
                        }
                        if (event.key.code == sf::Keyboard::Num2) {
                            if (sudoku.set_value(2)) {
                                sudoku_started = false;
                                sudoku_victory = true;
                            }
                        }
                        if (event.key.code == sf::Keyboard::Num3) {
                            if (sudoku.set_value(3)) {
                                sudoku_started = false;
                                sudoku_victory = true;
                            }
                        }
                        if (event.key.code == sf::Keyboard::Num4) {
                            if (sudoku.set_value(4)) {
                                sudoku_started = false;
                                sudoku_victory = true;
                            }
                        }
                        if (event.key.code == sf::Keyboard::Num5) {
                            if (sudoku.set_value(5)) {
                                sudoku_started = false;
                                sudoku_victory = true;
                            }
                        }
                        if (event.key.code == sf::Keyboard::Num6) {
                            if (sudoku.set_value(6)) {
                                sudoku_started = false;
                                sudoku_victory = true;
                            }
                        }
                        if (event.key.code == sf::Keyboard::Num7) {
                            if (sudoku.set_value(7)) {
                                sudoku_started = false;
                                sudoku_victory = true;
                            }
                        }
                        if (event.key.code == sf::Keyboard::Num8) {
                            if (sudoku.set_value(8)) {
                                sudoku_started = false;
                                sudoku_victory = true;
                            }
                        }
                        if (event.key.code == sf::Keyboard::Num9) {
                            if (sudoku.set_value(9)) {
                                sudoku_started = false;
                                sudoku_victory = true;
                            }
                        }
                        if (event.key.code == sf::Keyboard::BackSpace) {
                            sudoku.set_value(-1);
                        }
                        continue;
                    }
                    if (event.key.code == sf::Keyboard::Right && !inventory_and_quests_opened) {
                        for (int i = 1; i < 51; i++) {
                            if (!my_game.move(1, i)) {
                                break;
                            }
                            window.clear();
                            window.draw(my_game);
                            window.display();
                        }
                    }
                    if (event.key.code == sf::Keyboard::Up && !inventory_and_quests_opened) {
                        for (int i = 1; i < 51; i++) {
                            if (!my_game.move(2, i)) {
                                break;
                            }
                            window.clear();
                            window.draw(my_game);
                            window.display();
                        }
                    }
                    if (event.key.code == sf::Keyboard::Left && !inventory_and_quests_opened) {
                        for (int i = 1; i < 51; i++) {
                            if (!my_game.move(3, i)) {
                                break;
                            }
                            window.clear();
                            window.draw(my_game);
                            window.display();
                        }
                    }
                    if (event.key.code == sf::Keyboard::Down && !inventory_and_quests_opened) {
                        for (int i = 1; i < 51; i++) {
                            if (!my_game.move(4, i)) {
                                break;
                            }
                            window.clear();
                            window.draw(my_game);
                            window.display();
                        }
                    }
                    if (event.key.code == sf::Keyboard::X && !inventory_and_quests_opened) {
                        id = my_game.check_presence_of_teacher();
                        if (id > 0 && (executing_id == 0
                                       || executing_id == id
                                       || my_game.get_teachers()[executing_id - 2].get_quest_stage() > 2)) {
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
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (event.mouseButton.x > 0
                        && event.mouseButton.x < 110
                        && event.mouseButton.y > 0
                        && event.mouseButton.y < 50) {
                        game_started = false;
                        window.setView(standard_view);
                    }
                    else if (sudoku_started) {
                        int x_pressed = event.mouseButton.x - 314;
                        int y_pressed = event.mouseButton.y - 34;
                        x_pressed /= 50;
                        y_pressed /= 50;
                        sudoku.set_selected_cell(x_pressed, y_pressed);
                    }
                }
            }
            if (game_started) {
                window.clear();
                if (bugs_game_started){
                    window.draw(mg_bugs);
                    window.display();
                    continue;
                }
                window.draw(my_game);
                if (sudoku_started) {
                    window.draw(sudoku);
                    window.display();
                    continue;
                }
                if (sudoku_victory) {
                    int x_draw_cord = my_game.get_player().get_v_compare() * university_game::cell_v_size - 100;
                    int y_draw_cord = my_game.get_player().get_h_compare() * university_game::cell_h_size - 10;
                    victory_text.setPosition(x_draw_cord, y_draw_cord);
                    victory_shape.setPosition(x_draw_cord, y_draw_cord);
                    window.draw(victory_shape);
                    window.draw(victory_text);
                    window.display();
                    const sf::Time freezeLength{sf::seconds(3.f)};
                    sf::Clock freezeClock;
                    while (freezeClock.getElapsedTime() < freezeLength) {
                    }
                    sudoku_victory = false;
                    continue; //somewhy it doesn't work
                }
                if (inventory_and_quests_opened) {
                    window.draw(my_game.get_player());
                }
                if (teacher_speaking) {
                    const sf::Time freezeLength{sf::seconds(3.f)};
                    sf::Clock freezeClock;
                    while (freezeClock.getElapsedTime() < freezeLength) {
                        window.draw(my_game.get_teachers()[id - 2]);
                        window.display();
                    }
                    teacher_speaking = false;
                    my_game.get_teachers()[id - 2].satisfy_quest(my_game.get_player());
                }
                window.display();
            }
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
                        && event.mouseButton.y > 195 && event.mouseButton.y < 245 && !settings_opened) {

                        game_started = true;

                        university_game::game new_game(&window, text_font, player_1);
                        my_game = new_game;
                        my_game.setPosition(40.f, 40.f);

                        my_game.get_teachers()[0] = teacher_1;
                        my_game.get_teachers()[1] = teacher_2;
                        first_required.set_displayed(true);
                        my_game.get_displayed_items()[0] = first_required;
                    }
                    if (event.mouseButton.x > 490 && event.mouseButton.x < 790
                        && event.mouseButton.y > 295 && event.mouseButton.y < 345 && !settings_opened) {
                        settings_opened = true;
                    }
                    if (event.mouseButton.x > 590 && event.mouseButton.x < 690
                        && event.mouseButton.y > 595 && event.mouseButton.y < 645 && settings_opened) {
                        settings_opened = false;
                    }
                }
            }
            window.clear();
            if (!settings_opened) {
                window.draw(head_text);
                window.draw(new_game_button_text);
                window.draw(new_game_button_shape);
                window.draw(settings_button_text);
                window.draw(settings_button_shape);
                window.draw(copyright_text);
            } else {
                window.draw(settings_head_text);
                window.draw(settings_main_text);
                window.draw(settings_back_button_text);
                window.draw(settings_back_button_shape);
            }
            window.display();
        }
    }

    return 0;
}
