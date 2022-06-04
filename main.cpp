#include <SFML/Graphics.hpp>
#include "structure.h"
#include <cmath>
#include <random>

int main() {
    std::string prefix = university_game::prefix;
    sf::RenderWindow window(sf::VideoMode(1280, 720), "University game");
    window.setKeyRepeatEnabled(true);
    window.setFramerateLimit(1000);

    sf::View standard_view(sf::FloatRect(0, 0,
                                         window.getSize().x, window.getSize().y));
    standard_view.setCenter(640, 360);

    sf::Font text_font;
    text_font.loadFromFile(prefix + "/fonts/arial.ttf");

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

    sf::Text load_game_button_text;
    load_game_button_text.setFont(text_font);
    load_game_button_text.setString("Load game");
    load_game_button_text.setCharacterSize(25);
    load_game_button_text.setFillColor(sf::Color::Cyan);
    load_game_button_text.setStyle(sf::Text::Italic);
    load_game_button_text.setPosition(570, 300);

    sf::RectangleShape load_game_button_shape;
    load_game_button_shape.setSize(sf::Vector2f(300, 50));
    load_game_button_shape.setPosition(490, 295);
    load_game_button_shape.setOutlineThickness(3.f);
    load_game_button_shape.setFillColor(sf::Color::Transparent);
    load_game_button_shape.setOutlineColor(sf::Color::Cyan);

    sf::Text settings_button_text;
    settings_button_text.setFont(text_font);
    settings_button_text.setString("Settings");
    settings_button_text.setCharacterSize(25);
    settings_button_text.setFillColor(sf::Color::Cyan);
    settings_button_text.setStyle(sf::Text::Italic);
    settings_button_text.setPosition(580, 400);

    sf::RectangleShape settings_button_shape;
    settings_button_shape.setSize(sf::Vector2f(300, 50));
    settings_button_shape.setPosition(490, 395);
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
                                 "~ Leave game:                                       ESC\n"
                                 "~ Move player:                                       Arrow keys or WASD\n"
                                 "~ Start/end tetris minigame:                  T\n"
                                 "~ Start/end sudoky minigame:              G\n"
                                 "~ Start/end bugs minigame:                  B\n");
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

    university_game::quest first_quest;
    university_game::quest second_quest;
    university_game::quest third_quest;
    first_quest.create_from_json("quest1.json");
    second_quest.create_from_json("quest2.json");
    third_quest.create_from_json("quest3.json");
    university_game::item first_required = first_quest.get_required_item();
    university_game::item third_required = third_quest.get_required_item();

    std::vector<university_game::quest> initial_quests = {first_quest, second_quest, third_quest};
    std::vector<university_game::item> initial_items{};
    university_game::player player_1("You", initial_quests, initial_items);
    university_game::teacher teacher_1("Mr. Antipoff", 2, 1, 1,
                                       {"Hey! Wanna mark? Bring me my algebra book.",
                                        "Did you actually find it?", "Alright, here we go."}, first_quest.get_name());
    university_game::teacher teacher_2("Mr. Khrabroff", 3, 12, 5,
                                       {"Hey!",
                                        "I've heard that you're a trickster now.",
                                        "Good job! See you later."}, second_quest.get_name());
    university_game::teacher teacher_3("Pashok", 4, 22, 2,
                                       {"Yo! Find a wall, where I've hidden money.",
                                        "You've found it, right?",
                                        "Thank you, man. Appreciate that."}, third_quest.get_name());

    university_game::game my_game(&window, text_font, player_1);
    university_game::sudoku_game sudoku;
    university_game::minigame_bugs mg_bugs(&window);
    my_game.setPosition(40.f, 40.f);
    my_game.load_textures();

    // mini-game Tetris
    sf::Texture tile_tex;
    tile_tex.loadFromFile(university_game::prefix + "/images/tetris_tile.png");

    sf::Sprite tile(tile_tex);
    tile.setScale(2.83, 2.83);

    float tile_size = tile_tex.getSize().x * tile.getScale().x;

    //Setup score counter
    sf::Text score;
    score.setFont(text_font);
    score.setCharacterSize(15);
    score.setFillColor(sf::Color::Black);
    score.setPosition(10, 25);
    sf::Vector2<float> score_scale(1.5f, 1.5f);
    score.setScale(score_scale);
    score.setString("Lines: 0");

    university_game::byte colliders[16][12];
    university_game::byte grid[16][12];
    university_game::part piece;
    piece = piece.create_part(static_cast<university_game::part_type>((rand() % 7)));
    unsigned int timer = 0, gamespeed = 10, scoreCounter = 0;

    sf::Vector2f view_position(250, 370);
    sf::View view(sf::FloatRect(0, 0,
                                window.getSize().x, window.getSize().y));
    view.setCenter(view_position);

    bool game_started = false;
    bool settings_opened = false;
    bool inventory_and_quests_opened = false;
    bool teacher_speaking = false;
    bool something_extra_opened = false; //true if any minigame started or inventory opened
    bool mini_game_tetris_started = false;
    bool minigame_sudoku_started = false;
    bool minigame_bugs_started = false;
    bool sudoku_victory = false;
    int executing_id = 0;
    int id = 0;

    while (window.isOpen()) {
        if (game_started) {
            sf::Event event{};
            if (minigame_bugs_started) { //even if nothing is happening, the bugs still are moving and appearing
                for (int i: mg_bugs.bugs_id) {
                    mg_bugs.move_bug(i);
                }
                if (rand() % 2000 == 0 && mg_bugs.count_bugs <= 20) {
                    mg_bugs.add_bug();
                }
            }
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Escape) {
                        window.close();
                    }
                    if (!something_extra_opened) { //game moves, interaction with objects, starting any minigame
                        //or opening inventory
                        if (event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::D) {
                            for (int i = 1; i < 501; i++) {
                                if (!my_game.move(1, i)) {
                                    break;
                                }
                                window.clear();
                                window.draw(my_game);
                                window.display();
                            }
                        }
                        if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W) {
                            for (int i = 1; i < 501; i++) {
                                if (!my_game.move(2, i)) {
                                    break;
                                }
                                window.clear();
                                window.draw(my_game);
                                window.display();
                            }
                        }
                        if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::A) {
                            for (int i = 1; i < 501; i++) {
                                if (!my_game.move(3, i)) {
                                    break;
                                }
                                window.clear();
                                window.draw(my_game);
                                window.display();
                            }
                        }
                        if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S) {
                            for (int i = 1; i < 501; i++) {
                                if (!my_game.move(4, i)) {
                                    break;
                                }
                                window.clear();
                                window.draw(my_game);
                                window.display();
                            }
                        }
                        if (event.key.code == sf::Keyboard::X) {
                            id = my_game.check_presence_of_teacher();
                            if (id > 0 && (executing_id == 0
                                           || executing_id == id
                                           || my_game.get_teachers()[executing_id - 2].get_quest_stage() > 2)) {
                                executing_id = id;
                                teacher_speaking = true;
                            }
                            my_game.take_item_if_possible();
                        }
                        if (event.key.code == sf::Keyboard::E) {
                            inventory_and_quests_opened = true;
                            something_extra_opened = true;
                        }
                        if (event.key.code == sf::Keyboard::T) {
                            mini_game_tetris_started = true;
                            something_extra_opened = true;
                            window.setFramerateLimit(45);
                            timer = 0, gamespeed = 10, scoreCounter = 0;
                            for (int k = 0; k < 16; k++) {
                                for (int j = 0; j < 12; j++) {
                                    colliders[k][j] = 0;
                                    grid[k][j] = 0;
                                }
                            }
                            score.setString("Lines: 0");
                        }
                        if (event.key.code == sf::Keyboard::G) {
                            minigame_sudoku_started = true;
                            something_extra_opened = true;
                            sudoku.new_sudoku(my_game.get_player().get_v_compare(),
                                              my_game.get_player().get_h_compare());
                        }
                        if (event.key.code == sf::Keyboard::B) {
                            minigame_bugs_started = true;
                            something_extra_opened = true;
                            mg_bugs.add_bug();
                        }
                    } else {//closing minigames or inventory
                        if (event.key.code == sf::Keyboard::T && mini_game_tetris_started) {
                            mini_game_tetris_started = false;
                            something_extra_opened = false;
                            window.setFramerateLimit(1000);
                            timer = 0, gamespeed = 10, scoreCounter = 0;
                            for (int k = 0; k < 16; k++) {
                                for (int j = 0; j < 12; j++) {
                                    colliders[k][j] = 0;
                                    grid[k][j] = 0;
                                }
                            }
                            score.setString("Lines: 0");
                        }

                        if (event.key.code == sf::Keyboard::G && minigame_sudoku_started) {
                            minigame_sudoku_started = false;
                            something_extra_opened = false;
                        }

                        if (event.key.code == sf::Keyboard::E && inventory_and_quests_opened) {
                            inventory_and_quests_opened = false;
                            something_extra_opened = false;
                        }

                        if (event.key.code == sf::Keyboard::B && minigame_bugs_started) {
                            minigame_bugs_started = false;
                            something_extra_opened = false;
                        }
                    }
                    //directly miningames if started
                    if (mini_game_tetris_started) {
                        if (event.key.code == sf::Keyboard::Up) {
                            piece.rotate(piece, colliders);
                        } else if (event.key.code == sf::Keyboard::Left &&
                                   piece.a.x != 0 && piece.b.x != 0 && piece.c.x != 0 && piece.d.x != 0 &&
                                   (colliders[piece.a.y][piece.a.x - 1]) != 2 &&
                                   (colliders[piece.b.y][piece.b.x - 1]) != 2 &&
                                   (colliders[piece.c.y][piece.c.x - 1]) != 2 &&
                                   (colliders[piece.d.y][piece.d.x - 1]) != 2) {
                            piece.a.x--;
                            piece.b.x--;
                            piece.c.x--;
                            piece.d.x--;
                        } else if (event.key.code == sf::Keyboard::Right &&
                                   piece.a.x != 11 && piece.b.x != 11 && piece.c.x != 11 && piece.d.x != 11 &&
                                   (colliders[piece.a.y][piece.a.x + 1]) != 2 &&
                                   (colliders[piece.b.y][piece.b.x + 1]) != 2 &&
                                   (colliders[piece.c.y][piece.c.x + 1]) != 2 &&
                                   (colliders[piece.d.y][piece.d.x + 1]) != 2) {
                            piece.a.x++;
                            piece.b.x++;
                            piece.c.x++;
                            piece.d.x++;
                        }
                    }
                    if (minigame_sudoku_started) {
                        if (event.key.code == sf::Keyboard::Num1) {
                            if (sudoku.set_value(1)) {
                                minigame_sudoku_started = false;
                                something_extra_opened = false;
                                sudoku_victory = true;
                            }
                        }
                        if (event.key.code == sf::Keyboard::Num2) {
                            if (sudoku.set_value(2)) {
                                minigame_sudoku_started = false;
                                something_extra_opened = false;
                                sudoku_victory = true;
                            }
                        }
                        if (event.key.code == sf::Keyboard::Num3) {
                            if (sudoku.set_value(3)) {
                                minigame_sudoku_started = false;
                                something_extra_opened = false;
                                sudoku_victory = true;
                            }
                        }
                        if (event.key.code == sf::Keyboard::Num4) {
                            if (sudoku.set_value(4)) {
                                minigame_sudoku_started = false;
                                something_extra_opened = false;
                                sudoku_victory = true;
                            }
                        }
                        if (event.key.code == sf::Keyboard::Num5) {
                            if (sudoku.set_value(5)) {
                                minigame_sudoku_started = false;
                                something_extra_opened = false;
                                sudoku_victory = true;
                            }
                        }
                        if (event.key.code == sf::Keyboard::Num6) {
                            if (sudoku.set_value(6)) {
                                minigame_sudoku_started = false;
                                something_extra_opened = false;
                                sudoku_victory = true;
                            }
                        }
                        if (event.key.code == sf::Keyboard::Num7) {
                            if (sudoku.set_value(7)) {
                                minigame_sudoku_started = false;
                                something_extra_opened = false;
                                sudoku_victory = true;
                            }
                        }
                        if (event.key.code == sf::Keyboard::Num8) {
                            if (sudoku.set_value(8)) {
                                minigame_sudoku_started = false;
                                something_extra_opened = false;
                                sudoku_victory = true;
                            }
                        }
                        if (event.key.code == sf::Keyboard::Num9) {
                            if (sudoku.set_value(9)) {
                                minigame_sudoku_started = false;
                                something_extra_opened = false;
                                sudoku_victory = true;
                            }
                        }
                        if (event.key.code == sf::Keyboard::BackSpace) {
                            sudoku.set_value(-1);
                        }
                    }
                }
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (event.mouseButton.x > 0
                        && event.mouseButton.x < 110
                        && event.mouseButton.y > 0
                        && event.mouseButton.y < 50
                        && !something_extra_opened) {
                        game_started = false;
                        window.setView(standard_view);
                    }
                    if (minigame_sudoku_started) {
                        int x_pressed = event.mouseButton.x - 315;
                        int y_pressed = event.mouseButton.y - 35;
                        x_pressed /= 50;
                        y_pressed /= 50;
                        sudoku.set_selected_cell(x_pressed, y_pressed);
                    }
                    if (minigame_bugs_started) {
                        int mouse_pos_x = event.mouseButton.x;
                        int mouse_pos_y = event.mouseButton.y;
                        std::vector<int> ids_to_remove;
                        for (int ids_bugs: mg_bugs.bugs_id) {
                            university_game::bug cur_bug = mg_bugs.id_bug[ids_bugs];
                            if (std::abs(mouse_pos_x - cur_bug.active_x) <= 100 &&
                                std::abs(mouse_pos_y - cur_bug.active_y) <= 100) {
                                ids_to_remove.push_back(ids_bugs);
                            }
                        }
                        for (int i: ids_to_remove) {
                            mg_bugs.remove_bug(i);
                        }
                        if (mg_bugs.count_bugs <= 0) {
                            minigame_bugs_started = false;
                            something_extra_opened = false;
                            continue;
                        }
                    }
                }
            }

            if (game_started) { //drawing process starts here
                window.clear();
                if (minigame_bugs_started) {
                    window.draw(mg_bugs);
                    window.display();
                    continue;
                }
                window.draw(my_game);
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
                if (mini_game_tetris_started) {
                    window.setView(view);

                    window.clear(sf::Color(224, 145, 255));

                    sf::RectangleShape rectangle;
                    rectangle.setSize(sf::Vector2f(542, 706));
                    rectangle.setOutlineColor(sf::Color::Black);
                    rectangle.setFillColor(sf::Color::Transparent);
                    rectangle.setOutlineThickness(5);
                    rectangle.setPosition(0, 18);
                    window.draw(rectangle);

                    sf::Sprite piece_tile = tile;

                    piece_tile.setPosition(tile_size * piece.a.x, tile_size * piece.a.y);
                    window.draw(piece_tile);

                    piece_tile.setPosition(tile_size * piece.b.x, tile_size * piece.b.y);
                    window.draw(piece_tile);

                    piece_tile.setPosition(tile_size * piece.c.x, tile_size * piece.c.y);
                    window.draw(piece_tile);

                    piece_tile.setPosition(tile_size * piece.d.x, tile_size * piece.d.y);
                    window.draw(piece_tile);

                    for (size_t i = 0; i < 16; i++) {
                        for (size_t j = 0; j < 12; j++) {
                            if (colliders[i][j] == 2) {
                                grid[i][j] = 2;
                            } else {
                                grid[i][j] = 0;
                            }
                        }
                    }

                    if (timer > gamespeed) {
                        if (grid[piece.a.y + 1][piece.a.x] == 2 ||
                            grid[piece.b.y + 1][piece.b.x] == 2 ||
                            grid[piece.c.y + 1][piece.c.x] == 2 ||
                            grid[piece.d.y + 1][piece.d.x] == 2 ||
                            piece.a.y == 15 || piece.b.y == 15 || piece.c.y == 15 || piece.d.y == 15) {
                            grid[piece.a.y][piece.a.x] = 2;
                            grid[piece.b.y][piece.b.x] = 2;
                            grid[piece.c.y][piece.c.x] = 2;
                            grid[piece.d.y][piece.d.x] = 2;

                            colliders[piece.a.y][piece.a.x] = 2;
                            colliders[piece.b.y][piece.b.x] = 2;
                            colliders[piece.c.y][piece.c.x] = 2;
                            colliders[piece.d.y][piece.d.x] = 2;

                            piece = piece.create_part(static_cast<university_game::part_type>((rand() % 7)));
                        } else {
                            grid[piece.a.y + 1][piece.a.x] = 1;
                            grid[piece.b.y + 1][piece.b.x] = 1;
                            grid[piece.c.y + 1][piece.c.x] = 1;
                            grid[piece.d.y + 1][piece.d.x] = 1;

                            piece.a.y++;
                            piece.b.y++;
                            piece.c.y++;
                            piece.d.y++;
                        }

                        university_game::byte tetris_row = 0;
                        for (size_t i = 0; i < 16; i++) {
                            university_game::byte blocks_in_a_row = 0;
                            for (size_t j = 0; j < 12; j++) {
                                if (colliders[i][j] == 2) {
                                    blocks_in_a_row++;
                                }
                            }
                            if (blocks_in_a_row == 12) {
                                tetris_row++;
                                for (size_t k = i; k > 0; k--) {
                                    for (size_t l = 0; l < 12; l++) {
                                        colliders[k][l] = colliders[k - 1][l];
                                    }
                                }
                                scoreCounter++;
                                char temp[256];
                                sprintf_s(temp, "Lines: %i", scoreCounter);
                                score.setString(temp);
                            }
                        }

                        for (size_t i = 0; i < 12; i++) {
                            if (colliders[0][i] == 2) {
                                mini_game_tetris_started = false;
                                timer = 0, gamespeed = 10, scoreCounter = 0;
                                for (int k = 0; k < 16; k++) {
                                    for (int j = 0; j < 12; j++) {
                                        colliders[k][j] = 0;
                                        grid[k][j] = 0;
                                    }
                                }
                                window.setFramerateLimit(1000);
                                break;
                            }
                        }
                        timer = 0;
                    } else {
                        timer++;
                    }

                    for (size_t i = 0; i < 16; i++) {
                        for (size_t j = 0; j < 12; j++) {
                            if (grid[i][j] == 1) {
                                sf::Sprite t = tile;
                                t.setPosition(tile_size * j, tile_size * i);
                                window.draw(t);
                            }
                            if (colliders[i][j] == 2) {
                                sf::Sprite t = tile;
                                t.setPosition(tile_size * j, tile_size * i);
                                window.draw(t);
                            }
                        }
                    }
                    window.draw(score);
                }
                if (minigame_sudoku_started) {
                    window.draw(sudoku);
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
                        new_game.load_textures();
                        my_game = new_game;
                        my_game.setPosition(40.f, 40.f);

                        my_game.get_teachers()[0] = teacher_1;
                        my_game.get_teachers()[1] = teacher_2;
                        my_game.get_teachers()[2] = teacher_3;
                        first_required.set_displayed(true);
                        my_game.get_displayed_items()[0] = first_required;
                        third_required.set_displayed(true);
                        my_game.get_displayed_items()[1] = third_required;
                    }
                    if (event.mouseButton.x > 490 && event.mouseButton.x < 790
                        && event.mouseButton.y > 395 && event.mouseButton.y < 445 && !settings_opened) {
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
                window.draw(load_game_button_text);
                window.draw(load_game_button_shape);
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
