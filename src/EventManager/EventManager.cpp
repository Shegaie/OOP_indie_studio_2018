/*
** EPITECH PROJECT, 2022
** bomberman
** File description:
** Created by Pierre Chaudron
*/

#include <iostream>
#include "EventManager.hpp"

EventManager::EventManager()
{
    for (bool &i : KeyIsDown)
        i = false;
    mouseEvent = {{0, 0}, false, false};
}

bool EventManager::OnEvent(const irr::SEvent &event)
{
    if (event.EventType == irr::EET_KEY_INPUT_EVENT)
        KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
    if (event.EventType == irr::EET_MOUSE_INPUT_EVENT) {
        if (event.MouseInput.Event == irr::EMIE_LMOUSE_PRESSED_DOWN)
            mouseEvent = {{event.MouseInput.X, event.MouseInput.Y}, true, mouseEvent.rightButtonDown};
        if (event.MouseInput.Event == irr::EMIE_RMOUSE_PRESSED_DOWN)
            mouseEvent = {{event.MouseInput.X, event.MouseInput.Y}, mouseEvent.leftButtonDown, true};
    }
    return false;
}

bool EventManager::IsKeyDown(irr::EKEY_CODE keyCode)
{
    bool temp = KeyIsDown[keyCode];
    KeyIsDown[keyCode] = false;
    return temp;
}

bool EventManager::IsKeyPressed(irr::EKEY_CODE keyCode)
{
    return KeyIsDown[keyCode];
}

mouse_event_t EventManager::getMouseEvent()
{
    mouse_event_t temp = mouseEvent;
    mouseEvent.leftButtonDown = false;
    mouseEvent.rightButtonDown = false;
    return temp;
}
