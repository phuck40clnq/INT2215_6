#ifndef GAME_H
#define GAME_H

#include "enemy.h"
#include "player.h"

// Fps
#define fps 60

// Max number of enemies
#define max_enemies 5

// Size of window
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

// Class Game
class Game
{
    private:
        SDL_Window *window;
        SDL_Renderer *renderer;
        bool isRunning, isMenu;
        Player *player; SDL_Texture *player_texture;
        std::vector<Enemy*> enemies; SDL_Texture *enemy_texture;
        Music music;

        SDL_Texture *background;

    public:
        SDL_Renderer* get_renderer() { return renderer; }

        // Initialize and clean the game
        bool init(const char* title, int width, int height);
        void clean();
        bool menu() { return isMenu; };
        bool running() { return isRunning; };

        // Game run
        void handle_event();
            bool check_collision(const SDL_Rect &a, const SDL_Rect &b);
            void handle_collision();
        void update_game();
        void render();

        void maintain_FPS();

        // Private constructor
        Game() : window(NULL), renderer(NULL), isRunning(false) {}
        ~Game();
};

#endif