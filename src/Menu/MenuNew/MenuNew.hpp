/*
** EPITECH PROJECT, 2022
** bomberman
** File description:
** Created by Pierre Chaudron
*/

#ifndef BOMBERMAN_MENUNEW_HPP
#define BOMBERMAN_MENUNEW_HPP

#include <unordered_map>
#include "SoundManager/SoundManager.hpp"
#include "Button/Button.hpp"
#include "Menu/IMenu.hpp"
#include "IScene.hpp"

class MenuNew : public IMenu {
    private:
        std::unordered_map<std::string, Sprite2D> textures;
        std::unordered_map<std::string, Button> buttons;
        irr::IrrlichtDevice *device;
        irr::video::IVideoDriver *driver;
        SoundManager soundManager;
        game_params_t &gameParams;

        void updateElements() override;
        menu_t manageEvents() override;
        void drawTextures() override;
        void changeSkin(const mouse_event_t &mouseEvent, const std::string &button, const std::string &player, bool positive);
        void changeMultiplayer(int level, bool state);

    public:
        MenuNew(irr::IrrlichtDevice *deviceArg, irr::video::IVideoDriver *driverArg, game_params_t &params);

        menu_t updateMenu() override;
};

#endif //BOMBERMAN_MENUNEW_HPP