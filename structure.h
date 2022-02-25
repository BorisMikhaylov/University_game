#ifndef UNIVERSITY_GAME_STRUCTURE_H
#define UNIVERSITY_GAME_STRUCTURE_H

#include <string>
#include <utility>

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
}  //namespace university_game

#endif //UNIVERSITY_GAME_STRUCTURE_H
