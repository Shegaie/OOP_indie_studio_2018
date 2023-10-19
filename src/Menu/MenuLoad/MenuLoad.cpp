/*
** EPITECH PROJECT, 2022
** bomberman
** File description:
** Created by Pierre Chaudron
*/

#include <fstream>
#include <iostream>
#include "EventManager/EventManager.hpp"
#include "MenuLoad.hpp"

MenuLoad::MenuLoad(irr::IrrlichtDevice *deviceArg,
    irr::video::IVideoDriver *driverArg, game_params_t &params
) : device(deviceArg), driver(driverArg), gameParams(params)
{
    error = 0;
}

menu_t MenuLoad::manageEvents()
{
    return LOAD;
}

void MenuLoad::drawTextures()
{
}

void MenuLoad::updateElements()
{
    std::fstream fs;
    std::string line;
    fs.open(".save", std::fstream::in | std::fstream::out | std::fstream::app);
    gameParams.loaded = true;
    std::getline(fs, line);
    if (line.empty()) {
        error = 1;
        return;
    }
    while (line != " ") {
        gameParams.mapString.emplace_back(line);
        std::getline(fs, line);
    }
    while (!line.empty()) {
        std::getline(fs, line);
        if (line[0] == '1')
            gameParams.playerInfos.emplace_back(line);
        else if (line[0] == '0')
            gameParams.aiInfos.emplace_back(line);
    }
    fs.close();
}

menu_t MenuLoad::updateMenu()
{
    error = 0;
    updateElements();
    if (error == 1)
        return HOME;
    return NEWGAME;
}