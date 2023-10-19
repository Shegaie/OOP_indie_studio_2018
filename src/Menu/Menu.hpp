/*
** EPITECH PROJECT, 2022
** Indie
** File description:
** Created by Julien Montagne
*/

#ifndef INDIE_MENU_HPP
#define INDIE_MENU_HPP

#include <functional>
#include <memory>
#include "irrlicht/irrlicht.h"
#include "SoundManager/SoundManager.hpp"
#include "Sprite2D/Sprite2D.hpp"
#include "IScene.hpp"
#include "IMenu.hpp"

class Menu : public IScene {
    public:
        Menu(irr::IrrlichtDevice *deviceArg, irr::video::IVideoDriver *driverArg, game_params_t &params);
        ~Menu();

        scene_t runScene() override;

    private:
        irr::IrrlichtDevice *device;
        irr::video::IVideoDriver *driver;
        game_params_t &gameParams;

        std::unordered_map<menu_t, std::function<std::unique_ptr<IMenu>()>> menuCreator;
        std::unique_ptr<IMenu> menuPtr;
        menu_t menu;

        SoundManager soundManager;
        std::unordered_map<std::string, Sprite2D> textures;
};

#endif //INDIE_MENU_HPP