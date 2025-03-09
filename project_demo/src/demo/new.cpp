#include "../core/game.h"

int main()
{
    Game game;
    
    if (!game.init("Game SDL2", SCREEN_WIDTH, SCREEN_HEIGHT))
    {
        std::cout << "Game init failed\n";
        game.clean();
        return 1;
    }

    while (game.running())
    {
        std::cout << "Game is running\n";
        break;
    }
}