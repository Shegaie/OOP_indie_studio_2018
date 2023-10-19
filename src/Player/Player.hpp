/*
** EPITECH PROJECT, 2022
** bomberman
** File description:
** Created by Romain Floriani,
*/

#ifndef BOMBERMAN_PLAYER_HPP
#define BOMBERMAN_PLAYER_HPP

#include <vector>
#include <string>
#include "Map/Map.hpp"
#include "Bomb/Bomb.hpp"
#include "Effect/Explosion.hpp"

class Bomb;

class Player {
    private:

    protected:
        irr::scene::IAnimatedMeshSceneNode *player;
        irr::core::vector3df position;
        std::vector<Bomb> Bombs;
        bool isActive;
        int bombNumber;
        double speedFactor;
        int explosionRange;
        bool wallPass;
        std::vector<Explosion> explosion;
        int playerColor;

    public:
        Player(int posX, int posY, irr::scene::ISceneManager *sceneManager, irr::video::IVideoDriver *driver, int color);
        irr::core::vector3df getPosition();
        bool movePlayer(int direction, const std::vector<irr::scene::IMeshSceneNode *> &Cubes, const std::vector<irr::scene::IMeshSceneNode *> &Blocks, std::vector<Player> &Players, std::vector<std::vector<Bomb>> &Ai);
        void dropBomb(irr::scene::ISceneManager *sceneManager, irr::video::IVideoDriver *driver, Map &map);
        std::vector<Bomb> getBombs();
        bool bombIsEmpty();
        void manageBomb(Map &map, irr::scene::ISceneManager *sceneManager, irr::video::IVideoDriver *driver, Player &player, std::vector<Player> &Players);
        void manageBombs(Map &map, irr::scene::ISceneManager *sceneManager, irr::video::IVideoDriver *driver, Bomb bomb, Player &player, std::vector<Player> &Players);
        void setAnimation(int i, bool check);
        void manageExplosion();
        bool explosionIsEmpty();
        void manageRange (Map &map, int posY, int posX);
        void manageDeath(const std::vector<int> &rangeExplosion, const irr::core::vector3df &position, std::vector<Player> &Players);
        bool getActivity();
        void removePlayer();
        int getBombNumber () const;
        void setBombNumber (int bombNumber);
        double getSpeedFactor () const;
        void setSpeedFactor (double speedFactor);
        int getExplosionRange () const;
        void setExplosionRange (int explosionRange);
        bool getWallPass () const;
        int getColor();
        void setActivity();

        void increaseBombNumber();
        void increaseSpeedFactor();
        void increaseExplosionRange();
        void setWallPass(bool _wallPass);
};

#endif //BOMBERMAN_PLAYER_HPP
