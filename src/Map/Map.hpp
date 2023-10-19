/*
** EPITECH PROJECT, 2022
** bomberman
** File description:
** Created by Romain Floriani,
*/

#ifndef BOMBERMAN_MAP_HPP
#define BOMBERMAN_MAP_HPP

#include <string>
#include <vector>
#include "irrlicht/irrlicht.h"
#include "PowerUp/BombPowerUp.hpp"

class Map {

    private:
        std::vector<std::string> mapString;
        std::vector<std::string> firstPart;
        std::vector<std::string> secondPart;
        std::vector<IPowerUp *> livingPowerUp;
        std::vector<irr::scene::IMeshSceneNode *> Cubes;
        std::vector<irr::scene::IMeshSceneNode *> Blocks;
        std::vector<irr::scene::IMeshSceneNode *> Floors;

    public:
        std::vector<IPowerUp *> getLivingPowerUp();
        void addPowerUp(IPowerUp *powerUp);
        void managePowerUp(Player *player);
        void generateRandomPowerUp(irr::scene::ISceneManager *sceneManager, irr::video::IVideoDriver *driver, int y, int x);
        bool generateMapString(int sizeX, int sizeY);
        std::vector<std::string> getMapString();
        void setModificationMapString(const std::vector<std::string> &modifiedMap);
        void generateMap(const std::vector<std::string> &mapString, int sizeX, int sizeY, irr::scene::ISceneManager *sceneManager, irr::video::IVideoDriver *driver);
        void verifyResolution(int sizeX, int sizeY);
        void generateFloor(int posX, int posY, irr::scene::ISceneManager *sceneManager, irr::video::IVideoDriver *driver);
        std::vector<irr::scene::IMeshSceneNode *> getCubes();
        std::vector<irr::scene::IMeshSceneNode *> getBlocks();
        void manageExplosion(std::vector<int> rangeExplosion, irr::core::vector3df posBomb, irr::scene::ISceneManager *sceneManager, irr::video::IVideoDriver *driver);
        void setMapString(std::vector<std::string> map);
        void clearRange();
        void removeEntities();
};

#endif //BOMBERMAN_MAP_HPP