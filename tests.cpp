/*#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#define DOCTEST_CONFIG_NO_MULTITHREADING
#include "doctest.h"
#include "Character.h"
#include "spawn.h"
#include "ammo.h"
#include <SDL.h>
TEST_CASE("Right") {
	Character character(500, "lol.jpg", 3);
	character.moveRight();
	CHECK(character.x == 610);
}
TEST_CASE("Left") {
	Character character(500, "lol.jpg", 3);
	character.moveLeft();
	CHECK(character.x == 570);
}
TEST_CASE("hero_load_sprite") {
	SDL_Window* window = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 100, 100, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	Character character(500, "sprites/hero.jpg", 3);
	character.setRenderer(renderer);
	CHECK(character.loadSprite()==true);
}
TEST_CASE("chek_hero_collision") {
	Character character(500, "sprites/hero.jpg", 3);
	CHECK(character.checkCharacterEnemyCollision(550) == true);
}
TEST_CASE("chek_enemy_collision") {
	SDL_Window* window = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 100, 100, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	Enemy enemy(100,"sprites/vrag_1.jpg",renderer,1);
	CHECK(enemy.checkCollision(-100)==true);
}
TEST_CASE("enemy_load_sprite") {
	SDL_Window* window = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 100, 100, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	Enemy enemy(100, "sprites/vrag_1.jpg", renderer, 1);
	CHECK(enemy.loadSprite(renderer) == true);
}
TEST_CASE("chek_enemy_pos") {
	SDL_Window* window = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 100, 100, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	Enemy enemy(100, "sprites/vrag_1.jpg", renderer, 1);
	StartSpawn(renderer, 500);
	CHECK(GetPos() == -99);
}
TEST_CASE("chek_ammo_pos") {
	SDL_Window* window = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 100, 100, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	Shot(renderer, 100, 1);
	CHECK(GetAmmosPos() == 100);
}
TEST_CASE("chek_ammo_enemy_collision") {
	SDL_Window* window = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 100, 100, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	Shot(renderer, 100, 1);
	CHECK(checkAmmoEnemyCollision(100)==true);
}
TEST_CASE("RightFalse") {
	Character character(500, "lol.jpg", 3);
	character.moveRight();
	CHECK(character.x != 510);
}
TEST_CASE("LeftFalse") {
	Character character(500, "lol.jpg", 3);
	character.moveLeft();
	CHECK(character.x != 470);
}
TEST_CASE("hero_load_spriteFalse") {
	SDL_Window* window = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 100, 100, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	Character character(500, "sprites/her.jpg", 3);
	character.setRenderer(renderer);
	CHECK(character.loadSprite() == false);
}
TEST_CASE("chek_hero_collisionFalse") {
	Character character(500, "sprites/hero.jpg", 3);
	CHECK(character.checkCharacterEnemyCollision(50) == false);
}
TEST_CASE("chek_enemy_collisionFalse") {
	SDL_Window* window = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 100, 100, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	Enemy enemy(100, "sprites/vrag_1.jpg", renderer, 1);
	CHECK(enemy.checkCollision(100) == false);
}
TEST_CASE("enemy_load_spriteFalse") {
	SDL_Window* window = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 100, 100, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	Enemy enemy(100, "sprites/vrag.jpg", renderer, 1);
	CHECK(enemy.loadSprite(renderer) == false);
}
TEST_CASE("chek_enemy_posFalse") {
	SDL_Window* window = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 100, 100, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	Enemy enemy(100, "sprites/vrag_1.jpg", renderer, 1);
	StartSpawn(renderer, 500);
	CHECK(GetPos() != 99);
}
TEST_CASE("chek_ammo_posFalse") {
	SDL_Window* window = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 100, 100, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	Shot(renderer, 100, 1);
	CHECK(GetAmmosPos() != -100);
}
TEST_CASE("chek_ammo_enemy_collisionFalse") {
	SDL_Window* window = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 100, 100, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	Shot(renderer, 100, 1);
	CHECK(checkAmmoEnemyCollision(-100) == false);
}*/

