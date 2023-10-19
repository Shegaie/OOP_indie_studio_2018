/*
** EPITECH PROJECT, 2022
** bomberman
** File description:
** Created by lgregoire,
*/
#ifndef BOMBERMAN_EXPLOSION_HPP
#define BOMBERMAN_EXPLOSION_HPP

#include <chrono>
#include <vector>
#include "IParticleSystemSceneNode.h"
#include "ISceneManager.h"

class Explosion {
    public:
        Explosion(irr::scene::ISceneManager *sceneManager, irr::video::ITexture *texture, int x, int y, std::vector<int> range);
        Explosion();
    ~Explosion() = default;

        void start();
        void cancel();
        std::chrono::time_point<std::chrono::high_resolution_clock> getTimer();
        bool isInit();
        bool manageExplosion();
        irr::core::vector3df getPosition();
        bool getDestroyed();
    protected:
    private:
        irr::core::vector3df position;
        irr::scene::IParticleSystemSceneNode *xParticleSystem;
        irr::scene::IParticleSystemSceneNode *yParticleSystem;
        irr::scene::IParticleEmitter *xEmitter;
        irr::scene::IParticleEmitter *yEmitter;
        irr::scene::IParticleAffector *affector;
        std::chrono::time_point<std::chrono::high_resolution_clock> Timer;
        bool _isInit = false;
        bool isDestroyed;
};

#endif //BOMBERMAN_EXPLOSION_HPP
