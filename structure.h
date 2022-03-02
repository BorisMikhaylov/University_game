#ifndef UNIVERSITY_GAME_STRUCTURE_H
#define UNIVERSITY_GAME_STRUCTURE_H

#include <string>
#include <iostream>
#include <utility>
#include <vector>
#include <utility>
#include <map>
#include <set>

namespace university_game {

    struct coordinates {
        int x;
        int y;

        coordinates() = default;

        coordinates(int x, int y) : x(x), y(y) {}
    };

    class quest {
    private:
        std::string name;
        std::string description;
        int required_level = 1;
        bool is_completed = false;
        int m_id{};

    public:
        quest() = default;

        explicit quest(std::string name_,
                       std::string description_,
                       int required_level_, int id)
                : name(std::move(name_)),
                  description(std::move(description_)),
                  required_level(required_level_), m_id(id) {}

        [[nodiscard]] int get_required_level() const {
            return required_level;
        }

        [[nodiscard]] int get_id() const {
            return m_id;
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
        coordinates m_coordinates{};

    public:
        player() = default;

        explicit player(std::string name_,
                        std::vector<quest> &list_of_quests_,
                        std::vector<item> &inventory_, coordinates coord)
                : name(std::move(name_)),
                  list_of_quests(list_of_quests_),
                  inventory(inventory_), m_coordinates(coord) {}

        [[nodiscard]] std::string get_name() const {
            return name;
        }

        [[nodiscard]] int get_level() const {
            return level;
        }

        [[nodiscard]] std::vector<quest> &get_list_of_quests() {
            return list_of_quests;
        }

        void add_to_inventory(const item &new_item) {
            inventory.push_back(new_item);
        }

        void check_for_level_up() {
            for (const auto &m_quest: list_of_quests) {
                if (m_quest.get_required_level() <= get_level() && !m_quest.get_condition()) {
                    return;
                }
            }
            std::cout << get_name() << " completed all quests of level "
                      << level++ << " and was level-upped!\n\n";
        }

        void display_available_quests() const {
            std::cout << "~ " << get_name() << "'s available quests:\n\n";
            for (const auto &m_quest: list_of_quests) {
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
            for (const auto &m_item: inventory) {
                m_item.get_info();
            }
        }
    };

    class teacher {
    private:
        std::string name;
        int m_id{};

    public:
        teacher() = default;

        explicit teacher(std::string name_, int id)
                : name(std::move(name_)), m_id(id) {}

        teacher(teacher const &teacher1) = default;

        [[nodiscard]] std::string get_name() const {
            return name;
        }

        [[nodiscard]] int get_id() const {
            return m_id;
        }

        void satisfy_quest(player &player_, const std::string &quest_name, const item &award) const {
            for (auto &quest: player_.get_list_of_quests()) {
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

    struct map {
    private:
        int height{}, width{};

        std::vector<std::vector<int>> field;

    public:

        map() = default;

        map(int x, int y) : height(x), width(y) {
            field.resize(x, std::vector<int>(y, 0));
        }

        [[maybe_unused]] void make_map(const std::string &input_map) {
            int i = 0;
            int j = 0;
            for (char c: input_map) {
                if (c == '\n') {
                    i = 0;
                    j++;
                    continue;
                }
                field[i][j] = (int) c;
            }
        }
    };

    struct game {
        //singleplayer
    private:
        player m_player;
        map m_map;
        std::vector<teacher> m_teachers;
        std::map<int, teacher> id_teacher;
        std::vector<quest> m_quests;
        std::map<int, quest> id_quests;
    public:
        explicit game(player player) : m_player(std::move(player)) {}

        void update_map(const map &new_map) {
            m_map = new_map;
        }

        void add_teacher(const teacher &new_teacher) {
            m_teachers.push_back(new_teacher);
            id_teacher[new_teacher.get_id()] = new_teacher;
        }

        void remove_teacher_by_id(int teacher_id) {
            for (auto &t: m_teachers) {
                if (t.get_id() == teacher_id) {
                    m_teachers.erase(m_teachers.begin() + teacher_id);
                    id_teacher.erase(teacher_id);
                    std::cout << "deleted!\n";
                    return;
                }
            }
            std::cout << "there's no that teacher.\n";
        }

        void add_quest(const quest &new_quest){
            m_quests.push_back(new_quest);
            id_quests[new_quest.get_id()] = new_quest;
        }

        void remove_quest_by_id(int quest_id){
            for (auto &q: m_quests) {
                if (q.get_id() == quest_id) {
                    m_quests.erase(m_quests.begin() + quest_id);
                    id_quests.erase(quest_id);
                    std::cout << "deleted!\n";
                    return;
                }
            }
            std::cout << "there's no that quest.\n";
        }


    };
}  //namespace university_game


#endif //UNIVERSITY_GAME_STRUCTURE_H
