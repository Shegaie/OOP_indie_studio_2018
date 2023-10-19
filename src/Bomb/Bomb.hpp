/*
** EPITECH PROJECT, 2022
** bomberman
** File description:
** Created by Romain Floriani,
*/

#ifndef BOMBERMAN_BOMB_HPP
#define BOMBERMAN_BOMB_HPP

#include <chrono>
#include "irrlicht/irrlicht.h"
#include "Map/Map.hpp"
#include "Player/Player.hpp"
#include "Effect/MagicCandle.hpp"

class Player;

class Bomb {
    private:
        irr::core::vector3df position;
        std::chrono::time_point<std::chrono::high_resolution_clock> Timer;
        irr::scene::IAnimatedMeshSceneNode *bomb;

        int rangeExplosion;
        bool isDestroyed;
        MagicCandle fireEffect;

    public:
        Bomb(int posX, int posY, irr::scene::ISceneManager *sceneManager, irr::video::IVideoDriver* driver, int rangeExplosion);
        bool verifyTimer();
        std::vector<int> explode(std::vector<Bomb> &Bombs, Map &maps, int sizeX, int sizeY, Player &player, irr::scene::ISceneManager *sceneManager, irr::video::IVideoDriver* driver, std::vector<Player> &Players);
        irr::core::vector3df getPosition();
        void remove_entities();
        bool getDestroyed();
        int getRangeExplosion();
};

#endif //BOMBERMAN_BOMB_HPP
