/*
** EPITECH PROJECT, 2022
** bomberman
** File description:
** Created by Pierre Chaudron
*/

#include "EventManager/EventManager.hpp"
#include "MenuHowToPlay.hpp"

MenuHowToPlay::MenuHowToPlay(irr::IrrlichtDevice *deviceArg, irr::video::IVideoDriver *driverArg) : device(deviceArg), driver(driverArg)
{
    soundManager.addSounds({
        {"select", {"assets/menu/sounds/select.ogg", 100}},
        {"click", {"assets/menu/sounds/click.ogg", 20}}
    });
    textures = {
        {"background", Sprite2D("assets/menu/textures/htp/htp.jpeg", driver, {0, 0}, {0, 0, 1280, 720})}
    };
    buttons = {
        {"arrow_back", Button("assets/menu/textures/arrow_back.png", driver, {35, 35}, {0, 0, 146, 70}, soundManager)}
    };
}

MenuHowToPlay::~MenuHowToPlay() {}

void MenuHowToPlay::updateElements()
{
    auto mousePos = device->getCursorControl()->getPosition();

    buttons.at("arrow_back").updateHoverState(mousePos);
}

menu_t MenuHowToPlay::manageEvents()
{
    EventManager *eventManager = dynamic_cast<EventManager *>(device->getEventReceiver());
    mouse_event_t mouseEvent = eventManager->getMouseEvent();

    if (buttons.at("arrow_back").isClicked(mouseEvent) || eventManager->IsKeyDown(irr::KEY_ESCAPE))
        return HOME;
    return HOWTOPLAY;
}

void MenuHowToPlay::drawTextures()
{
    textures.at("background").drawSprite();
    buttons.at("arrow_back").drawSprite();
}

menu_t MenuHowToPlay::updateMenu()
{
    updateElements();
    menu_t menu = manageEvents();
    drawTextures();
    return menu;
}