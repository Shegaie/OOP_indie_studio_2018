/*
** EPITECH PROJECT, 2022
** bomberman
** File description:
** Created by Pierre Chaudron
*/

#include "Timer.hpp"

Timer::Timer() {
    timer = std::chrono::high_resolution_clock::now();
}

void Timer::setTask(std::function<void()> taskToDo, float delay) {
    task = std::move(taskToDo);
    taskDelay = delay;
}

double Timer::getElapsedTime() const {
    return std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - timer).count() * 1000;
}

void Timer::resetTimer() {
    timer = std::chrono::high_resolution_clock::now();
}

void Timer::executeTask() {
    if (getElapsedTime() >= taskDelay) {
        task();
        resetTimer();
    }
}