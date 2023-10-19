/*
** EPITECH PROJECT, 2022
** bomberman
** File description:
** Created by Pierre Chaudron
*/

#include "EventManager/EventManager.hpp"
#include "MenuHome.hpp"

MenuHome::MenuHome(irr::IrrlichtDevice *deviceArg,
    irr::video::IVideoDriver *driverArg
) : device(deviceArg), driver(driverArg)
{
    int RIGHT_B = 500;
    int TOP_B = 80;

    soundManager.addSounds({
        {"select", {"assets/menu/sounds/select.ogg", 100}},
        {"click", {"assets/menu/sounds/click.ogg", 20}}
    });
    textures = {
        {"background", Sprite2D("assets/menu/textures/home/background.jpeg", driver, {0, 0}, {0, 0, 1280, 720})},
        {"mrpepe", Sprite2D("assets/menu/textures/home/mrpepe.png", driver, {180, 20}, {0, 0, 295, 671})}
    };
    buttons = {
        {"exit", Button("assets/menu/textures/home/exit.png", driver, {RIGHT_B, TOP_B + 300}, {0, 0, 860, 83}, soundManager)},
        {"load", Button("assets/menu/textures/home/load.png", driver, {RIGHT_B, TOP_B + 100}, {0, 0, 860, 83}, soundManager)},
        {"new_game", Button("assets/menu/textures/home/new_game.png", driver, {RIGHT_B, TOP_B}, {0, 0, 860, 83}, soundManager)},
        {"settings", Button("assets/menu/textures/home/settings.png", driver, {RIGHT_B, TOP_B + 200}, {0, 0, 860, 83}, soundManager)},
        {"htp", Button("assets/menu/textures/home/htp.png", driver, {15, 15}, {0, 0, 120, 116}, soundManager)}
    };

    pepeAnimation.setTask([&textures = textures] () { textures.at("mrpepe").incrementTextureRect(); }, 400);
}

void MenuHome::updateElements()
{
    auto mousePos = device->getCursorControl()->getPosition();

    for (auto &button : buttons)
        button.second.updateHoverState(mousePos);

    pepeAnimation.executeTask();
}

menu_t MenuHome::manageEvents()
{
    EventManager *eventManager = dynamic_cast<EventManager *>(device->getEventReceiver());
    mouse_event_t mouse = eventManager->getMouseEvent();
    std::unordered_map<std::string, menu_t> hoverables = {
        {"load", LOAD},
        {"new_game", NEW},
        {"settings", SETTINGS},
        {"htp", HOWTOPLAY}
    };

    if (eventManager->IsKeyDown(irr::KEY_ESCAPE))
        device->closeDevice();
    for (auto &button: buttons) {
        if (button.second.isClicked(mouse)) {
            if (button.first == "exit")
                device->closeDevice();
            else
                return hoverables.at(button.first);
        }
    }
    return HOME;
}

void MenuHome::drawTextures()
{
    textures.at("background").drawSprite();
    textures.at("mrpepe").drawSprite();

    for (auto &button : buttons)
        button.second.drawSprite();
}

menu_t MenuHome::updateMenu()
{
    updateElements();
    menu_t menu = manageEvents();
    drawTextures();
    return menu;
}