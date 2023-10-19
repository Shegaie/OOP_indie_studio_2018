/*
** EPITECH PROJECT, 2022
** bomberman
** File description:
** Created by lgregoire,
*/

#ifndef BOMBERMAN_IPOWERUP_HPP
#define BOMBERMAN_IPOWERUP_HPP

#include "irrlicht/irrlicht.h"

class Player;

struct vector2i {
    int x;
    int y;
};

class IPowerUp {
    public:
        virtual ~IPowerUp() = default;;
        virtual void alterAbilities(Player *player) = 0;
        virtual void debugPosition() = 0;
        virtual bool isPlayerOn(irr::core::vector3df playerPos) = 0;
        virtual void destroy() = 0;
        virtual vector2i getPosition() = 0;
};

#endif //BOMBERMAN_IPOWERUP_HPP
