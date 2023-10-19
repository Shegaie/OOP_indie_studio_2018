/*
** EPITECH PROJECT, 2022
** bomberman
** File description:
** Created by Pierre Chaudron
*/

#include "BombermanException.hpp"

BombermanException::BombermanException(const std::string &message) :
_message(message) {}

const char *BombermanException::what() const noexcept {
    return _message.data();
}