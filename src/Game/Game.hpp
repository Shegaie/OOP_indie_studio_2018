/*
** EPITECH PROJECT, 2022
** bomberman
** File description:
** Created by Julien Montagne
*/

#ifndef BOMBERMAN_GAME_HPP
#define BOMBERMAN_GAME_HPP

#include <functional>
#include <memory>
#include "SoundManager/SoundManager.hpp"
#include "Sprite2D/Sprite2D.hpp"
#include "IScene.hpp"
#include "Player/Player.hpp"
#include "AI/AI.hpp"
#include "Button/Button.hpp"
#include "Map/Map.hpp"

#define RESUME 101
#define SAVE 102
#define EXIT 103

class Game: public IScene {
    public:
    Game(irr::IrrlichtDevice *deviceArg, irr::video::IVideoDriver *driverArg, game_params_t &params);
    ~Game();

    scene_t runScene() override;
    int manage_pause();
    int get_pause_event();
    int init_game();
    int remove_entities();
    int new_game();
    int load_game();
    int set_loaded_infos(std::vector<int> &infos, Player &player);
    int manage_win(int colorWin);
    std::vector<bool> assignColor();

    private:
    bool pause;
    game_params_t params;
    irr::IrrlichtDevice *device;
    irr::video::IVideoDriver *driver;
    SoundManager soundManager;
    EventManager *eventManager;
    Map map;
    int save_game ();
    irr::scene::ISceneManager *sceneManager;
    std::unordered_map<std::string, Sprite2D> textures;
    std::unordered_map<std::string, Button> buttons;
    std::vector<Player> players;
    std::vector<AI> ais;
};

#endif //BOMBERMAN_GAME_HPP