#include <iostream>
#include <SDL_image.h>
#include "ammo.h"

// Constants
const int AMMO_WIDTH = 30;
const int AMMO_HEIGHT = 30;
const int AMMO_SPEED = 3;
extern SDL_Rect characterRect;

Ammo::Ammo(int pos, const std::string& spritePath, SDL_Renderer* renderer, int direction, int ind)
    : spawnHeight(spawnHeight), spritePath(spritePath), renderer(renderer), x(pos), y(550), direction(direction), speed(AMMO_SPEED)
{
}
bool Ammo::loadSprite(SDL_Renderer* renderer)
{
    sprite = IMG_LoadTexture(renderer, spritePath.c_str());
    if (sprite == nullptr)
    {
        std::cout << "Failed to load enemy sprite: " << IMG_GetError() << std::endl;
        return false;
    }
    return true;
}


void Ammo::update()
{
    x+=direction*speed;
}

void Ammo::render()
{
    SDL_Rect ammoRect = { x, y, AMMO_WIDTH, AMMO_HEIGHT };
    SDL_RenderCopy(renderer, sprite, nullptr, &ammoRect);
}

bool Ammo::checkCollision(int pos)
{
    SDL_Rect ammoRect = { x, y, AMMO_WIDTH, AMMO_HEIGHT };
    if ( x <= 0 || x >= 1280) {
        return true;
    }
    else
    {
        return false;
    } 
    // return SDL_HasIntersection(&characterRect, &enemyRect);
}

std::vector<Ammo> ammos; 
int GetAmmosPos() {
    if (ammos.size() != 0)
        return ammos[0].x;
    else
        return -200;
}
void Shot(SDL_Renderer* renderer,  int pos,  int dis) {
    if (ammos.size() == 0) {
        int spawnSide = dis == 1 ? 1 : -1;
        Ammo enemy(pos, "sprites/bullet.jpg", renderer, spawnSide, 0);
        enemy.loadSprite(renderer);
        ammos.push_back(enemy);
    }
}
bool checkAmmoEnemyCollision(int pos) {
    if (abs(GetAmmosPos() - pos) <= 65) {
        ammos.erase(ammos.begin());
        return true;
    }
    else
    {
        return false;
    }
}
void UpdateAmmos() {
    if (ammos.size() != 0)
        ammos.erase(ammos.begin());
}
void AmmoController(SDL_Renderer* renderer, int pos)
{
    
    for (auto& ammo:ammos)
    {
        ammo.update();
        ammo.render();

        // Check collision with character
       if (ammo.checkCollision(pos))
        {
            // Enemy disappears
           ammos.erase(ammos.begin());
          
            break;
        }

    }

    SDL_RenderPresent(renderer);

}
