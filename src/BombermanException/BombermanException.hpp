/*
** EPITECH PROJECT, 2022
** bomberman
** File description:
** Created by Pierre Chaudron
*/

#ifndef BOMBERMAN_BOMBERMANEXCEPTION_HPP
#define BOMBERMAN_BOMBERMANEXCEPTION_HPP

#include <string>
#include <exception>

class BombermanException : public std::exception {
    private:
        std::string _message;

    public:
        BombermanException(const std::string &message);

        const char* what() const noexcept override;
};

#endif //BOMBERMAN_BOMBERMANEXCEPTION_HPP