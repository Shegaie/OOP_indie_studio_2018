/*
** EPITECH PROJECT, 2022
** bomberman
** File description:
** Created by Pierre Chaudron
*/

#ifndef BOMBERMAN_BUTTON_HPP
#define BOMBERMAN_BUTTON_HPP

#include "EventManager/EventManager.hpp"
#include "SoundManager/SoundManager.hpp"
#include "Sprite2D/Sprite2D.hpp"

class Button : public Sprite2D {
    private:
        SoundManager &sounds;

    public:
        Button(const std::string &path, irr::video::IVideoDriver *Driver,
                 const irr::core::position2d<irr::s32> &pos,
                 const irr::core::rect<irr::s32> &rect,
                 SoundManager &soundManager, bool toDisplay = true);
        ~Button();

        bool isClicked(const mouse_event_t &mouseEvent);
        void updateHoverState(const irr::core::position2d<irr::s32> &mousePos);
};

#endif //BOMBERMAN_BUTTON_HPP