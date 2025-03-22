#include "../core/game.h"

int main()
{
    Game game;

    if (!game.init("Game", SCREEN_WIDTH, SCREEN_HEIGHT))
    {
        game.clean();
        return 1;
    }

    while (game.running())
    {
        // frameStart = SDL_GetTicks();
        game.handle_event();
        game.update_game();
        game.render();

        // Handle fps
        game.maintain_FPS();
    }
    
    game.clean();

    return 0;
}