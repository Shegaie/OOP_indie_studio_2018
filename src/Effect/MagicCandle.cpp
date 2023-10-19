/*
** EPITECH PROJECT, 2022
** bomberman
** File description:
** Created by lgregoire,
*/
#include "MagicCandle.hpp"

MagicCandle::MagicCandle() = default;

MagicCandle::MagicCandle(irr::scene::ISceneManager *sceneManager,
    irr::video::ITexture *texture, int x, int y
)
{
    ParticleSystem = sceneManager->addParticleSystemSceneNode(false);
    Emitter = ParticleSystem->createBoxEmitter(
        irr::core::aabbox3d<irr::f32>(x - 1, y, -7, x + 1, y + 1, -8),
        irr::core::vector3df(0.00f,0.00f,-0.03f),
        static_cast<irr::u32>(50), static_cast<irr::u32>(60),
        irr::video::SColor(0,0,0,0),
        irr::video::SColor(0,255,255,255),
        100, 150,
        30,
        irr::core::dimension2df(4.0f,4.0f),
        irr::core::dimension2df(4.0f,4.0f));
    ParticleSystem->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    ParticleSystem->setMaterialFlag(irr::video::EMF_ZWRITE_ENABLE, false);
    ParticleSystem->setMaterialTexture(0, texture);
    ParticleSystem->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);
}

void MagicCandle::start()
{
    ParticleSystem->setEmitter(Emitter);
}

void MagicCandle::cancel()
{
    ParticleSystem->setEmitter(nullptr);
}

void MagicCandle::removeEntity()
{
    ParticleSystem->remove();
}

