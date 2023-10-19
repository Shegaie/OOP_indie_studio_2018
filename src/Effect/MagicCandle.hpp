/*
** EPITECH PROJECT, 2022
** bomberman
** File description:
** Created by lgregoire,
*/
#ifndef BOMBERMAN_MAGICCANDLE_HPP
#define BOMBERMAN_MAGICCANDLE_HPP

#include <chrono>
#include <vector>
#include "IParticleSystemSceneNode.h"
#include "ISceneManager.h"

class MagicCandle {
    public:
    MagicCandle(irr::scene::ISceneManager *sceneManager, irr::video::ITexture *texture, int x, int y);
    MagicCandle();
    ~MagicCandle() = default;

    void removeEntity();
    void start();
    void cancel();
    protected:
    private:
    irr::scene::IParticleSystemSceneNode *ParticleSystem;
    irr::scene::IParticleEmitter *Emitter;
    irr::scene::IParticleAffector *affector;
};

#endif //BOMBERMAN_MAGICCANDLE_HPP
