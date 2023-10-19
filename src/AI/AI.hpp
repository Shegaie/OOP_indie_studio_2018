/*
** EPITECH PROJECT, 2019
** bomberman
** File description:
** AI.hpp
*/

#ifndef BOMBERMAN_AI_HPP
#define BOMBERMAN_AI_HPP

#include "../Player/Player.hpp"

class AI : public Player {
    private:
    int direction;
    int up;
    int down;
    int left;
    int right;
    int x;
    int y;
    std::pair<int, int> old_pos;

    std::vector<int> check_around(char c, std::vector<std::string> mapString);
    void init_positions();
    void defensive_action(std::vector<std::string> mapString, const std::vector<irr::scene::IMeshSceneNode *> &Cubes,
        const std::vector<irr::scene::IMeshSceneNode *> &Blocks, std::vector<Player> &players, std::vector<std::vector<Bomb>> &AIBombs);
    void offensive_action(Map &map, std::vector<std::string> mapString, irr::scene::ISceneManager *sceneManager, irr::video::IVideoDriver *driver,
        const std::vector<irr::scene::IMeshSceneNode *> &Cubes,
        const std::vector<irr::scene::IMeshSceneNode *> &Blocks, std::vector<Player> &players, std::vector<std::vector<Bomb>> &AIBombs);
    int move_IA(std::vector<int> &around, const std::vector<irr::scene::IMeshSceneNode *> &Cubes,
        const std::vector<irr::scene::IMeshSceneNode *> &Blocks, std::vector<Player> &players, std::vector<std::vector<Bomb>> &AIBombs);


    public:
    AI(int posX, int posY, irr::scene::ISceneManager *sceneManager,
        irr::video::IVideoDriver *driver, int color
    );

    ~AI();

    void chooseTheAiWay(const std::vector<irr::scene::IMeshSceneNode *> &Cubes,
        const std::vector<irr::scene::IMeshSceneNode *> &Blocks,
        irr::scene::ISceneManager *sceneManager, irr::video::IVideoDriver *driver, Map &map, std::vector<Player> &players, std::vector<std::vector<Bomb>> &AIBombs
    );
};

#endif //BOMBERMAN_AI_HPP
