#include "character.h"
#include <iostream>
#include <SDL_image.h>

const int CHARACTER_SPEED = 20;

Character::Character(int spawnHeight, const std::string& spritePath,int hp)
    : spawnHeight(spawnHeight), spritePath(spritePath), renderer(nullptr), sprite(nullptr), x(590), y(spawnHeight),index(0),hp(hp)
{
}

void Character::setRenderer(SDL_Renderer* renderer)
{
    this->renderer = renderer;
}

bool Character::loadSprite()
{
    sprite = IMG_LoadTexture(renderer, spritePath.c_str());
    red_heart= IMG_LoadTexture(renderer, "sprites/love.jpg");
    dark_heart = IMG_LoadTexture(renderer, "sprites/death.jpg");
    if (sprite == nullptr)
    {
        std::cout << "Failed to load character sprite: " << IMG_GetError() << std::endl;
        return false;
    }
    return true;
}

void Character::UpdateHp()
{
    for (int i = 1; i <= hp; i++) {
        SDL_Rect hpRect = { 1200-i*100, 50, 100,120 };
        SDL_RenderCopy(renderer, red_heart, nullptr, &hpRect);
    }for (int i = hp+1; i <= 3; i++) {
        SDL_Rect hpRect = { 1200 - i * 100, 50, 100,120 };
        SDL_RenderCopy(renderer, dark_heart, nullptr, &hpRect);
    }
}

void Character::render()
{
    SDL_Rect characterRect = { x, y, 100,150 };
    SDL_RenderCopy(renderer, sprite, nullptr, &characterRect);
    SDL_Rect srcRect = { x-100, y-150, 100,150 };
    SDL_Rect destRect = { x, y, 100,150 };
    SDL_RendererFlip flip = (direction != 1) ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
    SDL_RenderCopyEx(renderer, sprite, NULL, &destRect, 0.0, nullptr, flip);

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
bool Character:: checkCharacterEnemyCollision(int pos) {
    if (abs(x - pos) <= 100)
        return true;
    else
    {
        return false;
    }
}

