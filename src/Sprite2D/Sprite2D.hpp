/*
** EPITECH PROJECT, 2022
** bomberman
** File description:
** Created by Pierre Chaudron
*/

#ifndef BOMBERMAN_2DSPRITE_HPP
#define BOMBERMAN_2DSPRITE_HPP

#include <memory>
#include <vector>
#include "irrlicht/irrlicht.h"

class Sprite2D {
    protected:
        irr::video::ITexture *texture;
        irr::core::position2d<irr::s32> position;
        irr::core::rect<irr::s32> textureRect;
        irr::video::IVideoDriver *driver;
        bool display;

    public:
        Sprite2D(const std::string &path, irr::video::IVideoDriver *Driver,
                 const irr::core::position2d<irr::s32> &pos,
                 const irr::core::rect<irr::s32> &rect, bool toDisplay = true);
        ~Sprite2D();

        void setPosition(const irr::core::position2d<irr::s32> &pos);
        irr::core::position2d<irr::s32> getPosition() const;

        irr::core::dimension2d<irr::u32> getTextureSize() const;

        void setDisplay(bool displayBool);
        bool isDisplayed() const;

        irr::core::dimension2d<irr::s32> getTextureRectSize() const;
        void setTextureRect(const irr::core::rect<irr::s32> &rect);
        irr::core::rect<irr::s32> getTexturerect() const;
        void resetTextureRect();
        void incrementTextureRect(bool reset = true, bool positive = true);
        void setTextureRectLevel(int level);
        int getTextureRectLevel() const;

        bool isHover(int x, int y) const;

        void drawSprite() const;
};

#endif //BOMBERMAN_2DSPRITE_HPP