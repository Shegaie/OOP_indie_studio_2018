/*
** EPITECH PROJECT, 2022
** bomberman
** File description:
** Created by Pierre Chaudron
*/

#ifndef BOMBERMAN_TIMER_HPP
#define BOMBERMAN_TIMER_HPP

#include <functional>
#include <memory>
#include <chrono>
#include "irrlicht/irrlicht.h"

class Timer {
    private:
        std::chrono::time_point<std::chrono::high_resolution_clock> timer;
        std::function<void()> task;
        float taskDelay;

    public:
        Timer();

        void setTask(std::function<void()> taskToDo, float delay);
        void executeTask();

        double getElapsedTime() const;
        void resetTimer();
};

#endif //BOMBERMAN_TIMER_HPP