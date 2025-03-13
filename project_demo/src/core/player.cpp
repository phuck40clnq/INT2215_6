#include "player.h"

// Constructor
Player::Player(int x, int y, int w, int h, int frames)
    : Object(x, y, w, h), frames(frames) {}

// Player
void Player::handle_event(const SDL_Event &event)
{
    return;
}

void Player::update()
{
    for (int i = 0; i < 1000; i++)
    {
        if (x == 10)
        {
            x = 800;
        }
        x -= 5;
    }
    return;
    
}

void Player::render(SDL_Renderer *renderer)
{
    Object::render(renderer);
    return;
}
