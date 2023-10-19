/*
** EPITECH PROJECT, 2022
** bomberman
** File description:
** Created by Pierre Chaudron
*/

#ifndef BOMBERMAN_EVENTMANAGER_HPP
#define BOMBERMAN_EVENTMANAGER_HPP

#include "irrlicht/irrlicht.h"

typedef struct mouse_event_s {
    irr::core::position2di position;
    bool leftButtonDown;
    bool rightButtonDown;
} mouse_event_t;

class EventManager : public irr::IEventReceiver {
    private:
        bool KeyIsDown[irr::KEY_KEY_CODES_COUNT];
        mouse_event_t mouseEvent;

    public:
        EventManager();
        bool OnEvent(const irr::SEvent &event) override;
        mouse_event_t getMouseEvent();
        bool IsKeyDown(irr::EKEY_CODE keyCode);
        bool IsKeyPressed(irr::EKEY_CODE keyCode);
};

#endif //BOMBERMAN_EVENTMANAGER_HPP