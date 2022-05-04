#include "structure.h"

namespace university_game {

sf::Font text_font_;
sf::Texture walkable_field_texture;
sf::Texture unwalkable_field_texture;
sf::Texture active_player_texture_front;
sf::Texture active_player_texture_right;
sf::Texture active_player_texture_left;
sf::Texture active_player_texture_back;
sf::Texture active_player_texture_front_moving;
sf::Texture active_player_texture_right_moving;
sf::Texture active_player_texture_left_moving;
sf::Texture active_player_texture_back_moving;
sf::Texture teacher1_texture;
sf::Texture teacher2_texture;
sf::Texture teacher3_texture;
sf::Texture item1_texture;

void game::load_textures() {
    text_font.loadFromFile(prefix + "/fonts/arial.ttf");
    text_font_.loadFromFile(prefix + "/fonts/arial.ttf");
    walkable_field_texture.loadFromFile(prefix + "/images/walkable_field.png");
    unwalkable_field_texture.loadFromFile(prefix + "/images/unwalkable_field.png");
    active_player_texture_front.loadFromFile(prefix + "/images/player_default.png");
    active_player_texture_right.loadFromFile(prefix + "/images/player_default_right.png");
    active_player_texture_left.loadFromFile(prefix + "/images/player_default_left.png");
    active_player_texture_back.loadFromFile(prefix + "/images/player_default_back.png");
    active_player_texture_front_moving.loadFromFile(prefix + "/images/player_default_moving.png");
    active_player_texture_right_moving.loadFromFile(prefix + "/images/player_default_right_moving.png");
    active_player_texture_left_moving.loadFromFile(prefix + "/images/player_default_left_moving.png");
    active_player_texture_back_moving.loadFromFile(prefix + "/images/player_default_back_moving.png");
    teacher1_texture.loadFromFile(prefix + "/images/teacher_default.png");
    teacher2_texture.loadFromFile(prefix + "/images/teacher_khrabroff.png");
    teacher3_texture.loadFromFile(prefix + "/images/teacher_pashok.png");
    item1_texture.loadFromFile(prefix + "/images/item_default.png");

}
void player::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();

    sf::Color outline_color = sf::Color(73, 103, 113);

    sf::RectangleShape frame_shape(sf::Vector2f(720, 480));
    frame_shape.setFillColor(sf::Color::White);
    frame_shape.setOutlineThickness(10.f);
    frame_shape.setOutlineColor(outline_color);
    frame_shape.setPosition(active_v * (cell_v_size) - 250, active_h * (cell_h_size) - 130);

    sf::RectangleShape split_shape(sf::Vector2f(10, 480));
    split_shape.setFillColor(outline_color);
    split_shape.setPosition(active_v * (cell_v_size) + 100, active_h * (cell_h_size) - 130);

    sf::Text quest_text;
    quest_text.setFont(text_font_);
    quest_text.setString("Available quests:");
    quest_text.setCharacterSize(30);
    quest_text.setFillColor(sf::Color::Black);
    quest_text.setStyle(sf::Text::Bold);
    quest_text.setPosition(active_v * (cell_v_size) - 240, active_h * (cell_h_size) - 120);

    sf::Text inventory_text;
    inventory_text.setFont(text_font_);
    inventory_text.setString("Your inventory:");
    inventory_text.setCharacterSize(30);
    inventory_text.setFillColor(sf::Color::Black);
    inventory_text.setStyle(sf::Text::Bold);
    inventory_text.setPosition(active_v * (cell_v_size) + 150, active_h * (cell_h_size) - 120);

    sf::Text level_text;
    level_text.setFont(text_font_);
    level_text.setString("Your current level: " + std::to_string(get_level()));
    level_text.setCharacterSize(30);
    level_text.setFillColor(sf::Color::Black);
    level_text.setStyle(sf::Text::Bold);
    level_text.setPosition(active_v * (cell_v_size) - 240, active_h * (cell_h_size) + 300);

    target.draw(frame_shape, states);
    target.draw(quest_text, states);
    target.draw(inventory_text, states);
    target.draw(level_text, states);

    quest_text.setString(display_available_quests());
    quest_text.setCharacterSize(15);
    quest_text.setPosition(active_v * (cell_v_size) - 240, active_h * (cell_h_size) - 70);

    inventory_text.setString(show_inventory());
    inventory_text.setCharacterSize(15);
    inventory_text.setPosition(active_v * (cell_v_size) + 150, active_h * (cell_h_size) - 70);

    target.draw(quest_text, states);
    target.draw(inventory_text, states);
    target.draw(split_shape, states);
}

void teacher::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();

    sf::Color outline_color = sf::Color(73, 103, 113);

    sf::RectangleShape frame_shape(sf::Vector2f(720, 60));
    frame_shape.setFillColor(sf::Color::White);
    frame_shape.setOutlineThickness(10.f);
    frame_shape.setOutlineColor(outline_color);
    frame_shape.setPosition(active_v * (cell_v_size) - 250, active_h * (cell_h_size) - 50);

    sf::Text quest_text;
    quest_text.setFont(text_font_);
    if (quest_stage > 2) {
        quest_text.setString("Sorry, nothing else for you today");
    } else {
        quest_text.setString(phrases[quest_stage]);
    }

    quest_text.setCharacterSize(30);
    quest_text.setFillColor(sf::Color::Black);
    quest_text.setStyle(sf::Text::Italic);
    quest_text.setPosition(active_v * (cell_v_size) - 240, active_h * (cell_h_size) - 40);

    target.draw(frame_shape, states);
    target.draw(quest_text, states);
}

void game::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    double active_v = active_player.get_v();
    double active_h = active_player.get_h();

    states.transform *= getTransform();

    sf::Color bg_color = sf::Color(254, 226, 183);
    sf::Color outline_color = sf::Color(58, 0, 0);

    sf::RectangleShape frame_shape(sf::Vector2f(2520, 750));
    frame_shape.setFillColor(sf::Color::White);
    frame_shape.setOutlineThickness(20.f);
    frame_shape.setOutlineColor(outline_color);
    target.draw(frame_shape, states);

    sf::RectangleShape shape;
    shape.setSize(sf::Vector2f(cell_v_size, cell_h_size));
    //shape.setOutlineThickness(1.f);
    //shape.setOutlineColor(color);

    for (unsigned int i = 0; i < h_table; i++) {
        for (unsigned int j = 0; j < v_table; j++) {
            if (map[i][j] == -2) {
                shape.setTexture(&unwalkable_field_texture);
            } else {
                shape.setTexture(&walkable_field_texture);
            }
            sf::Vector2f position(j * (cell_v_size), i * (cell_h_size));
            shape.setPosition(position);
            target.draw(shape, states);
        }
    }

    sf::RectangleShape active_player_shape(sf::Vector2f(cell_v_size, cell_h_size));
    if (active_player.get_graphic_phase() == 0) {
        if (active_player.get_direction() == 1) {
            active_player_shape.setTexture(&active_player_texture_right);
        } else if (active_player.get_direction() == 2) {
            active_player_shape.setTexture(&active_player_texture_back);
        } else if (active_player.get_direction() == 3) {
            active_player_shape.setTexture(&active_player_texture_left);
        } else if (active_player.get_direction() == 4) {
            active_player_shape.setTexture(&active_player_texture_front);
        }
    } else {
        if (active_player.get_direction() == 1) {
            active_player_shape.setTexture(&active_player_texture_right_moving);
        } else if (active_player.get_direction() == 2) {
            active_player_shape.setTexture(&active_player_texture_back_moving);
        } else if (active_player.get_direction() == 3) {
            active_player_shape.setTexture(&active_player_texture_left_moving);
        } else if (active_player.get_direction() == 4) {
            active_player_shape.setTexture(&active_player_texture_front_moving);
        }
    }

    sf::Vector2f active_player_position(active_v * (cell_v_size),
                                        active_h * (cell_h_size));
    active_player_shape.setPosition(active_player_position);

    sf::RectangleShape teacher1_shape(sf::Vector2f(cell_v_size, cell_h_size));
    teacher1_shape.setTexture(&teacher1_texture);
    sf::Vector2f teacher1_position(teachers[0].get_v() * (cell_v_size),
                                   teachers[0].get_h() * (cell_h_size));
    teacher1_shape.setPosition(teacher1_position);

    sf::RectangleShape teacher2_shape(sf::Vector2f(cell_v_size, cell_h_size));
    teacher2_shape.setTexture(&teacher2_texture);
    sf::Vector2f teacher2_position(teachers[1].get_v() * (cell_v_size),
                                   teachers[1].get_h() * (cell_h_size));
    teacher2_shape.setPosition(teacher2_position);

    sf::RectangleShape teacher3_shape(sf::Vector2f(cell_v_size, cell_h_size));
    teacher3_shape.setTexture(&teacher3_texture);
    sf::Vector2f teacher3_position(teachers[2].get_v() * (cell_v_size),
                                   teachers[2].get_h() * (cell_h_size));
    teacher3_shape.setPosition(teacher3_position);

    sf::RectangleShape item1_shape(sf::Vector2f(cell_v_size, cell_h_size));
    item1_shape.setTexture(&item1_texture);
    sf::Vector2f item1_position(displayed_items[0].get_v() * (cell_v_size),
                                displayed_items[0].get_h() * (cell_h_size));
    item1_shape.setPosition(item1_position);

    sf::RectangleShape item2_shape(sf::Vector2f(cell_v_size, cell_h_size));
    item2_shape.setTexture(&unwalkable_field_texture);
    sf::Vector2f item2_position(displayed_items[1].get_v() * (cell_v_size),
                                displayed_items[1].get_h() * (cell_h_size));
    item2_shape.setPosition(item2_position);

    sf::RectangleShape menu_button(sf::Vector2f(100, 40));
    menu_button.setFillColor(sf::Color::White);
    sf::Vector2f menu_button_position(active_v * (cell_v_size) - 570,
                                      active_h * (cell_h_size) - 290);
    menu_button.setPosition(menu_button_position);
    menu_button.setOutlineThickness(2.f);
    menu_button.setOutlineColor(sf::Color(73, 103, 113));

    sf::Text menu_text;
    menu_text.setFont(text_font);
    menu_text.setString(" Menu");
    menu_text.setCharacterSize(30);
    menu_text.setFillColor(sf::Color::Black);
    menu_text.setStyle(sf::Text::Italic);
    menu_text.setPosition(menu_button_position);

    sf::Text player_text;
    player_text.setFont(text_font);
    player_text.setString(active_player.get_name());
    player_text.setCharacterSize(20);
    player_text.setFillColor(sf::Color::Blue);
    player_text.setStyle(sf::Text::Italic);
    player_text.setPosition(active_player_position);

    sf::Text teacher1_text;
    teacher1_text.setFont(text_font);
    teacher1_text.setString(teachers[0].get_name());
    teacher1_text.setCharacterSize(20);
    teacher1_text.setFillColor(sf::Color::Red);
    teacher1_text.setStyle(sf::Text::Italic);
    teacher1_text.setPosition(teacher1_position);

    sf::Text teacher2_text;
    teacher2_text.setFont(text_font);
    teacher2_text.setString(teachers[1].get_name());
    teacher2_text.setCharacterSize(20);
    teacher2_text.setFillColor(sf::Color::Red);
    teacher2_text.setStyle(sf::Text::Italic);
    teacher2_text.setPosition(teacher2_position);

    sf::Text teacher3_text;
    teacher3_text.setFont(text_font);
    teacher3_text.setString(teachers[2].get_name());
    teacher3_text.setCharacterSize(20);
    teacher3_text.setFillColor(sf::Color::Red);
    teacher3_text.setStyle(sf::Text::Italic);
    teacher3_text.setPosition(teacher3_position);

    sf::Vector2f active_view_position(active_v * (cell_v_size) + 100,
                                      active_h * (cell_h_size) + 100);
    sf::View player_view(sf::FloatRect(0, 0,
                                       window->getSize().x, window->getSize().y));
    player_view.setCenter(active_view_position);
    window->setView(player_view);

    target.draw(active_player_shape, states);
    target.draw(player_text, states);
    target.draw(teacher1_shape, states);
    target.draw(teacher1_text, states);
    target.draw(teacher2_shape, states);
    target.draw(teacher2_text, states);
    target.draw(teacher3_shape, states);
    target.draw(teacher3_text, states);
    if (displayed_items[0].get_displayed()) {
        target.draw(item1_shape, states);
    }
    if (displayed_items[1].get_displayed()) {
        target.draw(item2_shape, states);
    }
    target.draw(menu_button, states);
    target.draw(menu_text, states);
}

}  // namespace university_game
