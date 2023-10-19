/*
** EPITECH PROJECT, 2022
** Indie
** File description:
** Created by Julien Montagne
*/

#include "Bomberman/Bomberman.hpp"

int main()
{
    Bomberman bomberman;

    if (!bomberman.run())
        return 84;
    return 0;
}