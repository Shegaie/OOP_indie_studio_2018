/*
** EPITECH PROJECT, 2022
** bomberman
** File description:
** Created by Pierre Chaudron
*/

#ifndef BOMBERMAN_BOMBERMAN_HPP
#define BOMBERMAN_BOMBERMAN_HPP

#include <memory>
#include <unordered_map>
#include <functional>
#include "irrlicht/irrlicht.h"
#include "EventManager/EventManager.hpp"
#include "IScene.hpp"

class Bomberman {
    private:
        irr::IrrlichtDevice *device;
        irr::video::IVideoDriver *driver;
        EventManager eventManager;

        game_params_t gameParams;

        std::unordered_map<scene_t, std::function<std::unique_ptr<IScene>()>> sceneCreator;
        std::unique_ptr<IScene> scenePtr;
        scene_t scene;

        void playPreroll();

    public:
        Bomberman();
        ~Bomberman();

        bool run();
};

#endif //BOMBERMAN_BOMBERMAN_HPP