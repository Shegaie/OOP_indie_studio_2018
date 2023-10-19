/*
** EPITECH PROJECT, 2022
** bomberman
** File description:
** Created by Romain Floriani,
*/

#include <vector>
#include <string>
#include "Bomb/Bomb.hpp"

Bomb::Bomb(int posX, int posY, irr::scene::ISceneManager *sceneManager, irr::video::IVideoDriver *driver, int range)
{
    fireEffect = MagicCandle(sceneManager, driver->getTexture("assets/game/fire.bmp"), posX * 10, posY * 10);
    position.Y = posY;
    position.X = posX;
    rangeExplosion = range;
    bomb = sceneManager->addAnimatedMeshSceneNode(sceneManager->getMesh("assets/game/Bomb.md2"), nullptr, -1, irr::core::vector3df(posX * 10, posY * 10, 0), irr::core::vector3df(0, 180, 0), irr::core::vector3df(0.0125, 0.0125, 0.0125), true);
    bomb->setMaterialTexture(0, driver->getTexture("assets/game/bomb.png"));
    bomb->setMaterialFlag(irr::video::EMF_LIGHTING, true);
    fireEffect.start();
    Timer = std::chrono::high_resolution_clock::now();
    isDestroyed = false;
}

bool Bomb::verifyTimer()
{
    return (std::chrono::high_resolution_clock::now() - Timer).count() >= 2000000000;
}

int getBombWithPosition(const std::vector<Bomb> &Bombs, int posX, int posY)
{
    int i = 0;
    for (auto bomb : Bombs) {
        if (bomb.getPosition().Y == posY && bomb.getPosition().X == posX)
            return i;
        i++;
    }
    return -1;
}

int getBombWithPositions(const std::vector<Bomb> &Bombs, int posX, int posY)
{
    int i = 0;
    for (auto bomb : Bombs) {
        if (bomb.getPosition().Y == posY && bomb.getPosition().X == posX && !bomb.getDestroyed())
            return i;
        i++;
    }
    return -1;
}

std::vector<int> Bomb::explode(std::vector<Bomb> &Bombs, Map &maps, int sizeX, int sizeY, Player &player, irr::scene::ISceneManager *sceneManager, irr::video::IVideoDriver* driver, std::vector<Player> &Players)
{
    std::vector<int> explosionRange = {0, 0, 0, 0};
    std::vector<std::string> map = maps.getMapString();
    int pos = getBombWithPositions(Bombs, position.X, position.Y);
    int saveBomb = 0;

    if (pos == -1)
        return {0, 0, 0, 0};
    if (!Bombs[pos].isDestroyed) {
        Bombs[getBombWithPositions(Bombs, position.X, position.Y)].isDestroyed = true;
        bomb->remove();
        fireEffect.cancel();
    }
    map[position.Y][position.X] = ' ';
    maps.setModificationMapString(map);
    for (int i = 1; i < rangeExplosion + 1; i++) {
        if (position.Y + i >= sizeY) {
            explosionRange[0] = i - 1;
            break;
        }
        if (map[position.Y + i][position.X] == '#') {
            explosionRange[0] = i - 1;
            break;
        }
        if (map[position.Y + i][position.X] == '+') {
            explosionRange[0] = i;
            break;
        }
        if (map[position.Y + i][position.X] == 'B') {
            if ((saveBomb = getBombWithPositions(Bombs, position.X, position.Y + i)) >= 0)
                player.manageBombs(maps, sceneManager, driver, Bombs[saveBomb], player, Players);
        }
        if (i == rangeExplosion)
            explosionRange[0] = rangeExplosion;
    }
    for (int i = 1; i < rangeExplosion + 1; i++) {
        if (position.X + i >= sizeX) {
            explosionRange[1] = i - 1;
            break;
        }
        if (map[position.Y][position.X + i] == '#') {
            explosionRange[1] = i - 1;
            break;
        }
        if (map[position.Y][position.X + i] == '+') {
            explosionRange[1] = i;
            break;
        }
        if (map[position.Y][position.X + i] == 'B') {
            if ((saveBomb = getBombWithPositions(Bombs, position.X + i, position.Y)) >= 0)
                player.manageBombs(maps, sceneManager, driver, Bombs[saveBomb], player, Players);
        }
        if (i == rangeExplosion)
            explosionRange[1] = rangeExplosion;
    }
    for (int i = 1; i < rangeExplosion + 1; i++) {
        if (position.Y - i < 0) {
            explosionRange[2] = i - 1;
            break;
        }
        if (map[position.Y - i][position.X] == '#') {
            explosionRange[2] = i - 1;
            break;
        }
        if (map[position.Y - i][position.X] == '+') {
            explosionRange[2] = i;
            break;
        }
        if (map[position.Y - i][position.X] == 'B') {
            if ((saveBomb = getBombWithPositions(Bombs, position.X, position.Y - i)) >= 0)
                player.manageBombs(maps, sceneManager, driver, Bombs[saveBomb], player, Players);
        }
        if (i == rangeExplosion)
            explosionRange[2] = rangeExplosion;
    }
    for (int i = 1; i < rangeExplosion + 1; i++) {
        if (position.X - i < 0) {
            explosionRange[3] = i - 1;
            break;
        }
        if (map[position.Y][position.X - i] == '#') {
            explosionRange[3] = i - 1;
            break;
        }
        if (map[position.Y][position.X - i] == '+') {
            explosionRange[3] = i;
            break;
        }
        if (map[position.Y][position.X - i] == 'B') {
            if ((saveBomb = getBombWithPositions(Bombs, position.X - i, position.Y)) >= 0)
                player.manageBombs(maps, sceneManager, driver, Bombs[saveBomb], player, Players);
        }
        if (i == rangeExplosion)
            explosionRange[3] = rangeExplosion;
    }
    Bombs.erase(Bombs.begin() + getBombWithPosition(Bombs, position.X, position.Y));
    return explosionRange;
}

irr::core::vector3df Bomb::getPosition()
{
    return position;
}

bool Bomb::getDestroyed()
{
    return isDestroyed;
}

int Bomb::getRangeExplosion()
{
    return rangeExplosion;
}

void Bomb::remove_entities()
{
    bomb->remove();
    fireEffect.removeEntity();
}