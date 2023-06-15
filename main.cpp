#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "character.h"
#include "spawn.h"
#include "ammo.h"
#include <SDL_mixer.h>
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

const int CHARACTER_WIDTH = 100;
const int CHARACTER_HEIGHT = 120;

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
SDL_Texture* buttonTexture = nullptr;
SDL_Texture* backgroundTexture = nullptr;
bool game;;
bool initializeSDL()/**
                    initializing the SDL library
                    */
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr)
    {
        std::cout << "Failed to create SDL window: " << SDL_GetError() << std::endl;
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr)
    {
        std::cout << "Failed to create SDL renderer: " << SDL_GetError() << std::endl;
        return false;
    }
    if(SDL_Init(SDL_INIT_AUDIO)<0)
        std::cout << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
    int result = Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    if (result < 0) {
        std::cout << "lol";
    }

    return true;
}

void closeSDL()/**
               Shutting down the library
               */
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    window = nullptr;
    renderer = nullptr;

    SDL_DestroyTexture(buttonTexture);
    buttonTexture = nullptr;

    SDL_DestroyTexture(backgroundTexture);
    backgroundTexture = nullptr;

    IMG_Quit();
    SDL_Quit();
}

SDL_Texture* loadTexture(const std::string& path)/**
                                                 function for loading texture
                                                 */
{
    SDL_Surface* surface = IMG_Load(path.c_str());
    if (surface == nullptr)
    {
        std::cout << "Failed to load image '" << path << "': " << IMG_GetError() << std::endl;
        return nullptr;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == nullptr)
    {
        std::cout << "Failed to create texture from surface: " << SDL_GetError() << std::endl;
    }

    SDL_FreeSurface(surface);
    return texture;
}

void StartGame()/**
                The beginning of the gameplay
                */
{
    Character character(475, "sprites/hero.jpg",3);
    backgroundTexture = loadTexture("sprites/city.jpg");
    character.setRenderer(renderer);
    character.loadSprite();
    bool quit = false;
    std::vector<Ammo> ammos;
    SDL_Event event;
    int ammo_pos;
    bool pause = false;
    UpdateKol();
    buttonTexture = loadTexture("sprites/pause.jpg");
    while (!quit)
    {
        
        StartSpawn(renderer, character.x);
        if (character.checkCharacterEnemyCollision(GetPos())) {
            character.hp--;
            if (character.hp == 0)
                quit = true;
        }
        AmmoController(renderer, GetPos());
        if (checkAmmoEnemyCollision(GetPos()))
            Death();
        while (SDL_PollEvent(&event) != 0)
        {
            if (event.type == SDL_QUIT)
            {
                quit = true;
                game = false;
            }
            else if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym)
                {
                case SDLK_a:
                    character.moveLeft();
                    break;
                case SDLK_d:
                    character.moveRight();
                    break;
                case SDLK_SPACE:
                    Shot(renderer,character.x,character.direction);
                    break;
                case SDLK_ESCAPE:
                    pause = true;
                    backgroundTexture = loadTexture("sprites/start_back.jpg");
                    break;
                default:
                    break;
                }
            }
        }

        SDL_RenderCopy(renderer, backgroundTexture, nullptr, nullptr);
        character.render();
        character.UpdateHp();
        while (pause)
        {
            while (SDL_PollEvent(&event) != 0)
            {
                if (event.type == SDL_QUIT)
                {
                    quit = true;
                }
                else if (event.type == SDL_MOUSEBUTTONDOWN)
                {
                    int mouseX, mouseY;
                    SDL_GetMouseState(&mouseX, &mouseY);

                    int buttonWidth, buttonHeight;
                    SDL_QueryTexture(buttonTexture, nullptr, nullptr, &buttonWidth, &buttonHeight);

                    int buttonX = (SCREEN_WIDTH - buttonWidth) / 2;
                    int buttonY = (SCREEN_HEIGHT - buttonHeight) / 2;

                    if (mouseX >= buttonX && mouseX < buttonX + buttonWidth &&
                        mouseY >= buttonY && mouseY < buttonY + buttonHeight)
                    {
                        pause = false;
                        backgroundTexture = loadTexture("sprites/city.jpg");
                    }
                }
            }
            Mix_HaltMusic();

            SDL_RenderClear(renderer);
            if (buttonTexture != nullptr)
            {
                int buttonWidth, buttonHeight;
                SDL_QueryTexture(buttonTexture, nullptr, nullptr, &buttonWidth, &buttonHeight);

                int buttonX = (SCREEN_WIDTH - buttonWidth) / 2;
                int buttonY = (SCREEN_HEIGHT - buttonHeight) / 2;

                SDL_Rect buttonRect = { buttonX, buttonY, buttonWidth, buttonHeight };
                SDL_RenderCopy(renderer, backgroundTexture, nullptr, nullptr);
                SDL_RenderCopy(renderer, buttonTexture, nullptr, &buttonRect);
            }

            SDL_RenderPresent(renderer);
        
        }
    }
    Death();
    UpdateAmmos();
    closeSDL();
}
int Menu()/**
          Starting the start menu
          */ 
{
    if (!initializeSDL())
    {
        closeSDL();
        return 1;
    }
    backgroundTexture = loadTexture("sprites/start_back.jpg");
    if (backgroundTexture == nullptr)
    {
        closeSDL();
        return 1;
    }
    buttonTexture = loadTexture("sprites/play.jpg");
    if (buttonTexture == nullptr)
    {
        closeSDL();
        return 1;
    }

    bool quit = false;
    SDL_Event event;
    Mix_Music* music = Mix_LoadMUS("menu_music.mp3");
   // Mix_PlayMusic(music, 0);

    while (!quit)
    {
        while (SDL_PollEvent(&event) != 0)
        {
            SDL_RenderCopy(renderer, backgroundTexture, nullptr, nullptr);
            if (event.type == SDL_QUIT)
            {
                quit = true;
                game = false;
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);

                int buttonWidth, buttonHeight;
                SDL_QueryTexture(buttonTexture, nullptr, nullptr, &buttonWidth, &buttonHeight);

                int buttonX = (SCREEN_WIDTH - buttonWidth) / 2;
                int buttonY = (SCREEN_HEIGHT - buttonHeight) / 2;

                if (mouseX >= buttonX && mouseX < buttonX + buttonWidth &&
                    mouseY >= buttonY && mouseY < buttonY + buttonHeight)
                {
                    quit = true;
                    SDL_DestroyTexture(buttonTexture);
                    buttonTexture = nullptr;
                    StartGame();
                }
            }
        }
        Mix_HaltMusic();

        SDL_RenderClear(renderer);
        if (buttonTexture != nullptr)
        {
            int buttonWidth, buttonHeight;
            SDL_QueryTexture(buttonTexture, nullptr, nullptr, &buttonWidth, &buttonHeight);

            int buttonX = (SCREEN_WIDTH - buttonWidth) / 2;
            int buttonY = (SCREEN_HEIGHT - buttonHeight) / 2;

            SDL_Rect buttonRect = { buttonX, buttonY, buttonWidth, buttonHeight };
            SDL_RenderCopy(renderer, backgroundTexture, nullptr, nullptr);
            SDL_RenderCopy(renderer, buttonTexture, nullptr, &buttonRect);
        }

        SDL_RenderPresent(renderer);
    }

    closeSDL();
}
int main(int argc, char* argv[])/**
                                the function responsible for the game cycle
                                */
{
    game = true;
    while (game)
    {
        Menu();
    }
    return 0;
}

