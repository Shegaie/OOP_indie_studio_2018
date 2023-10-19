/*
** EPITECH PROJECT, 2022
** bomberman
** File description:
** Created by Pierre Chaudron
*/

#include "EventManager/EventManager.hpp"
#include "MenuSettings.hpp"

#define TOP 220

MenuSettings::MenuSettings(irr::IrrlichtDevice *deviceArg, irr::video::IVideoDriver *driverArg): device(deviceArg), driver(driverArg) {
    soundManager.addSounds({
        {"select", {"assets/menu/sounds/select.ogg", 100}},
        {"click", {"assets/menu/sounds/click.ogg", 20}}
    });
    textures = {
        {"background", Sprite2D("assets/menu/textures/settings/settings.jpeg", driver, {0, 0}, {0, 0, 1280, 720})},
        {"background", Sprite2D("assets/menu/textures/settings/settings.jpeg", driver, {0, 0}, {0, 0, 1280, 720})},
        {"master", Sprite2D("assets/menu/textures/settings/bar.png", driver, {400, 220}, {0, 0, 486, 65})},
        {"sounds", Sprite2D("assets/menu/textures/settings/bar.png", driver, {400, TOP + 150}, {0, 0, 486, 65})},
        {"music", Sprite2D("assets/menu/textures/settings/bar.png", driver, {400, TOP + 300}, {0, 0, 486, 65})}
    };
    buttons = {
        {"arrow_back", Button("assets/menu/textures/arrow_back.png", driver, {35, 35}, {0, 0, 146, 70}, soundManager)},
        {"arrow_master_L", Button("assets/menu/textures/settings/arrow.png", driver, {333, 222}, {0, 0, 44, 64}, soundManager)},
        {"arrow_sounds_L", Button("assets/menu/textures/settings/arrow.png", driver, {333, TOP + 150}, {0, 0, 44, 64}, soundManager)},
        {"arrow_music_L", Button("assets/menu/textures/settings/arrow.png", driver, {333, TOP + 300}, {0, 0, 44, 64}, soundManager)},
        {"arrow_master_R", Button("assets/menu/textures/settings/arrow2.png", driver, {905, 222}, {0, 0, 44, 64}, soundManager)},
        {"arrow_sounds_R", Button("assets/menu/textures/settings/arrow2.png", driver, {905, TOP + 150}, {0, 0, 44, 64}, soundManager)},
        {"arrow_music_R", Button("assets/menu/textures/settings/arrow2.png", driver, {905, TOP + 300}, {0, 0, 44, 64}, soundManager)}
    };

    textures.at("master").setTextureRectLevel((int)(5 * SoundManager::masterMultiplier));
    textures.at("sounds").setTextureRectLevel((int)(5 * SoundManager::soundMultiplier));
    textures.at("music").setTextureRectLevel((int)(5 * SoundManager::musicMultiplier));
}

void MenuSettings::updateElements() {
    auto mousePos = device->getCursorControl()->getPosition();

    for (auto &button : buttons)
        button.second.updateHoverState(mousePos);
}

void MenuSettings::checkVolumeChange(const mouse_event_t &mouseEvent, const std::string &buttonName,
const std::string &volumeName, float &volume, bool positive, bool updateSounds) {
    if (buttons.at(buttonName).isClicked(mouseEvent)) {
        if (positive && volume < 1) {
            textures.at(volumeName).incrementTextureRect(false);
        } else if (!positive && volume > 0) {
            textures.at(volumeName).incrementTextureRect(false, false);
        } else
            return;
        volume = textures.at(volumeName).getTextureRectLevel() / 5.0f;
        if (updateSounds)
            soundManager.updateVolume();
    }
}

menu_t MenuSettings::manageEvents() {
    EventManager *eventManager = dynamic_cast<EventManager *>(device->getEventReceiver());
    mouse_event_t mouseEvent = eventManager->getMouseEvent();

    if (buttons.at("arrow_back").isClicked(mouseEvent) || eventManager->IsKeyDown(irr::KEY_ESCAPE))
        return HOME;

    checkVolumeChange(mouseEvent, "arrow_master_L", "master", SoundManager::masterMultiplier, false);
    checkVolumeChange(mouseEvent, "arrow_master_R", "master", SoundManager::masterMultiplier, true);
    checkVolumeChange(mouseEvent, "arrow_sounds_L", "sounds", SoundManager::soundMultiplier, false);
    checkVolumeChange(mouseEvent, "arrow_sounds_R", "sounds", SoundManager::soundMultiplier, true);
    checkVolumeChange(mouseEvent, "arrow_music_L", "music", SoundManager::musicMultiplier, false, false);
    checkVolumeChange(mouseEvent, "arrow_music_R", "music", SoundManager::musicMultiplier, true, false);

    return SETTINGS;
}

void MenuSettings::drawTextures() {
    textures.at("background").drawSprite();
    textures.at("master").drawSprite();
    textures.at("sounds").drawSprite();
    textures.at("music").drawSprite();

    for (auto &button : buttons)
        button.second.drawSprite();
}

menu_t MenuSettings::updateMenu() {
    updateElements();
    menu_t menu = manageEvents();
    drawTextures();
    return menu;
}