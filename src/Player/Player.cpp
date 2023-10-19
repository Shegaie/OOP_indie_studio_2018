/*
** EPITECH PROJECT, 2022
** bomberman
** File description:
** Created by Romain Floriani,
*/

#include <iostream>
#include "Player.hpp"

Player::Player(int posX, int posY, irr::scene::ISceneManager *sceneManager, irr::video::IVideoDriver *driver, int color)
{
    position.X = posX * 10;
    position.Y = posY * 10;
    isActive = true;
    bombNumber = 1;
    speedFactor = 1;
    explosionRange = 1;
    wallPass = false;
    player = sceneManager->addAnimatedMeshSceneNode(sceneManager->getMesh("assets/game/Bomberman.MD3"), nullptr, -1, irr::core::vector3df(position.X, position.Y, 2), irr::core::vector3df(-90 , 0, 0), irr::core::vector3df(8, 8, 8), true);
    player->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    std::vector<std::string> colors = {"Pink.png", "Blue.png", "Red.png", "White.png"};
    player->setMaterialTexture(0, driver->getTexture(("assets/game/" + colors[color]).c_str()));
    player->setMD2Animation(irr::scene::EMAT_STAND);
    playerColor = color;
}

irr::core::vector3df Player::getPosition()
{
    return position;
}

bool verifyPosition(irr::core::vector3df &nodePosition, int dir, const std::vector<irr::scene::IMeshSceneNode *> &Cubes)
{
    for (auto const &Cube : Cubes) {
        if (dir == 0 && nodePosition.Y + 8 >= Cube->getPosition().Y && nodePosition.Y + 8 <= Cube->getPosition().Y + 8 && ((nodePosition.X >= Cube->getPosition().X && nodePosition.X <= Cube->getPosition().X + 8) || (nodePosition.X + 6 >= Cube->getPosition().X && nodePosition.X + 6 <= Cube->getPosition().X + 8)))
            return false;
        else if (dir == 1 && nodePosition.X + 8 >= Cube->getPosition().X  && nodePosition.X + 8 <= Cube->getPosition().X + 8 && ((nodePosition.Y >= Cube->getPosition().Y && nodePosition.Y <= Cube->getPosition().Y + 8) || (nodePosition.Y + 6 >= Cube->getPosition().Y && nodePosition.Y + 6 <= Cube->getPosition().Y + 8)))
            return false;
        else if (dir == 2 && nodePosition.Y - 1 <= Cube->getPosition().Y + 8 && nodePosition.Y - 1 >= Cube->getPosition().Y && ((nodePosition.X >= Cube->getPosition().X && nodePosition.X <= Cube->getPosition().X + 8) || (nodePosition.X + 6 >= Cube->getPosition().X && nodePosition.X + 6 <= Cube->getPosition().X + 8)))
            return false;
        else if (dir == 3 && nodePosition.X - 1 <= Cube->getPosition().X + 8 && nodePosition.X - 1 >= Cube->getPosition().X && ((nodePosition.Y >= Cube->getPosition().Y && nodePosition.Y <= Cube->getPosition().Y + 8) || (nodePosition.Y + 6 >= Cube->getPosition().Y && nodePosition.Y + 6 <= Cube->getPosition().Y + 8)))
            return false;
    }
    return true;
}

bool verifyBombPosition(irr::core::vector3df &nodePosition, int dir, std::vector<Player> &players, std::vector<std::vector<Bomb>> &ais)
{
    int posX = (nodePosition.X + 5);
    int posY = (nodePosition.Y + 5);

    for (auto &player : players) {
        std::vector<Bomb> Bombs;
        Bombs = player.getBombs();
        for (auto &bomb : Bombs) {
            int posXBomb = bomb.getPosition().X * 10;
            int posYBomb = bomb.getPosition().Y * 10;
            if (posY + 2 < posYBomb) {
                if (dir == 0 && posY + 3 >= posYBomb && posX / 10 == posXBomb / 10)
                    return false;
            }
            if (posX + 2 < posXBomb) {
                if (dir == 1 && posX + 3 >= posXBomb && posY / 10 == posYBomb / 10)
                    return false;
            }
            if (posY - 2 > posYBomb + 10) {
                if (dir == 2 && posY - 3 <= posYBomb + 10 && posX / 10 == posXBomb / 10)
                    return false;
            }
            if (posX - 2 > posXBomb + 10) {
                if (dir == 3 && posX - 3 <= posXBomb + 10 && posY / 10 == posYBomb / 10)
                    return false;
            }
        }
    }
    for (auto &ai : ais) {
        for (auto &bomb : ai) {
            int posXBomb = bomb.getPosition().X * 10;
            int posYBomb = bomb.getPosition().Y * 10;
            if (posY + 2 < posYBomb) {
                if (dir == 0 && posY + 3 >= posYBomb && posX / 10 == posXBomb / 10)
                    return false;
            }
            if (posX + 2 < posXBomb) {
                if (dir == 1 && posX + 3 >= posXBomb && posY / 10 == posYBomb / 10)
                    return false;
            }
            if (posY - 2 > posYBomb + 10) {
                if (dir == 2 && posY - 3 <= posYBomb + 10 && posX / 10 == posXBomb / 10)
                    return false;
            }
            if (posX - 2 > posXBomb + 10) {
                if (dir == 3 && posX - 3 <= posXBomb + 10 && posY / 10 == posYBomb / 10)
                    return false;
            }
        }
    }
    return true;
}

bool Player::movePlayer(int direction, const std::vector<irr::scene::IMeshSceneNode *> &Cubes, const std::vector<irr::scene::IMeshSceneNode *> &Blocks, std::vector<Player> &Players, std::vector<std::vector<Bomb>> &Ai)
{
    int i = 0;

    if (direction == 0)
        player->setRotation(irr::core::vector3df(-90, 0, 180));
    if (direction == 1)
        player->setRotation(irr::core::vector3df(-90, 0, 90));
    if (direction == 2)
        player->setRotation(irr::core::vector3df(-90, 0, 0));
    if (direction == 3)
        player->setRotation(irr::core::vector3df(-90, 0, -90));
    if (direction == 0 && verifyPosition(position, direction, Cubes) && verifyBombPosition(position, direction, Players, Ai)) {
        if (verifyPosition(position, direction, Blocks) || wallPass)
            position.Y += 0.6 * speedFactor;
    } else if (direction == 2 && verifyPosition(position, direction, Cubes) && verifyBombPosition(position, direction, Players, Ai)) {
        if (verifyPosition(position, direction, Blocks) || wallPass)
            position.Y -= 0.6 * speedFactor;
    }
    if (direction == 1 && verifyPosition(position, direction, Cubes) && verifyBombPosition(position, direction, Players, Ai)) {
        if (verifyPosition(position, direction, Blocks) || wallPass)
            position.X += 0.6 * speedFactor;
    }
    else if (direction == 3 && verifyPosition(position, direction, Cubes) && verifyBombPosition(position, direction, Players, Ai)) {
            if (verifyPosition(position, direction, Blocks) || wallPass)
                position.X -= 0.6 * speedFactor;
        }
    player->setPosition(position);
    if (i > 0)
        return (true);
    return (false);
}

void Player::dropBomb(irr::scene::ISceneManager *sceneManager, irr::video::IVideoDriver *driver, Map &maps)
{
    std::vector<std::string> map = maps.getMapString();
    int posY = (position.Y + 5) / 10;
    int posX = (position.X + 5) / 10;

    if (Bombs.size() < bombNumber) {
        if (map[posY][posX] != 'B' && map[posY][posX] != '+') {
            map[posY][posX] = 'B';
            maps.setModificationMapString(map);
            Bomb bomb(posX, posY, sceneManager, driver, explosionRange);
            Bombs.emplace_back(bomb);
            manageRange(maps, posY, posX);
        }
    }
}

void Player::manageRange (Map &map, int posY, int posX) {
    std::vector<std::string> mapString = map.getMapString();

    mapString[posY][posX] = 'B';
    for (int i = 1; i <= explosionRange && mapString[posY + i][posX] != '+' && mapString[posY + i][posX] != '#'; i++)
        if (mapString[posY + i][posX] != 'B')
            mapString[posY + i][posX] = 'o';
    for (int i = 1; i <= explosionRange && mapString[posY][posX + i] != '+' && mapString[posY][posX + i] != '#'; i++)
        if (mapString[posY][posX + i] != 'B')
            mapString[posY][posX + i] = 'o';
    for (int i = 1; i <= explosionRange && mapString[posY - i][posX] != '+' && mapString[posY - i][posX] != '#'; i++)
        if (mapString[posY - i][posX] != 'B')
            mapString[posY - i][posX] = 'o';
    for (int i = 1; i <= explosionRange && mapString[posY][posX - i] != '+' && mapString[posY][posX - i] != '#'; i++)
        if (mapString[posY][posX - i] != 'B')
            mapString[posY][posX - i] = 'o';
    map.setMapString(mapString);
    int i = 0;
    for (auto &it : map.getMapString()) {
        i = 0;
        while (it[i]) {
            i++;
        }
    }
}


std::vector<Bomb> Player::getBombs()
{
    return Bombs;
}

bool Player::bombIsEmpty()
{
    return Bombs.empty();
}

int getExplosionWithPosition(std::vector<Explosion> explosions, int posX, int posY)
{
    int i = 0;
    for (auto explo : explosions) {
        if (explo.getPosition().Y == posY && explo.getPosition().X == posX)
            return i;
        i++;
    }
    return -1;
}

void Player::manageBomb(Map &map, irr::scene::ISceneManager *sceneManager, irr::video::IVideoDriver *driver, Player &player, std::vector<Player> &Players)
{
    for (auto &bomb : Bombs) {
        irr::core::vector3df posBomb;
        std::vector<int> rangeExplosion;
        if (bomb.verifyTimer()) {
            posBomb = bomb.getPosition();
            rangeExplosion = bomb.explode(Bombs, map, 20, 10, player, sceneManager, driver, Players);
            map.manageExplosion(rangeExplosion, posBomb, sceneManager, driver);
            Explosion tmp = Explosion(sceneManager, driver->getTexture("assets/game/fire.bmp"), static_cast<int>(posBomb.X * 10), static_cast<int>(posBomb.Y * 10), rangeExplosion);
            tmp.start();
            explosion.emplace_back(tmp);
            manageDeath(rangeExplosion, posBomb, Players);
        }
    }
}

void Player::setAnimation(int i, bool check)
{
    if (i == 1)
        player->setMD2Animation(irr::scene::EMAT_RUN);
    else if (!check)
        player->setMD2Animation(irr::scene::EMAT_STAND);
}

void Player::manageBombs(Map &map, irr::scene::ISceneManager *sceneManager, irr::video::IVideoDriver *driver, Bomb bomb, Player &player, std::vector<Player> &Players)
{
    irr::core::vector3df posBomb;
    std::vector<int> rangeExplosion;
    posBomb = bomb.getPosition();
    rangeExplosion = bomb.explode(Bombs, map, 20, 10, player, sceneManager, driver, Players);
    map.manageExplosion(rangeExplosion, posBomb, sceneManager, driver);
    Explosion tmp = Explosion(sceneManager, driver->getTexture("assets/game/fire.bmp"), static_cast<int>(posBomb.X * 10), static_cast<int>(posBomb.Y * 10), rangeExplosion);
    tmp.start();
    explosion.emplace_back(tmp);
    manageDeath(rangeExplosion, posBomb, Players);
}

void Player::manageExplosion()
{
    for (auto &explo : explosion) {
        if (explo.manageExplosion()) {
            if (explo.getDestroyed())
                explosion.erase(explosion.begin() + getExplosionWithPosition(explosion, explo.getPosition().X, explo.getPosition().Y));
        }
    }
}

bool Player::explosionIsEmpty()
{
    return explosion.empty();
}

void Player::increaseBombNumber()
{
    bombNumber++;
}

void Player::increaseSpeedFactor()
{
    speedFactor += 0.1;
}

void Player::increaseExplosionRange()
{
    explosionRange++;
}

void Player::setWallPass(bool _wallPass)
{
    wallPass = _wallPass;
}

void Player::manageDeath(const std::vector<int> &rangeExplosion, const irr::core::vector3df &positionBomb, std::vector<Player> &Players)
{
    for (int i = 0; i < rangeExplosion[0] + 1; i++) {
        for (auto &playerLoop : Players) {
            if (playerLoop.getActivity() &&
                playerLoop.getColor() != getColor()) {
                int posX = (5 + playerLoop.getPosition().X) / 10;
                int posY = (playerLoop.getPosition().Y + 5) / 10;
                std::vector<int> positionPlayer = {posY, posX};
                if (positionBomb.Y + i == positionPlayer[0] && positionBomb.X == positionPlayer[1] && playerLoop.getActivity()) {
                    playerLoop.removePlayer();
                    playerLoop.setActivity();
                }
            }
        }
        if (isActive) {
            int posX = (5 + getPosition().X) / 10;
            int posY = (getPosition().Y + 5) / 10;
            std::vector<int> positionPlayer = {posY, posX};
            if (positionBomb.Y + i == positionPlayer[0] && positionBomb.X == positionPlayer[1] && isActive) {
                removePlayer();
                setActivity();
            }
        }
    }
    for (int i = 0; i < rangeExplosion[1] + 1; i++) {
        for (auto &playerLoop : Players) {
            if (playerLoop.getActivity() && playerLoop.getColor() != getColor()) {
                int posX = (5 + playerLoop.getPosition().X) / 10;
                int posY = (playerLoop.getPosition().Y + 5) / 10;
                std::vector<int> positionPlayer = {posY, posX};
                if (positionBomb.Y == positionPlayer[0] && positionBomb.X + i == positionPlayer[1] && playerLoop.getActivity()) {
                    playerLoop.removePlayer();
                    playerLoop.setActivity();
                }
            }
        }
        if (isActive) {
            int posX = (5 + getPosition().X) / 10;
            int posY = (getPosition().Y + 5) / 10;
            std::vector<int> positionPlayer = {posY, posX};
            if (positionBomb.Y == positionPlayer[0] && positionBomb.X + i == positionPlayer[1] && isActive) {
                removePlayer();
                setActivity();
            }
        }
    }
    for (int i = 0; i < rangeExplosion[2] + 1; i++) {
        for (auto &playerLoop : Players) {
            if (playerLoop.getActivity() && playerLoop.getColor() != getColor()) {
                int posX = (5 + playerLoop.getPosition().X) / 10;
                int posY = (playerLoop.getPosition().Y + 5) / 10;
                std::vector<int> positionPlayer = {posY, posX};
                if (positionBomb.Y - i == positionPlayer[0] && positionBomb.X == positionPlayer[1] && playerLoop.getActivity()) {
                    playerLoop.removePlayer();
                    playerLoop.setActivity();
                }
            }
        }
        if (isActive) {
            int posX = (5 + getPosition().X) / 10;
            int posY = (getPosition().Y + 5) / 10;
            std::vector<int> positionPlayer = {posY, posX};
            if (positionBomb.Y - i == positionPlayer[0] && positionBomb.X == positionPlayer[1] && isActive) {
                removePlayer();
                setActivity();
            }
        }
    }
    for (int i = 0; i < rangeExplosion[3] + 1; i++) {
        for (auto &playerLoop : Players) {
            if (playerLoop.getActivity() &&
                playerLoop.getColor() != getColor()) {
                int posX = (5 + playerLoop.getPosition().X) / 10;
                int posY = (playerLoop.getPosition().Y + 5) / 10;
                std::vector<int> positionPlayer = {posY, posX};
                if (positionBomb.Y == positionPlayer[0] && positionBomb.X - i == positionPlayer[1] && playerLoop.getActivity()) {
                    playerLoop.removePlayer();
                    playerLoop.setActivity();
                }
            }
        }
        if (isActive) {
            int posX = (5 + getPosition().X) / 10;
            int posY = (getPosition().Y + 5) / 10;
            std::vector<int> positionPlayer = {posY, posX};
            if (positionBomb.Y == positionPlayer[0] && positionBomb.X - i == positionPlayer[1] && isActive) {
                removePlayer();
                setActivity();
            }
        }
    }
}

bool Player::getActivity()
{
    return isActive;
}

int Player::getBombNumber () const {
    return bombNumber;
}

void Player::setBombNumber (int bombNumber) {
    Player::bombNumber = bombNumber;
}

double Player::getSpeedFactor () const {
    return speedFactor;
}

void Player::setSpeedFactor (double speedFactor) {
    Player::speedFactor = speedFactor;
}

int Player::getExplosionRange () const {
    return explosionRange;
}

void Player::setExplosionRange (int explosionRange) {
    Player::explosionRange = explosionRange;
}

bool Player::getWallPass () const {
    return wallPass;
}

void Player::removePlayer()
{
    player->remove();
}

int Player::getColor()
{
    return playerColor;
}

void Player::setActivity()
{
    isActive = false;
}
