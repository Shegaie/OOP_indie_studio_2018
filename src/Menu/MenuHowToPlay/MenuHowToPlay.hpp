/*
** EPITECH PROJECT, 2022
** bomberman
** File description:
** Created by Pierre Chaudron
*/

#ifndef BOMBERMAN_MENUHOWTOPLAY_HPP
#define BOMBERMAN_MENUHOWTOPLAY_HPP

#include <unordered_map>
#include "Button/Button.hpp"
#include "Menu/IMenu.hpp"
#include "SoundManager/SoundManager.hpp"

class MenuHowToPlay : public IMenu {
    private:
        std::unordered_map<std::string, Sprite2D> textures;
        std::unordered_map<std::string, Button> buttons;
        irr::IrrlichtDevice *device;
        irr::video::IVideoDriver *driver;
        SoundManager soundManager;

        void updateElements() override;
        menu_t manageEvents() override;
        void drawTextures() override;

    public:
        menu_t updateMenu() override;

        ~MenuHowToPlay();
        MenuHowToPlay(irr::IrrlichtDevice *deviceArg, irr::video::IVideoDriver *driverArg);
};

#endif //BOMBERMAN_MENUHOWTOPLAY_HPP