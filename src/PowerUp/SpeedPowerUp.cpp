/*
** EPITECH PROJECT, 2022
** bomberman
** File description:
** Created by lgregoire,
*/

#include "SpeedPowerUp.hpp"
#include <iostream>
#include "Player/Player.hpp"

SpeedPowerUp::SpeedPowerUp(irr::scene::ISceneManager *sceneManager,
    irr::video::IVideoDriver *driver, int _x, int _y
) : x(_x * 10), y(_y * 10)
{
    model = sceneManager->addCubeSceneNode(
        8.0f, nullptr, -1, irr::core::vector3df(x, y, -2),
        irr::core::vector3df(0, 0, 0),
        irr::core::vector3df(1, 1, 0.1));
    model->setMaterialFlag(irr::video::EMF_LIGHTING, true);
    model->setMaterialTexture(0,
        driver->getTexture("assets/powerup/speed.png"));
}

void SpeedPowerUp::alterAbilities(Player *player)
{
    player->increaseSpeedFactor();
}

void SpeedPowerUp::debugPosition()
{
    std::cout << "x : " << x << " && y : " << y << std::endl;
    std::cout << std::endl;
}

bool SpeedPowerUp::isPlayerOn(irr::core::vector3df playerPos)
{
    return playerPos.X + 4 > x && playerPos.X + 4 < x + 10 && playerPos.Y + 4 > y && playerPos.Y + 4 < y + 10;
}

void SpeedPowerUp::destroy()
{
    model->remove();
}

vector2i SpeedPowerUp::getPosition()
{
    vector2i pos = {x, y};

    return pos;
}