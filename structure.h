//
// Created by Boris Mikhaylov on 13.02.2022.
//

#ifndef UNIVERSITY_GAME_STRUCTURE_H
#define UNIVERSITY_GAME_STRUCTURE_H

#include <string>
#include <utility>

namespace people{
    struct player{
        std::string m_name;

        explicit player(std::string &name){
            m_name = name;
        }
    };

    struct teacher{
        std::string m_name;

        explicit teacher(std::string &name){
            m_name = name;
        }
    };
}  //namespace people

struct quest{
private:
    std::string name;
    std::string definition;
};

#endif //UNIVERSITY_GAME_STRUCTURE_H
