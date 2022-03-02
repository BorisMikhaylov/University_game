#ifndef UNIVERSITY_GAME_STRUCTURE_H
#define UNIVERSITY_GAME_STRUCTURE_H

#include <string>
#include <utility>
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace university_game {

class quest {
private:
    std::string name;
    std::string description;
    int required_level = 1;
    bool is_completed = false;

public:
    quest() = default;

    explicit quest(std::string name_,
                   std::string description_,
                   int required_level_)
        : name(std::move(name_)),
          description(std::move(description_)),
          required_level(required_level_) {}

    [[nodiscard]] int get_required_level() const {
        return required_level;
    }

    [[nodiscard]] std::string get_name() const {
        return name;
    }

    [[nodiscard]] std::string get_description() const {
        return description;
    }

    [[nodiscard]] bool get_condition() const {
        return is_completed;
    }

    void mark_as_completed() {
        is_completed = true;
    }
};

class item {
private:
    std::string name;
    std::string usage;
public:
    item() = default;

    explicit item(std::string name_, std::string usage_) : name(std::move(name_)), usage(std::move(usage_)) {}

    [[nodiscard]] std::string get_name() const {
        return name;
    }

    [[nodiscard]] std::string get_usage() const {
        return usage;
    }

    void get_info() const {
        std::cout << "Name: " << get_name() << "\nUsage: " << get_usage() << ".\n\n";
    }
};

class player {
private:
    std::string name;
    int level = 1;
    std::vector<quest> list_of_quests{};
    std::vector<item> inventory{};

public:
    player() = default;

    explicit player(std::string name_,
                    std::vector<quest> &list_of_quests_,
                    std::vector<item> &inventory_)
        : name(std::move(name_)),
          list_of_quests(list_of_quests_),
          inventory(inventory_) {}

    [[nodiscard]] std::string get_name() const {
        return name;
    }

    [[nodiscard]] int get_level() const {
        return level;
    }

    [[nodiscard]] std::vector<quest> &get_list_of_quests() {
        return list_of_quests;
    }

    void add_to_inventory(const item& new_item) {
        inventory.push_back(new_item);
    }

    void check_for_level_up() {
        for (const auto &m_quest : list_of_quests) {
            if (m_quest.get_required_level() <= get_level() && !m_quest.get_condition()) {
                return;
            }
        }
        std::cout << get_name() << " completed all quests of level "
                  << level++ << " and was level-upped!\n\n";
    }

    void display_available_quests() const {
        std::cout << "~ " << get_name() << "'s available quests:\n\n";
        for (const auto &m_quest : list_of_quests) {
            if (m_quest.get_required_level() <= get_level()) {
                std::cout << m_quest.get_name() << " ";
                if (m_quest.get_condition()) {
                    std::cout << "\t'COMPLETED'\n";
                } else {
                    std::cout << "\t'NOT COMPLETED'\n";
                }
            }
        }
        std::cout << "\n";
    }

    void show_inventory() const {
        if (inventory.empty()) {
            std::cout << "~ " << get_name() << " has no items!\n\n";
            return;
        }
        std::cout << "~ " << get_name() << "'s items:\n\n";
        for (const auto &m_item : inventory) {
            m_item.get_info();
        }
    }
};

class teacher {
private:
    std::string name;

public:
    teacher() = default;

    explicit teacher(std::string name_)
        : name(std::move(name_)) {}

    [[nodiscard]] std::string get_name() const {
        return name;
    }

    void satisfy_quest(player &player_, const std::string& quest_name, const item& award) const {
        for (auto &quest : player_.get_list_of_quests()) {
            if (quest.get_name() == quest_name) {
                quest.mark_as_completed();
                std::cout << "~ " << get_name() << " confirmed, that " << player_.get_name()
                          << " completed '" << quest_name << "'.\n\n";
                player_.add_to_inventory(award);
                std::cout << player_.get_name() << " was awarded with '" << award.get_name() << "'!\n\n";
                player_.check_for_level_up();
                break;
            }
        }
    }
};

const int v_table = 13;
const int h_table = 5;
const int cell_v_size = 90;
const int cell_h_size = 125;
class game : public sf::Drawable, public sf::Transformable {
private:
    player active_player;
    std::vector<std::vector<bool>> map;
    int active_v = 0;
    int active_h = 0;
public:
    game() {
        map.resize(h_table);
        for (auto &line : map) {
            line.resize(v_table);
        }
        map[0][0] = true;
    }

    void move(int direction) {
        if (direction == 1 && active_v < v_table - 1) {
            map[active_h][active_v++] = false;
            map[active_h][active_v] = true;
            return;
        }
        if (direction == 2 && active_h > 0) {
            map[active_h--][active_v] = false;
            map[active_h][active_v] = true;
            return;
        }
        if (direction == 3 && active_v > 0) {
            map[active_h][active_v--] = false;
            map[active_h][active_v] = true;
            return;
        }
        if (direction == 4 && active_h < h_table - 1) {
            map[active_h++][active_v] = false;
            map[active_h][active_v] = true;
            return;
        }
    }

    [[nodiscard]] player &get_player() {
        return active_player;
    }

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        states.transform *= getTransform();
        sf::Color color = sf::Color(200, 100, 200);

        // Рисуем рамку игрового поля
        sf::RectangleShape shape(sf::Vector2f(1200, 640));
        shape.setOutlineThickness(2.f);
        shape.setOutlineColor(color);
        shape.setFillColor(sf::Color::Transparent);
        target.draw(shape, states);

        // Подготавливаем рамку для отрисовки всех плашек
        shape.setSize(sf::Vector2f(cell_v_size - 2, cell_h_size - 2));
        shape.setOutlineThickness(1.f);
        shape.setOutlineColor(color);
        shape.setFillColor(sf::Color::Transparent);

        for (unsigned int i = 0; i < h_table; i++) {
            for (unsigned int j = 0; j < v_table; j++) {
                shape.setOutlineColor(color);
                sf::Vector2f position(j * (cell_v_size + 2) + 5.f, i * (cell_h_size + 2) + 5.f);
                shape.setPosition(position);
                target.draw(shape, states);
            }
        }
        sf::Texture active_player_texture;
        active_player_texture.loadFromFile("C:/Users/bonda/cppgame/University_game/images/player_default.png");

        sf::RectangleShape active_player_shape(sf::Vector2f(cell_v_size, cell_h_size));
        active_player_shape.setTexture(&active_player_texture);

        sf::Vector2f active_player_position(active_v * (cell_v_size + 2) + 5.f, active_h * (cell_h_size + 2) + 5.f);
        active_player_shape.setPosition(active_player_position);
        target.draw(active_player_shape, states);
    }
};
}  //namespace university_game

#endif //UNIVERSITY_GAME_STRUCTURE_H
