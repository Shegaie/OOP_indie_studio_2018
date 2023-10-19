/*
** EPITECH PROJECT, 2022
** bomberman
** File description:
** Created by Julien Montagne
*/

#include <cmath>
#include <memory>
#include "BombermanException/BombermanException.hpp"
#include "SoundManager.hpp"

float SoundManager::musicMultiplier = 1;
float SoundManager::soundMultiplier = 1;
float SoundManager::masterMultiplier = 1;

SoundManager::SoundManager() {}

SoundManager::~SoundManager() {
    for (auto &sound : sounds)
        sound.second.sound.stop();
    for (auto &music : musics)
        music.second->stop();
}

void SoundManager::addSounds(const std::unordered_map<std::string, std::pair<std::string, float>> &paths) {
    for (const auto &path : paths) {
        sound_t &sound = sounds.insert({path.first, {sf::SoundBuffer(), sf::Sound(), path.second.second}}).first->second;

        if (!sound.soundBuffer.loadFromFile(path.second.first))
			throw BombermanException("Error opening '" + path.second.first + "'");
        sound.sound.setBuffer(sound.soundBuffer);
        sound.sound.setVolume(sound.volume * soundMultiplier * masterMultiplier);
    }
}

void SoundManager::addMusic(const std::string &name, const std::string &path) {
    musics.insert({name, std::make_unique<sf::Music>()});
    if (!musics.at(name)->openFromFile(path))
        throw BombermanException("Error opening '" + path + "'");
    musics.at(name)->setLoop(true);
    musics.at(name)->setVolume(20 * musicMultiplier * masterMultiplier);
}

void SoundManager::playSound(const std::string &key) {
    try {
        sounds.at(key).sound.play();
    } catch (const std::out_of_range &e) {
        throw BombermanException("Sound '" + key + "' doesn't exist");
    }
}

void SoundManager::playMusic(const std::string &key) {
    try {
        musics.at(key)->play();
    } catch (const std::out_of_range &e) {
        throw BombermanException("Music '" + key + "' doesn't exist");
    }
}

void SoundManager::updateVolume() {
    for (auto &sound : sounds)
        if (std::round(sound.second.sound.getVolume()) != std::round(sound.second.volume * soundMultiplier * masterMultiplier))
            sound.second.sound.setVolume(sound.second.volume * soundMultiplier * masterMultiplier);
    for (auto &music : musics)
        if (std::round(music.second->getVolume()) != std::round(20 * musicMultiplier * masterMultiplier))
            music.second->setVolume(20 * musicMultiplier * masterMultiplier);
}

void SoundManager::stopMusic(const std::string &key) {
    musics.at(key)->stop();
}