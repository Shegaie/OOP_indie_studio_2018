/*
** EPITECH PROJECT, 2022
** bomberman
** File description:
** Created by Pierre Chaudron
*/

#ifndef BOMBERMAN_MENULOAD_HPP
#define BOMBERMAN_MENULOAD_HPP

#include <unordered_map>
#include "SoundManager/SoundManager.hpp"
#include "Button/Button.hpp"
#include "Menu/IMenu.hpp"
#include "IScene.hpp"

class MenuLoad : public IMenu {
    private:
        std::unordered_map<std::string, Sprite2D> textures;
        std::unordered_map<std::string, Button> buttons;
        irr::IrrlichtDevice *device;
        irr::video::IVideoDriver *driver;
        SoundManager soundManager;
        int error;
        game_params_t &gameParams;

        void updateElements() override;
        menu_t manageEvents() override;
        void drawTextures() override;

    public:
        MenuLoad(irr::IrrlichtDevice *deviceArg, irr::video::IVideoDriver *driverArg, game_params_t &params);

        menu_t updateMenu() override;
};

#endif //BOMBERMAN_MENULOAD_HPP