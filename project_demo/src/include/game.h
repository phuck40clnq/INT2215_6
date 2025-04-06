#ifndef GAME_H
#define GAME_H

#include "../include/Game_gameover.h"
#include "../include/Game_menu.h"
#include "../include/Game_playing.h"

// Fps
#define fps 60

// Max number of enemies
#define max_enemies 20
#define ENEMY 6

// Size of window
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

// Class Game
class Game
{
    private:
        SDL_Window *window;
        SDL_Renderer *renderer;
        Music music;
        SDL_Texture *background;

        Game_Playing* game;
        Game_Menu* menu;
        Game_Gameover* gameover;

    public:
        SDL_Renderer* get_renderer() { return renderer; }

        // Initialize and clean the game
        bool init(const char* title, int width, int height);
        void clean();
        void clean_data();
        void new_menu();
        void new_game();
        void new_gameover();

        // Game run
        void handle_event();
        void update();
        void render();

        void maintain_FPS();


        // Private constructor
        Game() : window(NULL), renderer(NULL) {}
        ~Game();
};

#endif