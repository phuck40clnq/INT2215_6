#include "player.h"

// Constructor
Player::Player(SDL_Texture *texture, int x, int y, int w, int h, int frames)
    : Object(texture, x, y, w, h), frames(frames) {}

// Handle event
void Player::handle_event(const SDL_Event &event)
{
    if (event.type == SDL_KEYDOWN)
    {
        move(event);
        fire_bullet(event);
    }
}

    void Player::move(const SDL_Event &event)
    {
        switch (event.key.keysym.sym)
        {
            case SDLK_UP:   y -= 10; break;
            case SDLK_DOWN: y += 10; break;
            case SDLK_LEFT: x -= 10; break;
            case SDLK_RIGHT: x += 10; break;
        }
    }

    void Player::fire_bullet(const SDL_Event &event)
    {
        if (event.key.keysym.sym == SDLK_SPACE)
        {
            Player::bullets.push_back(Bullet(x + w / 2, y, speed));
        }
    }

// Update
void Player::update()
{
    update_bullets();
    return;
}

    void Player::update_bullets()
    {
        auto it = bullets.begin();
        for (auto& bullet : bullets)
        {
            bullet.update();
            if (bullet.active())
            {
                *it = bullet;
                ++it;
            }
        }
    }

// Renderer
void Player::render(SDL_Renderer *renderer)
{
    Object::render(renderer);
    render_bullets(renderer);
    return;
}

    void Player::render_bullets(SDL_Renderer *renderer)
    {
        for (auto& bullet : bullets)
        {
            bullet.render(renderer);
        }
    }
