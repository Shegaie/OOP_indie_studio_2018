/*
** EPITECH PROJECT, 2019
** bomberman
** File description:
** AI.cpp
*/

#include <algorithm>
#include <iostream>

#include "AI.hpp"

AI::AI(int posX, int posY, irr::scene::ISceneManager *sceneManager,
    irr::video::IVideoDriver *driver, int color
) : Player(posX, posY, sceneManager, driver, color)
{
    old_pos = {0, 0};
    direction = 3;
}

AI::~AI()
{
}

std::vector<int> AI::check_around(char c, std::vector<std::string> mapString)
{
    std::vector<int> check_pos;
    if (mapString[up + 1][x] == c)
        check_pos.emplace_back(0);
    if (mapString[y][right + 1] == c)
        check_pos.emplace_back(1);
    if (mapString[down - 1][x] == c)
        check_pos.emplace_back(2);
    if (mapString[y][left - 1] == c)
        check_pos.emplace_back(3);
    return (check_pos);
}

void AI::init_positions()
{
    up = static_cast<int>(std::round((position.Y - 4) / 10));
    down = static_cast<int>(std::round((position.Y + 4) / 10));
    left = static_cast<int>(std::round((position.X + 4) / 10));
    right = static_cast<int>(std::round((position.X - 4) / 10));
    x = static_cast<int>(std::round(position.X / 10));
    y = static_cast<int>(std::round(position.Y / 10));
}

int AI::move_IA(std::vector<int> &around,
    const std::vector<irr::scene::IMeshSceneNode *> &Cubes,
    const std::vector<irr::scene::IMeshSceneNode *> &Blocks, std::vector<Player> &players, std::vector<std::vector<Bomb>> &AIBombs)
{
    unsigned long n = 0;

    if (!around.empty()) {
        n = rand() % around.size();
        movePlayer(around[n], Cubes, Blocks, players, AIBombs);
        old_pos.first = y;
        old_pos.second = x;
        direction = around[n];
        return 0;
    }
    return 1;
}

void AI::chooseTheAiWay(const std::vector<irr::scene::IMeshSceneNode *> &Cubes,
    const std::vector<irr::scene::IMeshSceneNode *> &Blocks,
    irr::scene::ISceneManager *sceneManager, irr::video::IVideoDriver *driver,
    Map &map, std::vector<Player> &players, std::vector<std::vector<Bomb>> &AIBombs)
{
    std::vector<std::string> mapString = map.getMapString();
    std::vector<int> around;
    std::vector<int> ready;

    init_positions();
    around = check_around('o', mapString);
    ready = check_around(' ', mapString);
    if ((direction == 0 && mapString[up][x] == 'B') || (direction == 1 && mapString[y][right] == 'B') || (direction == 2 && mapString[down][x] == 'B') || (direction == 3 && mapString[y][left] == 'B') && mapString[y][x] == 'B') {
            move_IA(around, Cubes, Blocks, players, AIBombs);
    } else if (mapString[y][x] == 'o')
        defensive_action(mapString, Cubes, Blocks, players, AIBombs);
    else
        offensive_action(map, mapString, sceneManager, driver, Cubes, Blocks, players, AIBombs);
}

void AI::defensive_action(std::vector<std::string> mapString,
    const std::vector<irr::scene::IMeshSceneNode *> &Cubes,
    const std::vector<irr::scene::IMeshSceneNode *> &Blocks, std::vector<Player> &players, std::vector<std::vector<Bomb>> &AIBombs)
{
    std::vector<int> around = check_around(' ', mapString);

    if (move_IA(around, Cubes, Blocks, players, AIBombs) == 1)
        movePlayer(direction, Cubes, Blocks, players, AIBombs);
}

void AI::offensive_action(Map &map, std::vector<std::string> mapString,
    irr::scene::ISceneManager *sceneManager, irr::video::IVideoDriver *driver,
    const std::vector<irr::scene::IMeshSceneNode *> &Cubes,
    const std::vector<irr::scene::IMeshSceneNode *> &Blocks, std::vector<Player> &players, std::vector<std::vector<Bomb>> &AIBombs)
{
    std::vector<int> around = check_around('+', mapString);
    std::vector<int> ready = check_around(' ', mapString);
    std::vector<int> danger = check_around('o', mapString);

    if (!around.empty() && !ready.empty() && danger.empty())
        dropBomb(sceneManager, driver, map);
    else if (((direction == 0 && mapString[up + 1][x] == '#') ||
        (direction == 1 && mapString[y][right + 1] == '#') ||
        (direction == 2 && mapString[down - 1][x] == '#') ||
        (direction == 3 && mapString[y][left - 1] == '#')) && !ready.empty())
        move_IA(ready, Cubes, Blocks, players, AIBombs);
    else
        movePlayer(direction, Cubes, Blocks, players, AIBombs);
}