/*
** EPITECH PROJECT, 2022
** bomberman
** File description:
** Created by Julien Montagne
*/

#ifndef BOMBERMAN_SOUNDMANAGER_HPP
#define BOMBERMAN_SOUNDMANAGER_HPP

#include <string>
#include <unordered_map>
#include <memory>
#include <SFML/Audio.hpp>

typedef struct sound_s {
    sf::SoundBuffer soundBuffer;
    sf::Sound sound;
    float volume;
} sound_t;

class SoundManager {
    public:
        SoundManager();
        ~SoundManager();

        void playSound(const std::string &key);
        void playMusic(const std::string &key);
        void addSounds(const std::unordered_map<std::string, std::pair<std::string, float>> &paths);
        void addMusic(const std::string &name, const std::string &path);
        void stopMusic(const std::string &key);

        void updateVolume();

        static float musicMultiplier;
        static float soundMultiplier;
        static float masterMultiplier;

    private:
        std::unordered_map<std::string, sound_t> sounds;
        std::unordered_map<std::string, std::unique_ptr<sf::Music>> musics;
};

#endif //BOMBERMAN_SOUNDMANAGER_HPP