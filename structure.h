#ifndef UNIVERSITY_GAME_STRUCTURE_H
#define UNIVERSITY_GAME_STRUCTURE_H

#include <string>
#include <utility>
#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace university_game {
    const int v_table = 14;
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
            return "Name: " + get_name() + "\nUsage: " + get_usage() + ".\n\n";
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

        void draw(sf::RenderTarget &target, sf::RenderStates states) const override {
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

            sf::Font text_font;
            text_font.loadFromFile("C:/Users/bonda/cppgame/University_game/fonts/arial2.ttf");

            sf::Text quest_text;
            quest_text.setFont(text_font);
            quest_text.setString("Available quests:");
            quest_text.setCharacterSize(30);
            quest_text.setFillColor(sf::Color::Black);
            quest_text.setStyle(sf::Text::Bold);
            quest_text.setPosition(active_v * (cell_v_size) - 240, active_h * (cell_h_size) - 120);

            sf::Text inventory_text;
            inventory_text.setFont(text_font);
            inventory_text.setString("Your inventory:");
            inventory_text.setCharacterSize(30);
            inventory_text.setFillColor(sf::Color::Black);
            inventory_text.setStyle(sf::Text::Bold);
            inventory_text.setPosition(active_v * (cell_v_size) + 150, active_h * (cell_h_size) - 120);

            sf::Text level_text;
            level_text.setFont(text_font);
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

        void draw(sf::RenderTarget &target, sf::RenderStates states) const override {
            states.transform *= getTransform();

            sf::Color outline_color = sf::Color(73, 103, 113);

            sf::RectangleShape frame_shape(sf::Vector2f(720, 60));
            frame_shape.setFillColor(sf::Color::White);
            frame_shape.setOutlineThickness(10.f);
            frame_shape.setOutlineColor(outline_color);
            frame_shape.setPosition(active_v * (cell_v_size) - 250, active_h * (cell_h_size) - 50);

            sf::Font text_font;
            text_font.loadFromFile("C:/Users/bonda/cppgame/University_game/fonts/arial.ttf");

            sf::Text quest_text;
            quest_text.setFont(text_font);
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
    };

    struct bug : public sf::Drawable, public sf::Transformable {
    private:
        int id{};
    public:
        int active_x;
        int active_y;

        bug() = default;

        [[nodiscard]] int get_id() const {
            return id;
        }

        void create() {
            std::srand(std::time(nullptr));
            active_x = std::rand();
            active_y = std::rand();
        }

        std::pair<int, int> get_coordinates() {
            return std::make_pair(active_x, active_y);
        }

        void draw(sf::RenderTarget &target, sf::RenderStates states) const override {
            states.transform *= getTransform();

            sf::Texture bug_texture;
            bug_texture.loadFromFile("/Users/borismikhaylov/CLionProjects/University_game/images/bug.png");
            sf::RectangleShape frame_shape(sf::Vector2f(42, 40));
            frame_shape.setPosition(active_x * cell_h_size, active_y * cell_v_size);
            target.draw(frame_shape, states);
        }

        virtual ~bug() = default;
    };

    struct minigame_bugs : public sf::Drawable, public sf::Transformable {

        std::map<int, bug> id_bug;
        int count_bugs = 0;
        std::set<int> bugs_id;
        int map_width = 40;
        int map_height = 40;

        minigame_bugs() = default;

        void start() {

        }

        void add_bug() {
            bug new_bug{};
            new_bug.create();
            bugs_id.insert(new_bug.get_id());
            id_bug[new_bug.get_id()] = new_bug;
            count_bugs++;
        }

        void remove_bug(int cur_bug_id) {
            if (count_bugs <= 0) std::cerr << "You can't remove bug: there's no bugs left!"; //need stfl output
            id_bug.erase(cur_bug_id);
            bugs_id.erase(cur_bug_id);
            count_bugs--;
        }

        int get_number_of_bugs() const {
            return count_bugs;
        }

        void move_bug(int bug_id) {
            bug *cur_bug = &id_bug[bug_id];
            std::vector<std::pair<int, int>> moves{{0,  1},
                                                   {1,  0},
                                                   {-1, 0},
                                                   {0,  -1}};
            std::srand(std::time(nullptr));
            for (int i = 0; i < 10; ++i) {
                int direction = std::rand() % 4;
                if (cur_bug->active_x + moves[direction].first > 0 &&
                    cur_bug->active_x + moves[direction].first < map_height &&
                    cur_bug->active_y + moves[direction].second > 0 &&
                    cur_bug->active_y + moves[direction].second < map_width) {
                    cur_bug->active_x += moves[direction].first;
                    cur_bug->active_y += moves[direction].second;
                    return;
                }
            }

        }

        //returns -1 if bug not caught, otherwise gives id of caught bug
        int click_bug(int pos_x, int pos_y) {
            bool ans = false;
            bug cur_bug;
            for (int b: bugs_id) {
                cur_bug = id_bug[b];
                std::pair<int, int> coords = cur_bug.get_coordinates();
                bool cur = coords.first == pos_x && coords.second == pos_y;
                if (coords.first == pos_x && coords.second == pos_y) {
                    return b;
                }
            }
            return -1;
        }

        void draw(sf::RenderTarget &target, sf::RenderStates states) const override {
            states.transform *= getTransform();

            sf::Color outline_color = sf::Color(73, 103, 113);

            sf::Texture mg_bugs_carpet_texture;
            mg_bugs_carpet_texture.loadFromFile("/Users/borismikhaylov/CLionProjects/University_game/images/mg_bugs_carpet1.png");

            sf::RectangleShape mg_bug_field(sf::Vector2f(300, 100));
            mg_bug_field.setFillColor(sf::Color::White);
            mg_bug_field.setOutlineThickness(20.f);
            mg_bug_field.setOutlineColor(outline_color);
            target.draw(mg_bug_field, states);
            sf::RectangleShape mg_bugs_carpet(sf::Vector2f(cell_h_size, cell_v_size));
            mg_bugs_carpet.setTexture(&mg_bugs_carpet_texture);
            for (int i = 0; i < map_height; ++i){
                for (int j = 0; j < map_width; ++j){
                    sf::Vector2f position(i * cell_h_size, j * cell_v_size);
                    mg_bugs_carpet.setPosition(position);
                    target.draw(mg_bugs_carpet, states);
                }
            }
            sf::RectangleShape bug_shape(sf::Vector2f(42, 40));
            bug_shape.setTexture(&mg_bugs_carpet_texture);
            bug cur_bug;
            for (int b : bugs_id){
                cur_bug = id_bug.at(b);
                sf::Vector2f position(cur_bug.active_x, cur_bug.active_y);
                bug_shape.setPosition(position);
                target.draw(bug_shape, states);
            }
        }

    };

    struct question {
    private:
        std::string m_question;
        std::vector<std::string> m_answer;
    public:
        question(std::string mQuestion, std::vector<std::string> mAnswer) : m_question(std::move(mQuestion)),
                                                                            m_answer(std::move(mAnswer)) {}
    };

    struct minigame_zachet {
    private:
        int score = 0;
        std::vector<int> grades;
        std::vector<question> questions;
    public:
        explicit minigame_zachet(std::vector<int> grades) : grades(std::move(grades)) {}

        void add_question(const std::string &new_question, std::vector<std::string> answers) {
            questions.emplace_back(new_question, std::move(answers));
        }
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
            teachers.resize(2);
            displayed_items.resize(1);
            map = {{0,  0,  0,  0,  0,  -2, 0, 0, 0, 0, 0,  0, 0, 0},
                   {0,  2,  0,  0,  0,  -2, 0, 0, 0, 0, 0,  0, 0, 0},
                   {0,  0,  0,  0,  0,  -2, 0, 0, 0, 0, -1, 0, 0, 0},
                   {0,  0,  0,  0,  0,  0,  0, 0, 0, 0, 0,  0, 0, 0},
                   {-2, -2, -2, -2, -2, -2, 0, 0, 0, 0, 0,  0, 0, 0},
                   {0,  0,  0,  0,  0,  0,  0, 0, 0, 0, 0,  0, 3, 0}};
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

            if (iteration == 1) {
                if (direction == 1) {
                    if (!(active_v_compare < v_table - 1 && map[active_h_compare][active_v_compare + 1] == 0)) {
                        return false;
                    }
                    active_v += 0.02;
                    active_player.set_v_compare(++active_v_compare);
                }
                if (direction == 2) {
                    if (!(active_h_compare > 0 && map[active_h_compare - 1][active_v_compare] == 0)) {
                        return false;
                    }
                    active_h -= 0.02;
                    active_player.set_h_compare(--active_h_compare);
                }
                if (direction == 3) {
                    if (!(active_v_compare > 0 && map[active_h_compare][active_v_compare - 1] == 0)) {
                        return false;
                    }
                    active_v -= 0.02;
                    active_player.set_v_compare(--active_v_compare);
                }
                if (direction == 4) {
                    if (!(active_h_compare < h_table - 1 && map[active_h_compare + 1][active_v_compare] == 0)) {
                        return false;
                    }
                    active_h += 0.02;
                    active_player.set_h_compare(++active_h_compare);
                }
            } else {
                if (direction == 1) {
                    active_v += 0.02;
                }
                if (direction == 2) {
                    active_h -= 0.02;
                }
                if (direction == 3) {
                    active_v -= 0.02;
                }
                if (direction == 4) {
                    active_h += 0.02;
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

        void draw(sf::RenderTarget &target, sf::RenderStates states) const override {
            double active_v = active_player.get_v();
            double active_h = active_player.get_h();

            states.transform *= getTransform();

            sf::Color bg_color = sf::Color(254, 226, 183);
            sf::Color outline_color = sf::Color(58, 0, 0);

            // Рисуем рамку игрового поля
            sf::RectangleShape frame_shape(sf::Vector2f(1260, 750));
            frame_shape.setFillColor(sf::Color::White);
            frame_shape.setOutlineThickness(20.f);
            frame_shape.setOutlineColor(outline_color);
            target.draw(frame_shape, states);

            sf::Texture walkable_field_texture;
            walkable_field_texture.loadFromFile(
                    "/Users/borismikhaylov/CLionProjects/University_game/images/walkable_field.png");

            sf::Texture unwalkable_field_texture;
            unwalkable_field_texture.loadFromFile(
                    "/Users/borismikhaylov/CLionProjects/University_game/images/unwalkable_field.png");

            // Подготавливаем рамку для отрисовки всех плашек
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

            sf::Texture active_player_texture_front;
            active_player_texture_front.loadFromFile(
                    "/Users/borismikhaylov/CLionProjects/University_game/images/player_default.png");

            sf::Texture active_player_texture_right;
            active_player_texture_right.loadFromFile(
                    "/Users/borismikhaylov/CLionProjects/University_game/images/player_default_right.png");

            sf::Texture active_player_texture_left;
            active_player_texture_left.loadFromFile(
                    "/Users/borismikhaylov/CLionProjects/University_game/images/player_default_left.png");

            sf::Texture active_player_texture_back;
            active_player_texture_back.loadFromFile(
                    "/Users/borismikhaylov/CLionProjects/University_game/images/player_default_back.png");

            sf::Texture teacher_texture;
            teacher_texture.loadFromFile(
                    "/Users/borismikhaylov/CLionProjects/University_game/images/teacher_default.png");

            sf::Texture item_texture;
            item_texture.loadFromFile("/Users/borismikhaylov/CLionProjects/University_game/images/item_default.png");

            sf::RectangleShape active_player_shape(sf::Vector2f(cell_v_size, cell_h_size));
            if (active_player.get_direction() == 1) {
                active_player_shape.setTexture(&active_player_texture_right);
            } else if (active_player.get_direction() == 2) {
                active_player_shape.setTexture(&active_player_texture_back);
            } else if (active_player.get_direction() == 3) {
                active_player_shape.setTexture(&active_player_texture_left);
            } else if (active_player.get_direction() == 4) {
                active_player_shape.setTexture(&active_player_texture_front);
            }
            sf::Vector2f active_player_position(active_v * (cell_v_size),
                                                active_h * (cell_h_size));
            active_player_shape.setPosition(active_player_position);

            sf::RectangleShape teacher1_shape(sf::Vector2f(cell_v_size, cell_h_size));
            teacher1_shape.setTexture(&teacher_texture);
            sf::Vector2f teacher1_position(teachers[0].get_v() * (cell_v_size),
                                           teachers[0].get_h() * (cell_h_size));
            teacher1_shape.setPosition(teacher1_position);

            sf::RectangleShape teacher2_shape(sf::Vector2f(cell_v_size, cell_h_size));
            teacher2_shape.setTexture(&teacher_texture);
            sf::Vector2f teacher2_position(teachers[1].get_v() * (cell_v_size),
                                           teachers[1].get_h() * (cell_h_size));
            teacher2_shape.setPosition(teacher2_position);

            sf::RectangleShape item_shape(sf::Vector2f(cell_v_size, cell_h_size));
            item_shape.setTexture(&item_texture);
            sf::Vector2f item_position(displayed_items[0].get_v() * (cell_v_size),
                                       displayed_items[0].get_h() * (cell_h_size));
            item_shape.setPosition(item_position);

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
            if (displayed_items[0].get_displayed()) {
                target.draw(item_shape, states);
            }
            target.draw(menu_button, states);
            target.draw(menu_text, states);
        }
    };
}  //namespace university_game

#endif //UNIVERSITY_GAME_STRUCTURE_H