#ifndef AMMO_H
#define AMMO_H

#include <vector>
#include <SDL.h>
class Ammo/**
           Class for ammo
           */
{
public:
    Ammo(int x, const std::string& spritePath, SDL_Renderer* renderer, int direction, int ind);/**
           class constructor
           */
    void update();/**
           updating ammo location data
           */
    void render();/**
           drawing an ammo to the screen
           */
    bool checkCollision(int pos);/**
           checking for a collision with screen borders
           */
    bool loadSprite(SDL_Renderer* renderer);/**
           function for loading sprite
           */
    int ind;
    int x;
private:
    int spawnHeight;
    std::string spritePath;
    SDL_Renderer* renderer;
    SDL_Texture* sprite;
    int y;
    int direction;
    int speed;
};

void AmmoController(SDL_Renderer* renderer, int pos);/**
           this function updates all ammos on the screen
           */
void Shot(SDL_Renderer* renderer, int pos,  int dis);/**
           this function creates a new ammo if possible
           */
int GetAmmosPos();/**
           this function returns the location of the cartridge
           */
void UpdateAmmos();/**
           the function updates the number of ammos
           */
bool checkAmmoEnemyCollision(int pos);/**
           this function checks whether the ammo hit the enemy
           */
#endif // SPAWN_H
