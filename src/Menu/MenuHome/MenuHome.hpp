/*
** EPITECH PROJECT, 2022
** bomberman
** File description:
** Created by Pierre Chaudron
*/

#ifndef BOMBERMAN_MENUHOME_HPP
#define BOMBERMAN_MENUHOME_HPP

#include <unordered_map>
#include "Timer/Timer.hpp"
#include "SoundManager/SoundManager.hpp"
#include "Button/Button.hpp"
#include "Menu/IMenu.hpp"

class MenuHome : public IMenu {
    private:
        std::unordered_map<std::string, Sprite2D> textures;
        std::unordered_map<std::string, Button> buttons;
        irr::IrrlichtDevice *device;
        irr::video::IVideoDriver *driver;
        SoundManager soundManager;
        Timer pepeAnimation;

        void updateElements() override;
        menu_t manageEvents() override;
        void drawTextures() override;

    public:
        MenuHome(irr::IrrlichtDevice *deviceArg, irr::video::IVideoDriver *driverArg);

        menu_t updateMenu() override;
};

#endif //BOMBERMAN_MENUHOME_HPP