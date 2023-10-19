/*
** EPITECH PROJECT, 2022
** bomberman
** File description:
** Created by lgregoire,
*/

#ifndef BOMBERMAN_RANGEPOWERUP_HPP
#define BOMBERMAN_RANGEPOWERUP_HPP

#include <vector>
#include "irrlicht/irrlicht.h"
#include "IPowerUp.hpp"

class Player;

class RangePowerUp : public IPowerUp
{
    public:
    RangePowerUp(irr::scene::ISceneManager *sceneManager, irr::video::IVideoDriver *driver, int _x, int _y);
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

#endif //BOMBERMAN_RANGEPOWERUP_HPP
