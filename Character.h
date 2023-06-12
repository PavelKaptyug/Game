#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <SDL.h>

class Character {
public:
    Character(int spawnHeight, const std::string& spritePath);
    void setRenderer(SDL_Renderer* renderer);
    bool loadSprite();
    void update();
    void render();
    void moveLeft();
    void moveRight();

private:
    int spawnHeight;
    std::string spritePath;
    SDL_Renderer* renderer;
    SDL_Texture* sprite;
    int x;
    int y;
    int direction; // ƒобавлено поле дл€ хранени€ текущего направлени€
};

#endif // CHARACTER_H

