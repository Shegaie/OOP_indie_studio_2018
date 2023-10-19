/*
** EPITECH PROJECT, 2022
** bomberman
** File description:
** Created by Pierre Chaudron
*/

#ifndef BOMBERMAN_ISCENE_H
#define BOMBERMAN_ISCENE_H

#include <string>
#include <vector>

typedef enum scene_e {
    MENU,
    GAME
} scene_t;

typedef enum skin_e {
    PINK,
    BLUE,
    RED,
    WHITE
} skin_t;

typedef struct game_params_s {
    bool multiplayer;
    skin_t skinPlayerOne;
    skin_t skinPlayerTwo;
    bool loaded;
    std::vector<std::string> mapString;
    std::vector<std::string> playerInfos;
    std::vector<std::string> aiInfos;

} game_params_t;

class IScene {
    public:
        virtual scene_t runScene() = 0;
};

#endif //BOMBERMAN_ISCENE_H