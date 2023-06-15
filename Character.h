#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <SDL.h>
class Character {/**
           Class for character
           */
public:
    Character(int spawnHeight, const std::string& spritePath,int hp);/**
           class constructor
           */
    void setRenderer(SDL_Renderer* renderer);/**
           this function assigns a renderer to draw the character
           */
    bool loadSprite();/**
           function for loading sprite
           */
    void update();/**
           updating character location data
           */
    void render();/**
           drawing a character to the screen
           */
    void moveLeft();/**
           this function moves the character to the left
           */
    void moveRight();/**
           this function moves the character to the right
           */
    bool checkCharacterEnemyCollision(int pos);/**
           this function checks the character's collision with the enemy
           */
    void UpdateHp();/**
           this feature updates the health of the character
           */
    int direction;
    int x;
    int hp;
private:
    int spawnHeight;
    std::string spritePath;
    SDL_Renderer* renderer;
    SDL_Texture* sprite;
    SDL_Texture* red_heart;
    SDL_Texture* dark_heart;
    int y;
    int index; // ƒобавлено поле дл€ хранени€ текущего направлени€
};

#endif // CHARACTER_H

