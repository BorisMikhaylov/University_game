#ifndef UNIVERSITY_GAME_STRUCTURE_H
#define UNIVERSITY_GAME_STRUCTURE_H

#include <cmath>
#include <fstream>
#include <set>
#include <string>
#include <utility>
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <random>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <stdio.h>

#define PI 3.14159265359
namespace university_game {

    const std::string prefix = "/Users/borismikhaylov/CLionProjects/University_game";

    using byte = uint8_t;
    enum part_type {
        S, Z, L, J, SQR, I, T
    };

    struct Vec2 {
        byte y, x;

        Vec2() {}

        Vec2(byte dy, byte dx) : x(dx), y(dy) {}
    };

    struct part {
        Vec2 a, b, c, d;

        part() {}

        part(byte ax, byte ay, byte bx, byte by, byte cx, byte cy, byte dx, byte dy)
                : a(Vec2(ax, ay)), b(Vec2(bx, by)), c(Vec2(cx, cy)), d(Vec2(dx, dy)) {}

        part(Vec2 da, Vec2 db, Vec2 dc, Vec2 dd)
                : a(da), b(db), c(dc), d(dd) {}

        part create_part(part_type type) {
            switch (type) {
                case S :
                    return part(Vec2(1, 5), Vec2(1, 4), Vec2(0, 4), Vec2(2, 5));
                case Z:
                    return part(Vec2(1, 4), Vec2(1, 5), Vec2(0, 5), Vec2(2, 4));
                case L:
                    return part(Vec2(1, 5), Vec2(1, 4), Vec2(1, 6), Vec2(0, 6));
                case J:
                    return part(Vec2(1, 5), Vec2(1, 4), Vec2(1, 6), Vec2(0, 4));
                case SQR:
                    return part(Vec2(1, 5), Vec2(1, 4), Vec2(0, 5), Vec2(0, 4));
                case I:
                    return part(Vec2(1, 5), Vec2(1, 4), Vec2(1, 6), Vec2(1, 7));
                case T:
                    return part(Vec2(1, 5), Vec2(1, 4), Vec2(1, 6), Vec2(0, 5));
                default:
                    break;
            }
        }

        void rotate(part &part, byte colliders[16][12]) {
            float angle = 90 * (PI / 180);

            float b_offset_x = part.b.x - part.a.x;
            float c_offset_x = part.c.x - part.a.x;
            float d_offset_x = part.d.x - part.a.x;

            float b_offset_y = part.b.y - part.a.y;
            float c_offset_y = part.c.y - part.a.y;
            float d_offset_y = part.d.y - part.a.y;

            float pbx = part.a.x + (b_offset_x * cosf(angle) - b_offset_y * sinf(angle));
            float pby = part.a.y + (b_offset_x * sinf(angle) + b_offset_y * cosf(angle));

            float pcx = part.a.x + (c_offset_x * cosf(angle) - c_offset_y * sinf(angle));
            float pcy = part.a.y + (c_offset_x * sinf(angle) + c_offset_y * cosf(angle));

            float pdx = part.a.x + (d_offset_x * cosf(angle) - d_offset_y * sinf(angle));
            float pdy = part.a.y + (d_offset_x * sinf(angle) + d_offset_y * cosf(angle));

            if (colliders[(byte) pby][(byte) pbx] != 2 &&
                colliders[(byte) pcy][(byte) pcx] != 2 &&
                colliders[(byte) pdy][(byte) pdx] != 2 &&
                part.a.x != 1 && part.a.y != 1) {
                part.b.x = pbx;
                part.b.y = pby;

                part.c.x = pcx;
                part.c.y = pcy;

                part.d.x = pdx;
                part.d.y = pdy;
            }
        }
    };

    const int v_table = 28;
    const int h_table = 6;
    const int cell_v_size = 90;
    const int cell_h_size = 125;

    class item {
    private:
        std::string name;
        std::string usage;
        int active_v = 0;
        int active_h = 0;
        bool displayed = false;

    public:
        item() = default;

        explicit item(std::string name_, std::string usage_, int active_v_, int active_h_)
                : name(std::move(name_)),
                  usage(std::move(usage_)),
                  active_v(active_v_),
                  active_h(active_h_) {}

        [[nodiscard]] std::string get_name() const {
            return name;
        }

        [[nodiscard]] std::string get_usage() const {
            return usage;
        }

        [[nodiscard]] std::string get_info() const {
            return "Name: " + get_name() + "\nUsage: " + get_usage() + "\n\n";
        }

        [[nodiscard]] int get_v() const {
            return active_v;
        }

        [[nodiscard]] int get_h() const {
            return active_h;
        }

        [[nodiscard]] bool get_displayed() const {
            return displayed;
        }

        void set_displayed(bool condition) {
            displayed = condition;
        }
    };

    class quest {
    private:
        std::string name;
        std::string description;
        int required_level = 1;
        int is_completed = 0;
        item required_item;
        item award;

    public:
        quest() = default;

        explicit quest(std::string name_,
                       std::string description_,
                       int required_level_,
                       item required_item_,
                       item award_)
                : name(std::move(name_)),
                  description(std::move(description_)),
                  required_level(required_level_),
                  required_item(std::move(required_item_)),
                  award(std::move(award_)) {}

        [[nodiscard]] int get_required_level() const {
            return required_level;
        }

        [[nodiscard]] std::string get_name() const {
            return name;
        }

        [[nodiscard]] std::string get_description() const {
            return description;
        }

        [[nodiscard]] item get_required_item() const {
            return required_item;
        }

        [[nodiscard]] item get_award() const {
            return award;
        }

        [[nodiscard]] std::string get_condition() const {
            if (is_completed == 0) {
                return "NOT COMPLETED";
            }
            if (is_completed == 1) {
                return "IN PROGRESS";
            }
            if (is_completed == 2) {
                return "COMPLETED";
            }
            return "";
        }

        void mark_as_completed() {
            is_completed = 2;
        }

        void mark_as_in_progress() {
            is_completed = 1;
        }

        [[maybe_unused]] void create_from_json(const std::string &filename) {
            std::ifstream infile(prefix + "/json/" + filename);
            std::string input;
            std::getline(infile, input);

            rapidjson::Document d;
            d.Parse(input.c_str());

            required_item = item(d["required_item_name"].GetString(), d["required_item_usage"].GetString(),
                                 d["required_item_v"].GetInt(), d["required_item_h"].GetInt());
            award = item(d["award_item_name"].GetString(), d["award_item_usage"].GetString(),
                         d["award_item_v"].GetInt(), d["award_item_h"].GetInt());
            name = d["quest_name"].GetString();
            description = d["quest_description"].GetString();
            required_level = d["required_level"].GetInt();
            infile.close();
        }
    };

    class player : public sf::Drawable, public sf::Transformable {
    private:
        std::string name;
        int level = 1;
        std::vector<quest> list_of_quests{};
        std::vector<item> inventory{};
        double active_v = v_table / 2;
        double active_h = h_table / 2;
        int active_v_compare = v_table / 2;
        int active_h_compare = h_table / 2;
        std::string quest_taken;
        int direction = 4;
        int graphic_phase = 0;

    public:
        player() = default;

        explicit player(std::string name_,
                        std::vector<quest> &list_of_quests_,
                        std::vector<item> &inventory_)
                : name(std::move(name_)),
                  list_of_quests(list_of_quests_),
                  inventory(inventory_),
                  active_v(v_table / 2),
                  active_h(h_table / 2),
                  active_v_compare(v_table / 2),
                  active_h_compare(h_table / 2) {}

        void set_name(std::string new_name) {
            name = std::move(new_name);
        }

        [[nodiscard]] std::string get_name() const {
            return name;
        }

        [[nodiscard]] int get_level() const {
            return level;
        }

        [[nodiscard]] std::vector<quest> &get_list_of_quests() {
            return list_of_quests;
        }

        [[nodiscard]] double get_v() const {
            return active_v;
        }

        [[nodiscard]] double get_h() const {
            return active_h;
        }

        [[nodiscard]] int get_v_compare() const {
            return active_v_compare;
        }

        [[nodiscard]] int get_h_compare() const {
            return active_h_compare;
        }

        [[nodiscard]] std::string get_quest_taken() const {
            return quest_taken;
        }

        [[nodiscard]] std::vector<item> get_inventory() const {
            return inventory;
        }

        [[nodiscard]] int get_direction() const {
            return direction;
        }

        [[nodiscard]] int get_graphic_phase() const {
            return graphic_phase;
        }

        void set_graphic_phase(int new_graphic_phase) {
            graphic_phase = new_graphic_phase;
        }

        void set_direction(int new_direction) {
            direction = new_direction;
        }

        void set_quest_taken(const std::string &new_quest_name) {
            quest_taken = new_quest_name;
        }

        void set_v(double new_v) {
            active_v = new_v;
        }

        void set_h(double new_h) {
            active_h = new_h;
        }

        void set_v_compare(int new_v) {
            active_v_compare = new_v;
        }

        void set_h_compare(int new_h) {
            active_h_compare = new_h;
        }

        void add_to_inventory(const item &new_item) {
            inventory.push_back(new_item);
        }

        void set_inventory(std::vector<item> new_inventory) {
            inventory = std::move(new_inventory);
        }

        void check_for_level_up() {
            for (const auto &m_quest: list_of_quests) {
                if (m_quest.get_required_level() <= get_level() && m_quest.get_condition() == "NOT COMPLETED") {
                    return;
                }
            }
            level++;
        }

        [[nodiscard]] std::string display_available_quests() const {
            std::string res;
            int count = 1;
            for (const auto &m_quest: list_of_quests) {
                if (m_quest.get_required_level() <= get_level()) {
                    res += std::to_string(count++) + ") " + m_quest.get_name() + " ";
                    res += "\t'" + m_quest.get_condition() + "'\n";
                    res += m_quest.get_description() + "\n\n";
                }
            }
            return res;
        }

        [[nodiscard]] std::string show_inventory() const {
            std::string res;
            if (inventory.empty()) {
                res = "You have no items yet.\n\n";
                return res;
            }
            int count = 1;
            for (const auto &m_item: inventory) {
                res += std::to_string(count++) + ") " + m_item.get_info();
            }
            return res;
        }

        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    };

    class teacher : public sf::Drawable, public sf::Transformable {
    private:
        std::string name;
        int id = 2;
        int active_v = 0;
        int active_h = 0;
        std::vector<std::string> phrases;
        std::string associated_quest_name;
        int quest_stage = 0;

    public:
        teacher() = default;

        explicit teacher(std::string name_, int id_, int active_v_, int active_h_,
                         std::vector<std::string> phrases_, std::string associated_quest_name_)
                : name(std::move(name_)),
                  id(id_),
                  active_v(active_v_),
                  active_h(active_h_),
                  phrases(std::move(phrases_)),
                  associated_quest_name(std::move(associated_quest_name_)) {}

        [[nodiscard]] std::string get_name() const {
            return name;
        }

        [[nodiscard]] int get_v() const {
            return active_v;
        }

        [[nodiscard]] int get_h() const {
            return active_h;
        }

        [[nodiscard]] int get_id() const {
            return id;
        }

        [[nodiscard]] int get_quest_stage() const {
            return quest_stage;
        }

        [[nodiscard]] std::string get_associated_quest_name() const {
            return associated_quest_name;
        }

        void satisfy_quest(player &player_) {
            if (!(player_.get_quest_taken().empty()
                  || player_.get_quest_taken() == associated_quest_name)) {
                return;
            }
            for (auto &quest: player_.get_list_of_quests()) {
                if (quest.get_name() != associated_quest_name) {
                    continue;
                }
                if (quest.get_condition() == "NOT COMPLETED") {
                    quest.mark_as_in_progress();
                    quest_stage++;
                    player_.set_quest_taken(associated_quest_name);
                } else if (quest.get_condition() == "IN PROGRESS") {
                    if (quest.get_required_item().get_name() == "none") {
                        quest_stage++;
                        quest.mark_as_completed();
                        return;
                    }
                    for (auto &item_: player_.get_inventory()) {
                        if (item_.get_name() != quest.get_required_item().get_name()) {
                            continue;
                        }
                        std::vector<item> new_items;
                        for (auto &new_item_: player_.get_inventory()) {
                            if (new_item_.get_name() != quest.get_required_item().get_name()) {
                                new_items.push_back(new_item_);
                            }
                        }
                        player_.set_inventory(new_items);
                        quest_stage++;
                        quest.mark_as_completed();
                        break;
                    }
                } else if (quest.get_condition() == "COMPLETED") {
                    quest_stage++;
                    bool flag = false;
                    if (quest.get_award().get_name() == "none") {
                        flag = true;
                    } else {
                        for (auto &new_item_: player_.get_inventory()) {
                            if (new_item_.get_name() == quest.get_award().get_name()) {
                                flag = true;
                                break;
                            }
                        }
                    }
                    if (!flag) {
                        player_.add_to_inventory(quest.get_award());
                    }
                    player_.check_for_level_up();
                    player_.set_quest_taken("");
                }
                break;
            }
        }

        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    };

    struct bug {
        int id;
        int active_x;
        int active_y;

        bug() = default;

        bug(int pos_x, int pos_y, int new_id) : active_x(pos_x), active_y(pos_y), id(new_id) {

        }

        [[nodiscard]] int get_id() const {
            return id;
        }

        ~bug() = default;
    };

    struct minigame_bugs : public sf::Drawable, public sf::Transformable {

        sf::RenderWindow *window = nullptr;
        int count_bugs = 0;
        int all_ids = 0;
        std::map<int, bug> id_bug;
        std::set<int> bugs_id;
        int v_size = 0;
        int h_size = 0;

        minigame_bugs() = default;

        minigame_bugs(sf::RenderWindow *window_) : window(window_), v_size(window_->getSize().x),
                                                   h_size(window_->getSize().y) {
            add_bug();
        }

        void add_bug() {
            bug new_bug(rand() % (v_size-cell_v_size), rand() % (h_size-cell_h_size), all_ids++);
            bugs_id.insert(new_bug.get_id());
            id_bug[new_bug.get_id()] = new_bug;
            count_bugs++;
        }

        void remove_bug(int cur_bug_id) {
            id_bug.erase(cur_bug_id);
            bugs_id.erase(cur_bug_id);
            count_bugs--;
        }

        void move_bug(int bug_id) {
            bug *cur_bug = &id_bug[bug_id];
            int step = 2;
            std::vector<std::pair<int, int>> moves{{0,     step},
                                                   {step,  0},
                                                   {-step, 0},
                                                   {0,     -step}};
            //std::srand(std::time(nullptr));
            for (int i = 0; i < 10; ++i) {
                int direction = std::rand() % 4;
                if (id_bug[bug_id].active_x + moves[direction].first > 0 &&
                    id_bug[bug_id].active_x + moves[direction].first < v_size - cell_v_size &&
                    id_bug[bug_id].active_y + moves[direction].second > 0 &&
                    id_bug[bug_id].active_y + moves[direction].second < h_size - cell_h_size) {

                    id_bug[bug_id].active_x += moves[direction].first;
                    id_bug[bug_id].active_y += moves[direction].second;
                    return;
                }
            }

        }

        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    };

    struct sudoku_cell {
    private:
        int value = 0;
        bool changeable = true; //initially generated numbers cannot be changed
    public:
        sudoku_cell() = default;

        explicit sudoku_cell(int value_, bool changeable_) : value(value_), changeable(changeable_) {}

        void set_to_unchangeable(bool new_change) {
            changeable = new_change;
        }

        [[nodiscard]] bool get_changeable() const {
            return changeable;
        }

        void set_value(int new_value) {
            value = new_value;
        }

        [[nodiscard]] int get_value() const {
            return value;
        }
    };

    class sudoku_game : public sf::Drawable, public sf::Transformable {
    private:
        int selected_x_cord = 0;
        int selected_y_cord = 0;
        std::vector<std::vector<sudoku_cell>> current_map;
        std::vector<std::vector<int>> solution;
        int number_of_correct_placements = 0;
        int center_x_cord = 0;
        int center_y_cord = 0;
    public:
        sudoku_game() : current_map(9), solution(9) {};

        void new_sudoku(int center_x, int center_y) {
            number_of_correct_placements = 81;
            center_x_cord = center_x, center_y_cord = center_y;
            solution = {
                    {1, 2, 3, 4, 5, 6, 7, 8, 9},
                    {4, 5, 6, 7, 8, 9, 1, 2, 3},
                    {7, 8, 9, 1, 2, 3, 4, 5, 6},

                    {2, 3, 1, 5, 6, 4, 8, 9, 7},
                    {5, 6, 4, 8, 9, 7, 2, 3, 1},
                    {8, 9, 7, 2, 3, 1, 5, 6, 4},

                    {3, 1, 2, 6, 4, 5, 9, 7, 8},
                    {6, 4, 5, 9, 7, 8, 3, 1, 2},
                    {9, 7, 8, 3, 1, 2, 6, 4, 5}
            };

            std::srand(std::time(nullptr));

            for (int i = 0; i < 9; ++i) {//swap random sets of equal numbers
                current_map[i].clear();
                int j = rand() % 9;
                for (int x = 0; x < 9; ++x) {
                    for (int y = 0; y < 9; ++y) {
                        if (solution[x][y] == i + 1) {
                            solution[x][y] = j + 1;
                        } else if (solution[x][y] == j + 1) {
                            solution[x][y] = i + 1;
                        }
                    }
                }
            }

            for (int i = 0; i < 9; ++i) {//shuffle strings in every string trio
                int second_string = rand() % 3;
                int group = i / 3;
                for (int j = 0; j < 9; ++j) {
                    std::swap(solution[i][j], solution[group * 3 + second_string][j]);
                }
            }

            for (int i = 0; i < 9; ++i) {//shuffle columns in every column trio
                int second_column = rand() % 3;
                int group = i / 3;
                for (int j = 0; j < 9; ++j) {
                    std::swap(solution[j][i], solution[j][group * 3 + second_column]);
                }
            }

            for (int i = 0; i < 3; ++i) { //shuffle string trios
                int str_trio = rand() % 3;
                for (int k = 0; k < 3; ++k) {
                    for (int j = 0; j < 9; ++j) {
                        std::swap(solution[i * 3 + k][j], solution[str_trio * 3 + k][j]);
                    }
                }
            }

            for (int i = 0; i < 3; ++i) { //shuffle column trios
                int vertical_trio = rand() % 3;
                for (int k = 0; k < 3; ++k) {
                    for (int j = 0; j < 9; ++j) {
                        std::swap(solution[j][i * 3 + k], solution[j][vertical_trio * 3 + k]);
                    }
                }
            }

            std::vector<std::pair<int, int>> random_order;
            for (int i = 0; i < 9; ++i) {
                for (int j = 0; j < 9; ++j) {
                    current_map[i].emplace_back(sudoku_cell(solution[i][j], true));
                    random_order.emplace_back(std::make_pair(i, j));
                }
            }

            auto rng = std::default_random_engine{};
            std::shuffle(random_order.begin(), random_order.end(), rng);

            for (int i = 0; i < 81; ++i) {
                if (removeable(random_order[i].first, random_order[i].second)) {
                    --number_of_correct_placements;
                    current_map[random_order[i].first][random_order[i].second].set_value(-1);
                } else {
                    current_map[random_order[i].first][random_order[i].second].set_to_unchangeable(false);
                }
            }
        }

        bool removeable(int i, int j) {
            int removed_value = current_map[i][j].get_value();
            current_map[i][j].set_value(-1);
            for (int a = 0; a < 3; ++a) {
                for (int b = 0; b < 3; ++b) {
                    if (!(a == i % 3 && b == j % 3)) {
                        if (placeable((i / 3) * 3 + a, (j / 3) * 3 + b, removed_value)) {
                            current_map[i][j].set_value(removed_value);
                            return false;
                        }
                    }
                }
            }
            return true;
        }

        bool placeable(int i, int j, int val) {
            if (current_map[i][j].get_value() != -1) {
                return false;
            }
            for (int x = 0; x < 9; ++x) {
                if (current_map[x][j].get_value() == val) {
                    return false;
                }
                if (current_map[i][x].get_value() == val) {
                    return false;
                }
            }
            return true;
        }

        void set_selected_cell(int i, int j) {
            if ((0 <= i) && (i < 9) && (0 <= j) && (j < 9)) {
                selected_x_cord = i;
                selected_y_cord = j;
            }
        }

        bool set_value(int value) {
            if (!(((0 < value) && (value < 10)) || value == -1)) {
                return false;
            }
            if (!current_map[selected_y_cord][selected_x_cord].get_changeable()) {
                return false;
            }
            if (value == solution[selected_y_cord][selected_x_cord]) {
                if (current_map[selected_y_cord][selected_x_cord].get_value() !=
                    solution[selected_y_cord][selected_x_cord]) {
                    ++number_of_correct_placements;
                }
            }
            if (value != solution[selected_y_cord][selected_x_cord]) {
                if (current_map[selected_y_cord][selected_x_cord].get_value() ==
                    solution[selected_y_cord][selected_x_cord]) {
                    --number_of_correct_placements;
                }
            }
            current_map[selected_y_cord][selected_x_cord].set_value(value);
            return (number_of_correct_placements >= 81);
        }

        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    };

    class game : public sf::Drawable, public sf::Transformable {
    private:
        sf::RenderWindow *window = nullptr;
        sf::Font text_font;
        player active_player;
        std::vector<std::vector<int>> map;
        std::vector<teacher> teachers;
        std::vector<item> displayed_items;

    public:
        game(sf::RenderWindow *window_, const sf::Font &text_font_, player new_player) :
                window(window_),
                text_font(text_font_),
                active_player(std::move(new_player)) {
            map.resize(h_table);
            for (auto &line: map) {
                line.resize(v_table);
            }
            teachers.resize(3);
            displayed_items.resize(2);
            map = {{0,  0,  0,  0,  0,  -2, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, -2, 0, 0, 0,  0,  0,  0, 0, 0, 0, 0},
                   {0,  2,  0,  0,  0,  -2, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, -1, 0, 0, 0,  0,  0,  0, 0, 0, 0, 0},
                   {0,  0,  0,  0,  0,  -2, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, -2, 0, 0, 0,  0,  4,  0, 0, 0, 0, 0},
                   {0,  0,  0,  0,  0,  0,  0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, -2, 0, 0, -2, -2, -2, 0, 0, 0, 0, 0},
                   {-2, -2, -2, -2, -2, -2, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0,  0, 0, 0,  0,  0,  0, 0, 0, 0, 0},
                   {0,  0,  0,  0,  0,  0,  0, 0, 0, 0, 0,  0, 3, 0, 0, 0, 0, 0,  0, 0, 0,  0,  0,  0, 0, 0, 0, 0}};
        }

        [[nodiscard]] int check_presence_of_teacher() {
            int active_v = active_player.get_v_compare();
            int active_h = active_player.get_h_compare();
            for (auto &teacher_: teachers) {
                int teacher_active_v = teacher_.get_v();
                int teacher_active_h = teacher_.get_h();
                if (abs(active_h - teacher_active_h) <= 1 && abs(active_v - teacher_active_v) <= 1) {
                    for (auto &quest_: active_player.get_list_of_quests()) {
                        if (quest_.get_name() == teacher_.get_associated_quest_name()) {
                            if (quest_.get_required_level() <= active_player.get_level()) {
                                return teacher_.get_id();
                            } else {
                                return 0;
                            }
                        }
                    }
                }
            }
            return 0;
        }

        void take_item_if_possible() {
            int active_v = active_player.get_v_compare();
            int active_h = active_player.get_h_compare();
            for (auto &item_: displayed_items) {
                int item_active_v = item_.get_v();
                int item_active_h = item_.get_h();
                if (abs(active_h - item_active_h) <= 1 && abs(active_v - item_active_v) <= 1 && item_.get_displayed()) {
                    item_.set_displayed(false);
                    active_player.add_to_inventory(item_);
                    map[item_.get_h()][item_.get_v()] = 0;
                }
            }
        }

        bool move(int direction, int iteration) {
            double active_v = active_player.get_v();
            double active_h = active_player.get_h();
            int active_v_compare = active_player.get_v_compare();
            int active_h_compare = active_player.get_h_compare();
            active_player.set_direction(direction);

            if (iteration % 100 == 0) {
                active_player.set_graphic_phase((active_player.get_graphic_phase() + 1) % 2);
            }

            if (iteration == 1) {
                if (direction == 1) {
                    if (!(active_v_compare < v_table - 1 && map[active_h_compare][active_v_compare + 1] == 0)) {
                        return false;
                    }
                    active_v += 0.002;
                    active_player.set_v_compare(++active_v_compare);
                }
                if (direction == 2) {
                    if (!(active_h_compare > 0 && map[active_h_compare - 1][active_v_compare] == 0)) {
                        return false;
                    }
                    active_h -= 0.002;
                    active_player.set_h_compare(--active_h_compare);
                }
                if (direction == 3) {
                    if (!(active_v_compare > 0 && map[active_h_compare][active_v_compare - 1] == 0)) {
                        return false;
                    }
                    active_v -= 0.002;
                    active_player.set_v_compare(--active_v_compare);
                }
                if (direction == 4) {
                    if (!(active_h_compare < h_table - 1 && map[active_h_compare + 1][active_v_compare] == 0)) {
                        return false;
                    }
                    active_h += 0.002;
                    active_player.set_h_compare(++active_h_compare);
                }
            } else {
                if (iteration == 500) {
                    active_player.set_graphic_phase(0);
                }
                if (direction == 1) {
                    active_v += 0.002;
                }
                if (direction == 2) {
                    active_h -= 0.002;
                }
                if (direction == 3) {
                    active_v -= 0.002;
                }
                if (direction == 4) {
                    active_h += 0.002;
                }
            }
            active_player.set_h(active_h);
            active_player.set_v(active_v);
            return true;
        }

        [[nodiscard]] player &get_player() {
            return active_player;
        }

        [[nodiscard]] std::vector<teacher> &get_teachers() {
            return teachers;
        }

        [[nodiscard]] std::vector<std::vector<int>> &get_map() {
            return map;
        }

        [[nodiscard]] std::vector<item> &get_displayed_items() {
            return displayed_items;
        }

        void load_textures();

        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    };

}  // namespace university_game

#endif //UNIVERSITY_GAME_STRUCTURE_H