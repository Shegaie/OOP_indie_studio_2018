/*
** EPITECH PROJECT, 2022
** bomberman
** File description:
** Created by lgregoire,
*/

#ifndef BOMBERMAN_BOMBPOWERUP_HPP
#define BOMBERMAN_BOMBPOWERUP_HPP

#include <vector>
#include "IPowerUp.hpp"
#include "irrlicht/irrlicht.h"

class Player;

class BombPowerUp : public IPowerUp
{
    public:
        BombPowerUp(irr::scene::ISceneManager *sceneManager, irr::video::IVideoDriver *driver, int _x, int _y);
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

#endif //BOMBERMAN_BOMBPOWERUP_HPP
