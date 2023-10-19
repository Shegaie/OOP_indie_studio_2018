/*
** EPITECH PROJECT, 2022
** Indie
** File description:
** Created by Julien Montagne
*/

#include <iostream>
#include <memory>
#include "BombermanException/BombermanException.hpp"
#include "Menu/MenuHome/MenuHome.hpp"
#include "Menu/MenuSettings/MenuSettings.hpp"
#include "Menu/MenuHowToPlay/MenuHowToPlay.hpp"
#include "Menu/MenuLoad/MenuLoad.hpp"
#include "Menu/MenuNew/MenuNew.hpp"
#include "Menu.hpp"
#include "SFML/Audio.hpp"

Menu::Menu(irr::IrrlichtDevice *deviceArg, irr::video::IVideoDriver *driverArg, game_params_t &params)
: device(deviceArg), driver(driverArg), gameParams(params)
{
    soundManager.addMusic("theme", "assets/menu/sounds/bomberman-theme-cover.ogg");
    textures = {
        {"cursor", Sprite2D("assets/menu/textures/cursor.png", driver, {0, 0}, {0, 0, 32, 32})}
    };

    menuCreator = {
        {HOME, [device = device, driver = driver] () { return std::make_unique<MenuHome>(device, driver); }},
        {SETTINGS, [device = device, driver = driver] () { return std::make_unique<MenuSettings>(device, driver); }},
        {HOWTOPLAY, [device = device, driver = driver] () { return std::make_unique<MenuHowToPlay>(device, driver); }},
        {LOAD, [device = device, driver = driver, &gameParams = gameParams] () { return std::make_unique<MenuLoad>(device, driver, gameParams); }},
        {NEW, [device = device, driver = driver, &gameParams = gameParams] ()
        { return std::make_unique<MenuNew>(device, driver, gameParams); }}
    };
    menu = HOME;
    menuPtr = menuCreator.at(menu)();
    gameParams.loaded = false;
}

Menu::~Menu() {}

scene_t Menu::runScene()
{
    irr::gui::IGUIInOutFader* fader = device->getGUIEnvironment()->addInOutFader();
    soundManager.playMusic("theme");
    dynamic_cast<EventManager *>(device->getEventReceiver())->getMouseEvent();
    fader->setColor(irr::video::SColor(0, 0, 0, 0));
    fader->fadeIn(300);
    while (device->run()) {
        driver->beginScene(true, true, {255, 255, 255, 255});
        menu_t temp = menuPtr->updateMenu();
        soundManager.updateVolume();
        textures.at("cursor").setPosition(device->getCursorControl()->getPosition());
        textures.at("cursor").drawSprite();
        device->getGUIEnvironment()->drawAll();
        driver->endScene();
        if (temp != menu) {
            if (temp == NEWGAME) {
                soundManager.stopMusic("theme");
                return GAME;
            }
            try {
                menuPtr = menuCreator.at(temp)();
            } catch (const BombermanException &exception) {
                throw BombermanException(exception);
            }
            menu = temp;
            fader->setColor(irr::video::SColor(0, 0, 0, 0));
            fader->fadeIn(300);
        }
    }
    return MENU;
}