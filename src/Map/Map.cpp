/*
** EPITECH PROJECT, 2022
** OOP_indie_studio_2018
** File description:
** Created by Romain Floriani
*/

#include <iostream>
#include <ctime>
#include <fstream>
#include <iostream>
#include "Player/Player.hpp"
#include "Map.hpp"
#include "PowerUp/BombPowerUp.hpp"
#include "PowerUp/SpeedPowerUp.hpp"
#include "PowerUp/RangePowerUp.hpp"
#include "PowerUp/WallPassPowerUp.hpp"

bool mapCorner(int x, int y, std::vector<std::string> &map)
{
    if (y == 1 && x == 1) {
        map[y] += ' ';
        return true;
    }
    if (y == 1 && x == 2) {
        map[y] += ' ';
        return true;
    }
    if (y == 2 && x == 1) {
        map[y] += ' ';
        return true;
    }
    if (y == 2 && x == 2) {
        map[y] += '#';
        return true;
    }
    if (y == 3 && x == 1) {
        map[y] += '+';
        return true;
    }
    if (y == 1 && x == 3) {
        map[y] += '+';
        return true;
    }
    return false;
}

std::vector<std::string> generateThirdPart(int sizeX, int sizeY,
    std::vector<std::string> &secondPart
)
{
    std::vector<std::string> map = secondPart;

    for (int y = 0; y < sizeY; y++) {
        std::string string;
        map.emplace_back(string);
    }
    int posY = sizeY * 2;
    for (int y = 0; y < sizeY; y++)
        map[posY - y] = map[y];
    return map;
}

std::vector<std::string> generateSecondPart(int sizeX, int sizeY,
    std::vector<std::string> &firstPart
)
{
    std::vector<std::string> map = firstPart;

    for (int y = 0; y < sizeY + 1; y++) {
        for (int x = sizeX - 1; x > -1; x--)
            map[y] += map[y][x];
    }
    return map;
}

std::vector<std::string> generateFirstPart(int sizeX, int sizeY)
{
    std::vector<std::string> map;
    bool column = false;

    std::srand(std::time(nullptr));
    for (int y = 0; y < sizeY + 1; y++) {
        std::string string;
        map.emplace_back(string);
    }
    for (int x = 0; x < sizeX + 1; x++)
        map[0] += '#';
    for (int y = 1; y < sizeY + 1; y++) {
        bool line = false;
        map[y] += '#';
        for (int x = 1; x < sizeX + 1; x++) {
            if (line && column)
                map[y] += '#';
            else if (!mapCorner(x, y, map)) {
                int randomValue = std::rand() / ((RAND_MAX + 1u) / 4);
                if (randomValue == 1)
                    map[y] += ' ';
                else
                    map[y] += '+';
            }
                line = !line;
        }
        column = !column;
    }
    return map;
}

bool Map::generateMapString(int sizeX, int sizeY)
{
    if (sizeX % 2 != 0 || sizeY % 2 != 0 || sizeX < 6 || sizeY < 6)
        return false;
    firstPart = generateFirstPart(sizeX / 2, sizeY / 2);
    secondPart = generateSecondPart(sizeX / 2, sizeY / 2, firstPart);
    mapString = generateThirdPart(sizeX, sizeY / 2, secondPart);
    return true;
}

std::vector<std::string> Map::getMapString()
{
    return mapString;
}

void Map::setModificationMapString(const std::vector<std::string> &modifiedMap)
{
    mapString = modifiedMap;
}

void Map::generateMap(const std::vector<std::string> &mapStrings, int sizeX,
    int sizeY, irr::scene::ISceneManager *sceneManager,
    irr::video::IVideoDriver *driver
)
{
    for (int y = 0; y < sizeY + 1; y++) {
        for (int x = 0; x < sizeX + 1; x++) {
            if (mapStrings[y][x] == '#') {
                irr::scene::IMeshSceneNode *cube = sceneManager->addCubeSceneNode(
                    10.0f, nullptr, -1,
                    irr::core::vector3df(x * 10, y * 10, 0.0f),
                    irr::core::vector3df(0, 0, 0),
                    irr::core::vector3df(1, 1, 0.75));
                cube->setMaterialFlag(irr::video::EMF_LIGHTING, true);
                cube->setMaterialTexture(0,
                    driver->getTexture("assets/game/brique.png"));
                Cubes.emplace_back(cube);
            }
            if (mapStrings[y][x] == '+') {
                irr::scene::IMeshSceneNode *block = sceneManager->addCubeSceneNode(
                    10.0f, nullptr, -1,
                    irr::core::vector3df(x * 10, y * 10, 0.0f),
                    irr::core::vector3df(0, 0, 0),
                    irr::core::vector3df(1, 1, 0.5));
                block->setMaterialFlag(irr::video::EMF_LIGHTING, true);
                block->setMaterialTexture(0,
                    driver->getTexture("assets/game/brick.png"));
                Blocks.emplace_back(block);
            }
            if (mapStrings[y][x] == ' ' || mapStrings[y][x] == 'B' || mapStrings[y][x] == 'o' || mapStrings[y][x] == '1' || mapStrings[y][x] == '2' || mapStrings[y][x] == '3' || mapStrings[y][x] == '4') {
                irr::scene::IMeshSceneNode *floor = sceneManager->addCubeSceneNode(
                    10.0f, nullptr, -1, irr::core::vector3df(x * 10, y * 10, 3),
                    irr::core::vector3df(0, 0, 0),
                    irr::core::vector3df(1, 1, 0.1));
                floor->setMaterialFlag(irr::video::EMF_LIGHTING, true);
                floor->setMaterialTexture(0,
                    driver->getTexture("assets/game/floor.jpeg"));
                Floors.emplace_back(floor);
            }
        }
    }
}

void Map::verifyResolution(int sizeX, int sizeY)
{
    for (int y = 1; y < sizeY - 1; y++) {
        for (int x = 1; x < sizeX - 1; x++) {
            int count = 0;
            if (mapString[y][x] == '#') {
                if (mapString[y + 1][x] == '#')
                    count++;
                if (mapString[y][x + 1] == '#')
                    count++;
                if (mapString[y - 1][x] == '#')
                    count++;
                if (mapString[y][x - 1] == '#')
                    count++;
            }
            if (count > 1)
                mapString[y][x] = ' ';
        }
    }
}

void Map::generateFloor(int posX, int posY,
    irr::scene::ISceneManager *sceneManager, irr::video::IVideoDriver *driver
)
{
    irr::scene::IMeshSceneNode *floor = sceneManager->addCubeSceneNode(10.0f,
        nullptr, -1, irr::core::vector3df(posX * 10, posY * 10, 3),
        irr::core::vector3df(0, 0, 0), irr::core::vector3df(1, 1, 0.1));
    floor->setMaterialTexture(0, driver->getTexture("assets/game/floor.jpeg"));
    floor->setMaterialFlag(irr::video::EMF_LIGHTING, true);
    Floors.emplace_back(floor);
}

std::vector<irr::scene::IMeshSceneNode *> Map::getCubes()
{
    return Cubes;
}

std::vector<irr::scene::IMeshSceneNode *> Map::getBlocks()
{
    return Blocks;
}

void Map::generateRandomPowerUp(irr::scene::ISceneManager *sceneManager,
    irr::video::IVideoDriver *driver, int y, int x
)
{
    int whichPowerUp = rand() % 100;
    IPowerUp *powerUp = nullptr;

    if (whichPowerUp >= 0 && whichPowerUp < 30) {
        powerUp = new BombPowerUp(sceneManager, driver, x, y);
        mapString[y][x] = '1';
    } else if (whichPowerUp >= 30 && whichPowerUp < 60) {
        powerUp = new SpeedPowerUp(sceneManager, driver, x, y);
        mapString[y][x] = '2';
    } else if (whichPowerUp >= 60 && whichPowerUp < 95) {
        powerUp = new RangePowerUp(sceneManager, driver, x, y);
        mapString[y][x] = '3';
    } else if (whichPowerUp >= 95  && whichPowerUp <= 100) {
        powerUp = new WallPassPowerUp(sceneManager, driver, x, y);
        mapString[y][x] = '4';
    }
    addPowerUp(powerUp);
}

void Map::manageExplosion(std::vector<int> rangeExplosion,
    irr::core::vector3df posBomb, irr::scene::ISceneManager *sceneManager,
    irr::video::IVideoDriver *driver
)
{
    int posX = posBomb.X;
    int posY = posBomb.Y;
    int putPowerUp = rand() % 2;

    if (mapString[posY + rangeExplosion[0]][posX] == '+') {
        int i = 0;
        for (auto &block : Blocks) {
            if (block->getPosition().Y == (posY + rangeExplosion[0]) * 10 &&
                block->getPosition().X == posX * 10) {
                block->remove();
                Blocks.erase(Blocks.begin() + i);
                generateFloor(posX, (posY + rangeExplosion[0]), sceneManager,
                    driver);
                mapString[posY + rangeExplosion[0]][posX] = (putPowerUp == 0 ?
                    ' ' : 'P');
                if (mapString[posY + rangeExplosion[0]][posX] == 'P')
                    generateRandomPowerUp(sceneManager, driver,
                        posY + rangeExplosion[0], posX);
            }
            i++;
        }
    }
    if (mapString[posY][posX + rangeExplosion[1]] == '+') {
        int i = 0;
        for (auto &block : Blocks) {
            if (block->getPosition().Y == posY * 10 &&
                block->getPosition().X == (posX + rangeExplosion[1]) * 10) {
                block->remove();
                Blocks.erase(Blocks.begin() + i);
                generateFloor((posX + rangeExplosion[1]), posY, sceneManager,
                    driver);
                mapString[posY][posX + rangeExplosion[1]] = (putPowerUp == 0 ?
                    ' ' : 'P');
                if (mapString[posY][posX + rangeExplosion[1]] == 'P')
                    generateRandomPowerUp(sceneManager, driver, posY,
                        posX + rangeExplosion[1]);
            }
            i++;
        }
    }
    if (mapString[posY - rangeExplosion[2]][posX] == '+') {
        int i = 0;
        for (auto &block : Blocks) {
            if (block->getPosition().Y == (posY - rangeExplosion[2]) * 10 &&
                block->getPosition().X == posX * 10) {
                block->remove();
                Blocks.erase(Blocks.begin() + i);
                generateFloor(posX, (posY - rangeExplosion[2]), sceneManager,
                    driver);
                mapString[posY - rangeExplosion[2]][posX] = (putPowerUp == 0 ?
                    ' ' : 'P');
                if (mapString[posY - rangeExplosion[2]][posX] == 'P')
                    generateRandomPowerUp(sceneManager, driver,
                        posY - rangeExplosion[2], posX);
            }
            i++;
        }
    }
    if (mapString[posY][posX - rangeExplosion[3]] == '+') {
        int i = 0;
        for (auto &block : Blocks) {
            if (block->getPosition().Y == posY * 10 &&
                block->getPosition().X == (posX - rangeExplosion[3]) * 10) {
                block->remove();
                Blocks.erase(Blocks.begin() + i);
                generateFloor((posX - rangeExplosion[3]), posY, sceneManager,
                    driver);
                mapString[posY][posX - rangeExplosion[3]] = (putPowerUp == 0 ?
                    ' ' : 'P');
                if (mapString[posY][posX - rangeExplosion[3]] == 'P')
                    generateRandomPowerUp(sceneManager, driver, posY,
                        posX - rangeExplosion[3]);
            }
            i++;
        }
    }

    clearRange();
}

void Map::setMapString (std::vector<std::string> map) {
    mapString = map;
}

void Map::clearRange () {
    for(auto &it : mapString) {
        for(int x = 0; it[x]; x++) {
            if (it[x] == 'o' || it[x] == 'B')
                it[x] = ' ';
        }
    }
}

std::vector<IPowerUp *> Map::getLivingPowerUp()
{
    return livingPowerUp;
}

void Map::managePowerUp(Player *player)
{
    int i = 0;
    irr::core::vector3df playerPos = player->getPosition();

    for (auto powerUp : livingPowerUp) {
        if (powerUp->isPlayerOn(playerPos)) {
            powerUp->alterAbilities(player);
            powerUp->destroy();
            livingPowerUp.erase(livingPowerUp.begin() + i);
            mapString[powerUp->getPosition().y / 10][powerUp->getPosition().x / 10] = ' ';
        }
        i++;
    }
}

void Map::addPowerUp(IPowerUp *powerUp)
{
    livingPowerUp.push_back(powerUp);
}

void Map::removeEntities()
{
    for (auto &cube: Cubes)
        cube->remove();
    for (auto &block: Blocks)
        block->remove();
    for (auto &floor: Floors)
        floor->remove();
    for (auto &powerup: livingPowerUp)
        powerup->destroy();
}
