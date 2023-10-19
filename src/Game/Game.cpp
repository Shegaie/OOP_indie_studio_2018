/*
** EPITECH PROJECT, 2022
** bomberman
** File description:
** Created by Julien Montagne
*/

#include <fstream>
#include "IScene.hpp"
#include "Game/Game.hpp"
#include "IrrlichtDevice.h"

std::vector<int> splitString(std::string s, std::string delimiter)
{
    size_t pos = 0;
    std::string token;
    std::vector<int> stringSplit;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        stringSplit.emplace_back(std::stoi(token));
        s.erase(0, pos + delimiter.length());
    }
    return (stringSplit);
}

Game::Game(irr::IrrlichtDevice *deviceArg, irr::video::IVideoDriver *driverArg,
    game_params_t &params
) : device(deviceArg), driver(driverArg), params(params)
{
    int RIGHT_B = 500;
    int TOP_B = 80;
    eventManager = dynamic_cast<EventManager *>(device->getEventReceiver());
    soundManager.addMusic("theme", "assets/game/music.ogg");
    soundManager.addSounds({{"select", {"assets/menu/sounds/select.ogg", 100}},
        {"click", {"assets/menu/sounds/click.ogg", 20}}});
    textures = {{"background",
        Sprite2D("assets/game/pause.jpeg", driver, {0, 0}, {0, 0, 1280, 720})},
        {"win", Sprite2D("assets/game/win.png", driver,
            {640 - (651 / 2), 360 - (486 / 2)}, {0, 0, 651, 486})}, {"black",
            Sprite2D("assets/game/black.png", driver, {0, 0},
                {0, 0, 1280, 720})}, {"game",
            Sprite2D("assets/game/background.jpeg", driver, {0, 0},
                {0, 0, 1280, 720})}, {"cursor",
            Sprite2D("assets/menu/textures/cursor.png", driver, {0, 0},
                {0, 0, 32, 32})}};
    buttons = {{"exit",
        Button("assets/game/exit.png", driver, {RIGHT_B, TOP_B + 350},
            {0, 0, 860, 83}, soundManager)}, {"save",
        Button("assets/game/save.png", driver, {RIGHT_B, TOP_B + 250},
            {0, 0, 860, 83}, soundManager)}, {"resume",
        Button("assets/game/resume.png", driver, {RIGHT_B, TOP_B + 150},
            {0, 0, 860, 83}, soundManager)}};
    sceneManager = device->getSceneManager();
    sceneManager->addLightSceneNode(nullptr,
        irr::core::vector3df(180, 100 / 2, -180));
    sceneManager->addLightSceneNode(nullptr,
        irr::core::vector3df(20, 100 / 2, -180));
    sceneManager->addCameraSceneNode(nullptr,
        irr::core::vector3df(200 / 2, 100 / 2, -100),
        irr::core::vector3df(200 / 2, 100 / 2, 0), -1, true);
}

Game::~Game()
{
}

int Game::get_pause_event()
{
    mouse_event_t mouse = eventManager->getMouseEvent();
    std::unordered_map<std::string, int> hoverables = {{"resume", RESUME},
        {"save", SAVE}, {"exit", EXIT}};

    for (auto &button: buttons)
        if (button.second.isClicked(mouse))
            return hoverables.at(button.first);
    return 0;
}

int Game::manage_pause()
{
    auto mousePos = device->getCursorControl()->getPosition();
    int event = get_pause_event();

    if (event == SAVE)
        save_game();
    if (eventManager->IsKeyPressed(irr::KEY_ESCAPE) || event == RESUME)
        pause = false;
    for (auto &button : buttons)
        button.second.updateHoverState(mousePos);
    textures.at("background").drawSprite();
    for (auto &button : buttons)
        button.second.drawSprite();
    textures.at("cursor").setPosition(
        device->getCursorControl()->getPosition());
    textures.at("cursor").drawSprite();
    return event;
}

int Game::remove_entities()
{
    for (auto &player: players) {
        std::vector<Bomb> bombs = player.getBombs();
        for (auto &bomb: bombs)
            bomb.remove_entities();
        if (player.getActivity())
            player.removePlayer();
    }
    for (auto &ai: ais) {
        std::vector<Bomb> bombs = ai.getBombs();
        for (auto &bomb: bombs)
            bomb.remove_entities();
        if (ai.getActivity())
            ai.removePlayer();
    }
    map.removeEntities();
    return 0;
}

int Game::new_game()
{
    std::vector<std::string> printMap;
    map.generateMapString(20, 10);
    printMap = map.getMapString();
    map.generateMap(printMap, 20, 10, sceneManager, driver);
    std::vector<bool> colorUsed = assignColor();
    std::vector<int> colorIA;
    for (int i = 0; i < 4; i++) {
        if (!colorUsed[i]) {
            colorIA.emplace_back(i);
            colorUsed[i] = true;
        }
    }
    if (!params.loaded) {
        Player player1(1, 1, sceneManager, driver, params.skinPlayerOne);
        players.emplace_back(player1);
        if (params.multiplayer) {
            Player player2(19, 1, sceneManager, driver, params.skinPlayerTwo);
            players.emplace_back(player2);
            AI ia1(19, 9, sceneManager, driver, colorIA[0]);
            ais.emplace_back(ia1);
            AI ia2(1, 9, sceneManager, driver, colorIA[1]);
            ais.emplace_back(ia2);
        } else {
            AI ia1(19, 9, sceneManager, driver, colorIA[0]);
            ais.emplace_back(ia1);
            AI ia2(1, 9, sceneManager, driver, colorIA[1]);
            ais.emplace_back(ia2);
            AI ia3(19, 1, sceneManager, driver, colorIA[2]);
            ais.emplace_back(ia3);
        }
    } else {
        AI ai1(18, 8, sceneManager, driver, colorIA[0]);
        ais.emplace_back(ai1);
        AI ai2(1, 8, sceneManager, driver, colorIA[1]);
        ais.emplace_back(ai2);
        AI ai3(18, 1, sceneManager, driver, colorIA[2]);
        ais.emplace_back(ai3);
    }
    return 0;
}

int Game::set_loaded_infos(std::vector<int> &infos, Player &player)
{
    player.setBombNumber(infos[3]);
    player.setExplosionRange(infos[4]);
    player.setSpeedFactor(infos[5]);
    player.setWallPass(infos[6]);
    return 0;
}

int Game::load_game()
{
    std::vector<int> infos = splitString(params.playerInfos[0], " ");
    if (infos[8] == 1) {
        Player player1(infos[1], infos[2], sceneManager, driver, infos[7]);
        set_loaded_infos(infos, player1);
        players.emplace_back(player1);
    }
    infos.clear();
    infos = splitString(params.aiInfos[0], " ");
    if (infos[8] == 1) {
        AI ai1(infos[1], infos[2], sceneManager, driver, infos[7]);
        set_loaded_infos(infos, ai1);
        ais.emplace_back(ai1);
    }
    infos.clear();
    infos = splitString(params.aiInfos[1], " ");
    if (infos[8] == 1) {
        AI ai2(infos[1], infos[2], sceneManager, driver, infos[7]);
        set_loaded_infos(infos, ai2);
        ais.emplace_back(ai2);
    }
    if (params.playerInfos.size() == 1) {
        infos.clear();
        infos = splitString(params.aiInfos[2], " ");
        if (infos[8] == 1) {
            AI ai3(infos[1], infos[2], sceneManager, driver, infos[7]);
            set_loaded_infos(infos, ai3);
            ais.emplace_back(ai3);
        }
    } else if (params.playerInfos.size() == 2) {
        infos.clear();
        infos = splitString(params.playerInfos[1], " ");
        if (infos[8] == 1) {
            Player player2(infos[1], infos[2], sceneManager, driver, infos[7]);
            set_loaded_infos(infos, player2);
            players.emplace_back(player2);
        }
    }
    map.setMapString(params.mapString);
    map.generateMap(params.mapString, 20, 10, sceneManager, driver);
    return 0;
}

int Game::init_game()
{
    pause = false;

    if (!params.loaded)
        new_game();
    else
        load_game();
    return 0;
}

int Game::manage_win(int colorWin)
{
    textures.at("black").drawSprite();
    textures.at("win").setTextureRectLevel(colorWin);
    textures.at("win").drawSprite();
    if (eventManager->IsKeyPressed(irr::KEY_RETURN))
        return MENU;
    else
        return GAME;
}

scene_t Game::runScene()
{
    int i = 0;
    int event_pause = 0;
    irr::video::SColor color(255, 255, 255, 255);
    init_game();
    soundManager.playMusic("theme");
    std::vector<bool> winner = {true, true, true, true};
    int colorWin = -1;

    while (device->run()) {
        driver->beginScene(true, true, color);
        if (winner[0] + winner[1] + winner[2] + winner[3] == 1) {
            for (auto &player : players) {
                if (player.getActivity()) {
                    colorWin = player.getColor();
                }
            }
            for (auto &ai : ais) {
                if (ai.getActivity())
                    colorWin = ai.getColor();
            }
        }
        if (winner[0] + winner[1] + winner[2] + winner[3] == 0)
            colorWin = 4;
        int winnerIncrement = 0;
        for (auto &player : players) {
            if (!player.getActivity() && winner[winnerIncrement] != false)
                winner[winnerIncrement] = false;
            winnerIncrement++;
        }
        for (auto &ai : ais) {
            if (!ai.getActivity() && winner[winnerIncrement] != false)
                winner[winnerIncrement] = false;
            winnerIncrement++;
        }
        if (eventManager->IsKeyPressed(irr::KEY_KEY_P))
            pause = true;
        if (pause) {
            event_pause = manage_pause();
            if (event_pause == EXIT) {
                soundManager.stopMusic("theme");
                remove_entities();
                players.clear();
                ais.clear();
                return MENU;
            }
            driver->endScene();
            continue;
        }
        textures.at("game").drawSprite();
        bool player_1_2 = false;
        std::vector<std::vector<Bomb>> aiBombs;
        for (auto &ai : ais)
            aiBombs.emplace_back(ai.getBombs());
        for (auto &player : players) {
            bool checkRun = false;
            if (player.getActivity()) {
                if (!player_1_2) {
                    if (eventManager->IsKeyPressed(irr::KEY_RETURN))
                        player.dropBomb(sceneManager, driver, map);
                    if (eventManager->IsKeyPressed(irr::KEY_UP)) {
                        player.movePlayer(0, map.getCubes(), map.getBlocks(),
                            players, aiBombs);
                        checkRun = true;
                    } else if (eventManager->IsKeyPressed(irr::KEY_DOWN)) {
                        player.movePlayer(2, map.getCubes(), map.getBlocks(),
                            players, aiBombs);
                        checkRun = true;
                    }
                    if (eventManager->IsKeyPressed(irr::KEY_RIGHT)) {
                        player.movePlayer(1, map.getCubes(), map.getBlocks(),
                            players, aiBombs);
                        checkRun = true;
                    } else if (eventManager->IsKeyPressed(irr::KEY_LEFT)) {
                        player.movePlayer(3, map.getCubes(), map.getBlocks(),
                            players, aiBombs);
                        checkRun = true;
                    }
                } else {
                    if (eventManager->IsKeyPressed(irr::KEY_SPACE))
                        player.dropBomb(sceneManager, driver, map);
                    if (eventManager->IsKeyPressed(irr::KEY_KEY_Z)) {
                        player.movePlayer(0, map.getCubes(), map.getBlocks(),
                            players, aiBombs);
                        checkRun = true;
                    } else if (eventManager->IsKeyPressed(irr::KEY_KEY_S)) {
                        player.movePlayer(2, map.getCubes(), map.getBlocks(),
                            players, aiBombs);
                        checkRun = true;
                    }
                    if (eventManager->IsKeyPressed(irr::KEY_KEY_D)) {
                        player.movePlayer(1, map.getCubes(), map.getBlocks(),
                            players, aiBombs);
                        checkRun = true;
                    } else if (eventManager->IsKeyPressed(irr::KEY_KEY_Q)) {
                        player.movePlayer(3, map.getCubes(), map.getBlocks(),
                            players, aiBombs);
                        checkRun = true;
                    }
                }
                if (checkRun)
                    i++;
                else
                    i = 0;
                player.setAnimation(i, checkRun);
            }
            if (!player.bombIsEmpty())
                player.manageBomb(map, sceneManager, driver, player, players);
            if (!player.explosionIsEmpty())
                player.manageExplosion();
            map.managePowerUp(&player);
            player_1_2 = !player_1_2;
        }
        for (auto &ai: ais) {
            if (ai.getActivity())
                ai.chooseTheAiWay(map.getCubes(), map.getBlocks(), sceneManager,
                    driver, map, players, aiBombs);
            if (!ai.bombIsEmpty())
                ai.manageBomb(map, sceneManager, driver, ai, players);
            if (!ai.explosionIsEmpty())
                ai.manageExplosion();
            map.managePowerUp(&ai);
        }
        sceneManager->drawAll();
        if (colorWin > -1) {
            if (manage_win(colorWin) == MENU) {
                soundManager.stopMusic("theme");
                remove_entities();
                players.clear();
                ais.clear();
                return MENU;
            }
        }
        driver->endScene();
    }
    return GAME;
}

std::vector<bool> Game::assignColor()
{
    std::vector<bool> colorUsed = {false, false, false, false};

    colorUsed[params.skinPlayerOne] = true;
    if (params.multiplayer)
        colorUsed[params.skinPlayerTwo] = true;
    return colorUsed;
}

int Game::save_game()
{
    std::ofstream outfile(".save");
    irr::core::vector3df position;
    std::vector<std::string> mapString = map.getMapString();

    for (auto &it : mapString)
        outfile << it << std::endl;
    outfile << " " << std::endl;
    for (auto &it : players) {
        position = it.getPosition();
        outfile << "1 " << (position.X + 5) / 10 << " " << (position.Y + 5) / 10 << " "
            << it.getBombNumber() << " " << it.getExplosionRange() << " "
            << it.getSpeedFactor() << " " << it.getWallPass() << " "
            << it.getColor() << " " << it.getActivity() << " "
            << it.getActivity() << std::endl;
    }
    for (auto &it : ais) {
        position = it.getPosition();
        outfile << "0 " << (position.X + 5) / 10 << " " << (position.Y + 5) / 10 << " "
            << it.getBombNumber() << " " << it.getExplosionRange() << " "
            << it.getSpeedFactor() << " " << it.getWallPass() << " "
            << it.getColor() << " " << it.getActivity() << " "
            << it.getActivity() << std::endl;
    }
    outfile.close();
    return 0;
}
