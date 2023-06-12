#include "character.h"
#include <iostream>
#include <SDL_image.h>

const int CHARACTER_SPEED = 10;

Character::Character(int spawnHeight, const std::string& spritePath)
    : spawnHeight(spawnHeight), spritePath(spritePath), renderer(nullptr), sprite(nullptr), x(0), y(spawnHeight)
{
}

void Character::setRenderer(SDL_Renderer* renderer)
{
    this->renderer = renderer;
}

bool Character::loadSprite()
{
    sprite = IMG_LoadTexture(renderer, spritePath.c_str());
    if (sprite == nullptr)
    {
        std::cout << "Failed to load character sprite: " << IMG_GetError() << std::endl;
        return false;
    }
    return true;
}

void Character::update()
{
    // Character update logic here
}

void Character::render()
{
    SDL_Rect characterRect = { x, y, 100,120 };
    SDL_RenderCopy(renderer, sprite, nullptr, &characterRect);
    SDL_Rect srcRect = { 0, 0, 100,120 };
    SDL_Rect destRect = { x, y, 100,120 };
    SDL_RendererFlip flip = (direction == 1) ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
    SDL_RenderCopyEx(renderer, sprite, &srcRect, &destRect, 0.0, nullptr, flip);

}

void Character::moveLeft()
{
    if (x > 0) {
        x -= CHARACTER_SPEED;
    }
    direction = -1;
}

void Character::moveRight()
{
    if (x <1180) {
        x += CHARACTER_SPEED;
    }
    direction = 1;
}

