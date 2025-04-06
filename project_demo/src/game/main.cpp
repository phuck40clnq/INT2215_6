#include "../include/game.h"

int main()
{
    Game game;

    if (!game.init("Game", SCREEN_WIDTH, SCREEN_HEIGHT))
    {
        game.clean();
        return 1;
    }

    while (is_running())
    {
        game.handle_event();
        game.update();
        game.render();

        // Handle fps
        game.maintain_FPS();
    }
    
    game.clean();

    return 0;
}