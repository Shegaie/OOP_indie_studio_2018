/*
** EPITECH PROJECT, 2022
** bomberman
** File description:
** Created by Pierre Chaudron
*/

#include "EventManager/EventManager.hpp"
#include "MenuNew.hpp"

MenuNew::MenuNew(irr::IrrlichtDevice *deviceArg, irr::video::IVideoDriver *driverArg, game_params_t &params)
: device(deviceArg), driver(driverArg), gameParams(params)
{
    soundManager.addSounds({
        {"select", {"assets/menu/sounds/select.ogg", 100}},
        {"click", {"assets/menu/sounds/click.ogg", 20}}
    });
    textures = {
        {"background", Sprite2D("assets/menu/textures/new/background.jpeg", driver, {0, 0}, {0, 0, 1280, 720})},
        {"j1", Sprite2D("assets/menu/textures/new/j1.png", driver, {251, 188}, {0, 0, 315, 344})},
        {"j2", Sprite2D("assets/menu/textures/new/j2.png", driver, {715, 188}, {0, 344, 315, 688})},
        {"skin_j1", Sprite2D("assets/menu/textures/new/skins.png", driver, {327, 269}, {0, 0, 165, 145}, true)},
        {"skin_j2", Sprite2D("assets/menu/textures/new/skins.png", driver, {787, 269}, {0, 0, 165, 145}, false)}
    };
    buttons = {
        {"arrow_back", Button("assets/menu/textures/arrow_back.png", driver, {35, 35}, {0, 0, 146, 70}, soundManager)},
        {"cross", Button("assets/menu/textures/new/cross.png", driver, {994, 191}, {0, 0, 33, 33}, soundManager, false)},
        {"arrow_j1_L", Button("assets/menu/textures/settings/arrow.png", driver, {271, 311}, {0, 0, 44, 64}, soundManager)},
        {"arrow_j1_R", Button("assets/menu/textures/settings/arrow2.png", driver, {506, 311}, {0, 0, 44, 64}, soundManager)},
        {"arrow_j2_L", Button("assets/menu/textures/settings/arrow.png", driver, {730, 311}, {0, 0, 44, 64}, soundManager, false)},
        {"arrow_j2_R", Button("assets/menu/textures/settings/arrow2.png", driver, {965, 311}, {0, 0, 44, 64}, soundManager, false)}
    };
    gameParams = {false, PINK, PINK};
}

void MenuNew::updateElements() {
    auto mousePos = device->getCursorControl()->getPosition();

    for (auto &button : buttons)
        button.second.updateHoverState(mousePos);
}

void MenuNew::changeMultiplayer(int level, bool state)
{
    textures.at("j2").setTextureRectLevel(level);
    textures.at("skin_j2").setDisplay(state);
    buttons.at("arrow_j2_L").setDisplay(state);
    buttons.at("arrow_j2_R").setDisplay(state);
    buttons.at("cross").setDisplay(state);
    gameParams.multiplayer = state;
}

void MenuNew::changeSkin(const mouse_event_t &mouseEvent, const std::string &button, const std::string &player,
    bool positive)
{
    if (buttons.at(button).isClicked(mouseEvent)) {
        textures.at(player).incrementTextureRect(true, positive);
        if (textures.at(player).getTextureRectLevel()
        == textures.at((player == "skin_j1") ? "skin_j2" : "skin_j1").getTextureRectLevel())
            textures.at(player).incrementTextureRect(true, positive);

        skin_t skins[] = {PINK, BLUE, RED, WHITE};
        if (player == "skin_j1")
            gameParams.skinPlayerOne = skins[textures.at(player).getTextureRectLevel()];
        else
            gameParams.skinPlayerTwo = skins[textures.at(player).getTextureRectLevel()];
    }
}

menu_t MenuNew::manageEvents() {
    EventManager *eventManager = dynamic_cast<EventManager *>(device->getEventReceiver());
    mouse_event_t mouseEvent = eventManager->getMouseEvent();

    if (eventManager->IsKeyDown(irr::KEY_RETURN))
        return NEWGAME;

    if (eventManager->IsKeyDown(irr::KEY_SPACE)) {
        changeMultiplayer(0, true);
        gameParams.skinPlayerTwo = (textures.at("skin_j1").getTextureRectLevel() == 0) ? BLUE : PINK;
        textures.at("skin_j2").resetTextureRect();
        if (gameParams.skinPlayerTwo == BLUE)
            textures.at("skin_j2").incrementTextureRect(true, true);
    }

    if (buttons.at("cross").isClicked(mouseEvent))
        changeMultiplayer(1, false);

    if (buttons.at("arrow_back").isClicked(mouseEvent) || eventManager->IsKeyDown(irr::KEY_ESCAPE))
        return HOME;

    changeSkin(mouseEvent, "arrow_j1_L", "skin_j1", false);
    changeSkin(mouseEvent, "arrow_j1_R", "skin_j1", true);
    changeSkin(mouseEvent, "arrow_j2_L", "skin_j2", false);
    changeSkin(mouseEvent, "arrow_j2_R", "skin_j2", true);
    return NEW;
}

void MenuNew::drawTextures() {
    textures.at("background").drawSprite();
    textures.at("j1").drawSprite();
    textures.at("j2").drawSprite();
    textures.at("skin_j1").drawSprite();
    textures.at("skin_j2").drawSprite();
    for (auto &button : buttons)
        button.second.drawSprite();
}

menu_t MenuNew::updateMenu() {
    updateElements();
    menu_t menu = manageEvents();
    drawTextures();
    return menu;
}
