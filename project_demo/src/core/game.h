#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

// Size of window
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

// Class Game
class Game
{
    private:
        SDL_Window *window;
        SDL_Renderer *renderer;
        bool isRunning;

    public:
        // Initialize and clean the game
        bool init(const char* title, int width, int height);
        void clean();
        bool running() { return isRunning; };

        // Game run
        void handle_event();
        void update_game();
        void render();

        // Private constructor
        Game() : window(NULL), renderer(NULL), isRunning(false) {}
        ~Game();
};

#endif