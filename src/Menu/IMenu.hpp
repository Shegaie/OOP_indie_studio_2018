/*
** EPITECH PROJECT, 2022
** bomberman
** File description:
** Created by Pierre Chaudron
*/

#ifndef BOMBERMAN_IMENU_HPP
#define BOMBERMAN_IMENU_HPP

typedef enum menu_e {
    HOME,
    SETTINGS,
    HOWTOPLAY,
    LOAD,
    NEW,
    NEWGAME
} menu_t;

class IMenu {
    private:
        virtual void updateElements() = 0;
        virtual menu_t manageEvents() = 0;
        virtual void drawTextures() = 0;

    public:
        virtual menu_t updateMenu() = 0;
};

#endif //BOMBERMAN_IMENU_HPP