#include <SDL_image.h>
#include "spawn.h"
#include <stdlib.h>

// Constants
const int ENEMY_WIDTH = 100;
const int ENEMY_HEIGHT = 100;
const int ENEMY_SPEED = 1;
SDL_Rect characterRect;

Enemy::Enemy(int spawnHeight, const std::string& spritePath, SDL_Renderer* renderer, int direction)
    : spawnHeight(spawnHeight), spritePath(spritePath), renderer(renderer), x(640-direction*740), y(spawnHeight), direction(direction), speed(ENEMY_SPEED)
{
}
bool Enemy::loadSprite(SDL_Renderer* renderer)
{
    sprite = IMG_LoadTexture(renderer, spritePath.c_str());
    if (sprite == nullptr)
    {
        std::cout << "Failed to load enemy sprite: " << IMG_GetError() << std::endl;
        return false;
    }
    return true;
}


void Enemy::update()
{
    x += direction * speed;
}

void Enemy::render()
{
    SDL_Rect enemyRect = { x, y, ENEMY_WIDTH, ENEMY_HEIGHT };
    SDL_RenderCopy(renderer, sprite, nullptr, &enemyRect);
}

bool Enemy::checkCollision(int pos)
{
    if (abs(x-pos)<=99)
        return true;
    else
    {
        return false;
    }
}
int kol = 0;
int hp;
std::vector<Enemy> enemies;
int GetPos() {
    if (enemies.size() != 0)
        return enemies[0].x;
    else
        return -300;
}
void Death() {
    hp--;
    if (hp == 0)
        enemies.erase(enemies.begin());
}
void UpdateKol() {
    kol = 0;
}
void StartSpawn(SDL_Renderer* renderer,int pos)
{
        if (enemies.size() == 0) {
            kol++;
            int dis = rand()%2;
            int spawnSide = dis == 0 ? -1 : 1;
            if (kol < 10) {
                Enemy enemy(520, "sprites/vrag_1.jpg", renderer, spawnSide);
                hp = 1;
                enemy.loadSprite(renderer);
                enemies.push_back(enemy);
            }
            else if(kol<20){
                Enemy enemy(520, "sprites/vrag_2.jpg", renderer, spawnSide);
                hp = 2;
                enemy.loadSprite(renderer);
                enemies.push_back(enemy);
            }
            else{
                Enemy enemy(520, "sprites/vrag_3.jpg", renderer, spawnSide);
                hp = 3;
                enemy.loadSprite(renderer);
                enemies.push_back(enemy);
            }
        }

        for (auto& enemy : enemies)
        {
            enemy.update();
            enemy.render();

            if (enemy.checkCollision(pos))
            {
                enemies.erase(enemies.begin());
                break;
            }
        }
}
