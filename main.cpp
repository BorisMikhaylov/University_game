#include <iostream>
#include <vector>
#include "structure.h"

int main() {
    university_game::quest first_quest("first_quest", "1st description", 1);
    university_game::quest second_quest("second_quest", "2nd description", 2);
    std::vector<university_game::quest> initial_quests = {first_quest, second_quest};
    std::vector<university_game::item> initial_items{};

    university_game::player player_1("Fedor", initial_quests, initial_items);
    university_game::teacher teacher_1("Mr. Antipoff");

    player_1.display_available_quests();
    player_1.show_inventory();

    university_game::item first_prize("gold medal", "just useless, enjoy");
    teacher_1.satisfy_quest(player_1, "first_quest", first_prize);

    player_1.display_available_quests();
    player_1.show_inventory();
    return 0;
}
