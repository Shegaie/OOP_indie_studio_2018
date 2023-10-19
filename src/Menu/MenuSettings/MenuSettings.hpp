/*
** EPITECH PROJECT, 2022
** bomberman
** File description:
** Created by Pierre Chaudron
*/

#ifndef BOMBERMAN_MENUSETTINGS_HPP
#define BOMBERMAN_MENUSETTINGS_HPP

#include <unordered_map>
#include "SoundManager/SoundManager.hpp"
#include "Button/Button.hpp"
#include "Menu/IMenu.hpp"

class MenuSettings : public IMenu {
    private:
        std::unordered_map<std::string, Sprite2D> textures;
        std::unordered_map<std::string, Button> buttons;
        irr::IrrlichtDevice *device;
        irr::video::IVideoDriver *driver;
        SoundManager soundManager;

        void updateElements() override;
        menu_t manageEvents() override;
        void drawTextures() override;

        void checkVolumeChange(const mouse_event_t &mouseEvent, const std::string &buttonName,
        const std::string &volumeName, float &volume, bool positive, bool updateSounds = true);

    public:
        MenuSettings(irr::IrrlichtDevice *deviceArg, irr::video::IVideoDriver *driverArg);

        menu_t updateMenu() override;
};

#endif //BOMBERMAN_MENUSETTINGS_HPP