/*
** EPITECH PROJECT, 2022
** bomberman
** File description:
** Created by Pierre Chaudron
*/

#include "BombermanException/BombermanException.hpp"
#include "Sprite2D.hpp"

Sprite2D::Sprite2D(const std::string &path, irr::video::IVideoDriver *driverArg,
    const irr::core::vector2d<irr::s32> &pos,
    const irr::core::rect<irr::s32> &txRect, bool toDisplay)
    : position(pos),
    textureRect(txRect), driver(driverArg), display(toDisplay)
{
    texture = driverArg->getTexture(path.c_str());
    if (!texture)
        throw BombermanException("Error loading texture: " + path);
}

Sprite2D::~Sprite2D() {}

void Sprite2D::setPosition(const irr::core::vector2d<irr::s32> &pos)
{
    position = pos;
}

irr::core::vector2d<irr::s32> Sprite2D::getPosition() const
{
    return position;
}

void Sprite2D::setTextureRect(const irr::core::rect<irr::s32> &rect)
{
    textureRect = rect;
}

irr::core::rect<irr::s32> Sprite2D::getTexturerect() const
{
    return textureRect;
}

void Sprite2D::drawSprite() const
{
    if (display)
        driver->draw2DImage(texture, position, textureRect, 0,
        irr::video::SColor(255, 255, 255, 255), true);
}

irr::core::dimension2d<irr::s32> Sprite2D::getTextureRectSize() const
{
    return {textureRect.LowerRightCorner.X - textureRect.UpperLeftCorner.X,
            textureRect.LowerRightCorner.Y - textureRect.UpperLeftCorner.Y};
}

bool Sprite2D::isHover(int x, int y) const
{
    if (display)
        return (x > position.X && x < position.X + getTextureRectSize().Width
        && y > position.Y && y < position.Y + getTextureRectSize().Height);
    else
        return false;
}

void Sprite2D::resetTextureRect() {
    textureRect.LowerRightCorner.X = getTextureRectSize().Width;
    textureRect.LowerRightCorner.Y = getTextureRectSize().Height;
    textureRect.UpperLeftCorner.X = 0;
    textureRect.UpperLeftCorner.Y = 0;
}

void Sprite2D::incrementTextureRect(bool reset, bool positive) {
    auto size = getTextureRectSize();

    if (size.Width != getTextureSize().Width) {
        if (positive) {
            if (textureRect.UpperLeftCorner.X + size.Width != getTextureSize().Width) {
                textureRect.UpperLeftCorner.X += size.Width;
                textureRect.LowerRightCorner.X += size.Width;
            } else if (reset)
                resetTextureRect();
        } else {
            if (textureRect.UpperLeftCorner.X > 0) {
                textureRect.UpperLeftCorner.X -= size.Width;
                textureRect.LowerRightCorner.X -= size.Width;
            } else if (reset) {
                textureRect.UpperLeftCorner.X = getTextureSize().Width - size.Width;
                textureRect.LowerRightCorner.X = getTextureSize().Width;
            }
        }
    } else {
        if (positive) {
            if (textureRect.UpperLeftCorner.Y+ size.Height != getTextureSize().Height) {
                textureRect.UpperLeftCorner.Y += size.Height;
                textureRect.LowerRightCorner.Y += size.Height;
            } else if (reset)
                resetTextureRect();
        } else {
            if (textureRect.UpperLeftCorner.Y > 0) {
                textureRect.UpperLeftCorner.Y -= size.Height;
                textureRect.LowerRightCorner.Y -= size.Height;
            } else if (reset) {
                textureRect.UpperLeftCorner.Y = getTextureSize().Height - size.Height;
                textureRect.LowerRightCorner.Y = getTextureSize().Height;
            }
        }
    }
}

void Sprite2D::setTextureRectLevel(int level) {
    auto size = getTextureRectSize();

    if (size.Width != getTextureSize().Width) {
        textureRect.UpperLeftCorner.X = level * size.Width;
        textureRect.LowerRightCorner.X = (level + 1) * size.Width;
    } else {
        textureRect.UpperLeftCorner.Y = level * size.Height;
        textureRect.LowerRightCorner.Y = (level + 1) * size.Height;

    }
}

int Sprite2D::getTextureRectLevel() const {
    if (getTextureRectSize().Width != getTextureSize().Width)
        return textureRect.UpperLeftCorner.X / getTextureRectSize().Width;
    else
        return textureRect.UpperLeftCorner.Y / getTextureRectSize().Height;
}

void Sprite2D::setDisplay(bool displayBool) {
    display = displayBool;
}

bool Sprite2D::isDisplayed() const {
    return display;
}

irr::core::dimension2d<irr::u32> Sprite2D::getTextureSize() const {
    return texture->getSize();
}