#include <iostream>
#include <fstream>
#include <string>

// example of .json file, created by this program:

// { "quest_name" : "", "quest_description" : "", "required_level" : 1,
//   "required_item_name" : "", "required_item_usage" : "",
//   "required_item_v" : 0, "required_item_h" : 0,
//   "award_item_name" : "", "award_item_usage" : "",
//   "award_item_v" : 0, "award_item_h" : 0 }

int main() {
    std::string temp;
    std::cout << "Enter the filename of your new quest: \n";
    getline(std::cin, temp);

    // for quest

    std::ofstream filename(temp + ".json");
    std::string new_json = " { \"quest_name\" : ";

    std::cout << "Enter the value of field \"quest_name\": \n";
    getline(std::cin, temp);
    new_json += "\"" + temp + R"(", "quest_description" : )";

    std::cout << "Enter the value of field \"quest_description\": \n";
    getline(std::cin, temp);
    new_json += "\"" + temp + R"(", "required_level" : )";

    std::cout << "Enter the value of field \"required_level\" (int): \n";
    getline(std::cin, temp);
    new_json += temp + R"(, "required_item_name" : )";

    // for required item

    std::cout << "Enter the value of field \"required_item_name\": \n";
    getline(std::cin, temp);
    new_json += "\"" + temp + R"(", "required_item_usage" : )";

    std::cout << "Enter the value of field \"required_item_usage\": \n";
    getline(std::cin, temp);
    new_json += "\"" + temp + R"(", "required_item_v" : )";

    std::cout << "Enter the value of field \"required_item_v\" (int): \n";
    getline(std::cin, temp);
    new_json += temp + R"(, "required_item_h" : )";

    std::cout << "Enter the value of field \"required_item_h\" (int): \n";
    getline(std::cin, temp);
    new_json += temp + R"(, "award_item_name" : )";

    // for award item

    std::cout << "Enter the value of field \"award_item_name\": \n";
    getline(std::cin, temp);
    new_json += "\"" + temp + R"(", "award_item_usage" : )";

    std::cout << "Enter the value of field \"award_item_usage\": \n";
    getline(std::cin, temp);
    new_json += "\"" + temp + R"(", "award_item_v" : )";

    std::cout << "Enter the value of field \"award_item_v\" (int): \n";
    getline(std::cin, temp);
    new_json += temp + R"(, "award_item_h" : )";

    std::cout << "Enter the value of field \"award_item_h\" (int): \n";
    getline(std::cin, temp);
    new_json += temp + R"( } )";

    // write to new json file

    filename << new_json << "\n";
    filename.close();
    return 0;
}