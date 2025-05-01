#ifndef GAME_H
#define GAME_H

#include "Game_gameover.h"
#include "Game_menu.h"
#include "Game_playing.h"

// Fps
#define fps 60

// Size of window
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

// Class Game
class Game
{
    private:
        // Frames
        unsigned frame_start;
        int frame_delay = 1000 / fps;

        SDL_Window *window;
        SDL_Renderer *renderer;

        Game_Playing* game;
        Game_Menu* menu;
        Game_Gameover* gameover;

        Board* instruction,* setting;
        Music music;
        Font font;
        Texture texture;

    public:

        SDL_Renderer* get_renderer() { return renderer; }

        // Initialize and clean the game
        bool init(const char* title, int width, int height);
        void clean();
        void clean_data();
        void new_menu();
        void new_game();
        void new_gameover();
        void new_instruction();

        // Game run
        void handle_event();
        void handle_state(GAME_STATE state, SDL_Event& event);
        void handle_overlay(OVERLAY overlay, SDL_Event& event);

        void update();
        
        void render();
        void render_state(GAME_STATE state);
        void render_overlay(OVERLAY overlay);

        void start_frame();
        void end_frame();

        // Constructor
        Game();
        ~Game() { clean(); }
};

#endif