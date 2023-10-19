/*
** EPITECH PROJECT, 2022
** bomberman
** File description:
** Created by Pierre Chaudron
*/

#include "BombermanException/BombermanException.hpp"
#include "SoundManager/SoundManager.hpp"
#include "Menu/Menu.hpp"
#include "Game/Game.hpp"
#include "Sprite2D/Sprite2D.hpp"
#include "Bomberman.hpp"

void Bomberman::playPreroll() {
    irr::gui::IGUIInOutFader* fader = device->getGUIEnvironment()->addInOutFader();
    irr::ITimer *timer = device->getTimer();
    irr::u32 current = timer->getTime();
    SoundManager soundManager;
    Sprite2D preroll("assets/menu/textures/studio.png", driver, {0, 0}, {0, 0, 1280, 720});

    soundManager.addSounds({{"intro", {"assets/menu/sounds/intro.ogg", 50}}});
    fader->setColor(irr::video::SColor(0,0,0,0));
    fader->fadeIn(4000);
    soundManager.playSound("intro");
    while (timer->getTime() - current <= 4500 && device->run()) {
        driver->beginScene(true, true, {255, 255, 255, 255});
        preroll.drawSprite();
        device->getGUIEnvironment()->drawAll();
        driver->endScene();
    }
}

Bomberman::Bomberman() {
    device = irr::createDevice(irr::video::EDT_OPENGL,
    irr::core::dimension2d<irr::u32>(1280, 720), 32, false, false, false, &eventManager);
    device->getCursorControl()->setVisible(false);
    device->setResizable(false);

    driver = device->getVideoDriver();

    sceneCreator = {
        {MENU, [device = device, driver = driver, &gameParams = gameParams] ()
        { return std::make_unique<Menu>(device, driver, gameParams);}},
        {GAME, [device = device, driver = driver, &gameParams = gameParams] ()
        { return std::make_unique<Game>(device, driver, gameParams);}}
    };
    scene = MENU;
}

bool Bomberman::run() {
    try {
        scenePtr = sceneCreator.at(scene)();
        playPreroll();
        while (device->run()) {
            scene_t newScene = scenePtr->runScene();
            if (newScene != scene) {
                scenePtr = sceneCreator.at(newScene)();
                scene = newScene;
            }
        }
    } catch (const BombermanException &exception) {
        return false;
    }
    return true;
}

Bomberman::~Bomberman() {
    driver->removeAllTextures();
    device->drop();
}
