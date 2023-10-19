/*
** EPITECH PROJECT, 2022
** bomberman
** File description:
** Created by lgregoire,
*/

#include <thread>
#include <iostream>
#include "Explosion.hpp"
#include "Timer/Timer.hpp"

#define BLOCK_SIZE 10
#define PARTICLE_NB 400

Explosion::Explosion() = default;

Explosion::Explosion(irr::scene::ISceneManager *sceneManager,
    irr::video::ITexture *texture, int x, int y, std::vector<int> range
)
{
    xParticleSystem = sceneManager->addParticleSystemSceneNode(false);
    yParticleSystem = sceneManager->addParticleSystemSceneNode(false);
    xEmitter = xParticleSystem->createBoxEmitter(
        irr::core::aabbox3d<irr::f32>(x - 2,
            y + (BLOCK_SIZE * (range[0] + 1)) - 5, -5, x + BLOCK_SIZE - 7,
            y - (BLOCK_SIZE * (range[2] + 1)) + 5, 0),
        irr::core::vector3df(0.00f, 0.00f, 0.00f),
        static_cast<irr::u32>(PARTICLE_NB * (range[0] + range[2])),
        static_cast<irr::u32>(PARTICLE_NB * (range[0] + range[2])),
        irr::video::SColor(0, 0, 0, 0), irr::video::SColor(0, 255, 255, 255),
        600, 1200, 0, irr::core::dimension2df(8.0f, 8.0f),
        irr::core::dimension2df(14.0f, 14.0f));
    yEmitter = yParticleSystem->createBoxEmitter(
        irr::core::aabbox3d<irr::f32>(x - (BLOCK_SIZE * (range[3] + 1)) + 10, y,
            -5, x + (BLOCK_SIZE * (range[1] + 1)) - 5, y + BLOCK_SIZE - 10, 0),
        irr::core::vector3df(0.00f, 0.00f, 0.00f),
        static_cast<irr::u32>(PARTICLE_NB * (range[3] + range[1])),
        static_cast<irr::u32>(PARTICLE_NB * (range[3] + range[1])),
        irr::video::SColor(0, 0, 0, 0), irr::video::SColor(0, 255, 255, 255),
        600, 1200, 0, irr::core::dimension2df(8.0f, 8.0f),
        irr::core::dimension2df(14.0f, 14.0f));
    xParticleSystem->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    xParticleSystem->setMaterialFlag(irr::video::EMF_ZWRITE_ENABLE, false);
    xParticleSystem->setMaterialTexture(0, texture);
    xParticleSystem->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);
    yParticleSystem->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    yParticleSystem->setMaterialFlag(irr::video::EMF_ZWRITE_ENABLE, false);
    yParticleSystem->setMaterialTexture(0, texture);
    yParticleSystem->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);
    _isInit = true;
    position.X = x;
    position.Y = y;
    isDestroyed = false;
}

void Explosion::start()
{
    xParticleSystem->setEmitter(xEmitter);
    yParticleSystem->setEmitter(yEmitter);
    Timer = std::chrono::high_resolution_clock::now();
}

void Explosion::cancel()
{
    xParticleSystem->setEmitter(nullptr);
    yParticleSystem->setEmitter(nullptr);
}

std::chrono::time_point<std::chrono::high_resolution_clock> Explosion::getTimer()
{
    return Timer;
}

bool Explosion::isInit()
{
    return _isInit;
}

bool Explosion::manageExplosion()
{
    if (!isInit())
        start();
    if ((std::chrono::high_resolution_clock::now() - Timer).count() >=
        150000000) {
        cancel();
        if ((std::chrono::high_resolution_clock::now() - Timer).count() >=
            200000000)
            return true;
    }
    return false;
}

irr::core::vector3df Explosion::getPosition()
{
    return position;
}

bool Explosion::getDestroyed()
{
    return isDestroyed;
}

