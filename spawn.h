#ifndef SPAWN_H
#define SPAWN_H

#include <vector>
#include <SDL.h>
#include <iostream>
class Enemy/**
           Class for enemies
           */
{
public:
    Enemy(int spawnHeight, const std::string& spritePath, SDL_Renderer* renderer, int direction);/**
           class constructor
           */
    void update();/**
           updating character location data
           */
    void render();/**
           drawing a character to the screen
           */
    bool checkCollision(int x);/**
           checking for a collision with a character
           */
    bool loadSprite(SDL_Renderer* renderer);/**
           function for loading sprite
           */
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

void StartSpawn(SDL_Renderer* renderer,int pos);/**
           this function is responsible for spawning enemies
           */
int GetPos();/**
           this function returns the location of the enemy
           */
void Death();/**
           this function regulates the health of enemies
           */
void UpdateKol();/**
           Class for enemies
           */

#endif 
