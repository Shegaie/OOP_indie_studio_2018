/*
** EPITECH PROJECT, 2022
** bomberman
** File description:
** Created by lgregoire,
*/

#ifndef BOMBERMAN_SPEEDPOWERUP_HPP
#define BOMBERMAN_SPEEDPOWERUP_HPP

#include <vector>
#include "irrlicht/irrlicht.h"
#include "IPowerUp.hpp"

class Player;

class SpeedPowerUp : public IPowerUp
{
    public:
    SpeedPowerUp(irr::scene::ISceneManager *sceneManager, irr::video::IVideoDriver *driver, int _x, int _y);
    void alterAbilities(Player *player) override;
    bool isPlayerOn(irr::core::vector3df playerPos) override;
    void debugPosition() override;
    void destroy() override;
    vector2i getPosition() override;

    private:
    irr::scene::IMeshSceneNode *model;
    int x;
    int y;
};

#endif //BOMBERMAN_SPEEDPOWERUP_HPP
