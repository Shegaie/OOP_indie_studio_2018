/*
** EPITECH PROJECT, 2022
** bomberman
** File description:
** Created by Pierre Chaudron
*/

#include "Button.hpp"

Button::Button(const std::string &path, irr::video::IVideoDriver *Driver, const irr::core::vector2d<irr::s32> &pos,
               const irr::core::rect<irr::s32> &rect, SoundManager &soundManager, bool toDisplay)
               : Sprite2D(path, Driver, pos, rect, toDisplay), sounds(soundManager) {}

Button::~Button() {}

bool Button::isClicked(const mouse_event_t &mouseEvent) {
    if (isHover(mouseEvent.position.X, mouseEvent.position.Y) && mouseEvent.leftButtonDown) {
        setTextureRectLevel(2);
        sounds.playSound("click");
        return true;
    }
    return false;
}

void Button::updateHoverState(const irr::core::position2d<irr::s32> &mousePos) {
    if (isHover(mousePos.X, mousePos.Y)) {
        if (getTextureRectLevel() != 1) {
            setTextureRectLevel(1);
            sounds.playSound("select");
        }
    } else if (getTextureRectLevel() != 0)
        resetTextureRect();
}