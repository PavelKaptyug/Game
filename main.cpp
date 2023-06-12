#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "character.h"
#include "spawn.h"
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

const int CHARACTER_WIDTH = 100;
const int CHARACTER_HEIGHT = 120;

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
SDL_Texture* buttonTexture = nullptr;

bool initializeSDL()
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

    return true;
}

void closeSDL()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    window = nullptr;
    renderer = nullptr;

    SDL_DestroyTexture(buttonTexture);
    buttonTexture = nullptr;

    IMG_Quit();
    SDL_Quit();
}

SDL_Texture* loadTexture(const std::string& path)
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

void StartGame()
{
    // Load background image
    SDL_Texture* backgroundTexture = loadTexture("city.jpg");
    if (backgroundTexture == nullptr)
    {
        closeSDL();
        return;
    }

    Character character(500, "hero.jpg");
    character.setRenderer(renderer);
    character.loadSprite();

    bool quit = false;
    SDL_Event event;

    while (!quit)
    {
        while (SDL_PollEvent(&event) != 0)
        {
            if (event.type == SDL_QUIT)
            {
                quit = true;
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
                default:
                    break;
                }
            }
        }

        SDL_RenderClear(renderer);

        // Render the background
        SDL_RenderCopy(renderer, backgroundTexture, nullptr, nullptr);

        // Update and render the character
        character.update();
        character.render();

        // Update the screen
        SDL_RenderPresent(renderer);
    }

    // Clean up
    SDL_DestroyTexture(backgroundTexture);
    closeSDL();
}

int main(int argc, char* argv[])
{
    if (!initializeSDL())
    {
        closeSDL();
        return 1;
    }

    SDL_Texture* backgroundTexture = loadTexture("city.jpg");
    // Create button texture
    buttonTexture = loadTexture("play.jpg");
    if (buttonTexture == nullptr)
    {
        closeSDL();
        return 1;
    }

    bool quit = false;
    SDL_Event event;

    while (!quit)
    {
        while (SDL_PollEvent(&event) != 0)
        {
            SDL_RenderCopy(renderer, backgroundTexture, nullptr, nullptr);
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
                    quit = true;
                    SDL_DestroyTexture(buttonTexture);
                    buttonTexture = nullptr;
                    StartGame();
                    StartSpawn();
                }
            }
        }

        SDL_RenderClear(renderer);

        // Render the button
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

        // Update the screen
        SDL_RenderPresent(renderer);
    }

    closeSDL();

    return 0;
}
