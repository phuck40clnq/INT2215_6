#include "player.h"

// Constructor
Player::Player(SDL_Texture *texture, int x, int y, int w, int h, int frames)
    : Object(texture, x, y, w, h), frames(frames) {
        shoot_sound = Mix_LoadWAV("../music/gun_shoot.wav");
        if (shoot_sound == NULL)
        {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Player load sound failed: %s", Mix_GetError());
        }
        move_sound = Mix_LoadWAV("../music/player_move_sound.wav");
        if (move_sound == NULL)
        {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Player load sound failed: %s", Mix_GetError());
        }
    }

// Handle event
void Player::handle_event(const SDL_Event &event)
{
    if (event.type == SDL_KEYDOWN)
    {
        move(event);
        fire_bullet(event);
    }
    else if (event.type == SDL_KEYUP)
    {
        move_sound_playing = false;
        Mix_HaltChannel(0);
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Player stop move sound");
    }
}

    void Player::move(const SDL_Event &event)
    {
        bool moved = false;
        
        switch (event.key.keysym.sym)
        {
            case SDLK_UP:   y -= 10; moved = true; break;
            case SDLK_DOWN: y += 10; moved = true; break;
            case SDLK_LEFT: x -= 10; moved = true; break;
            case SDLK_RIGHT: x += 10; moved = true; break;
        }

        if (moved) {
            if (!move_sound_playing) {  // Chỉ phát âm thanh khi bắt đầu di chuyển
                Mix_PlayChannel(0, move_sound, -1);  // Luôn dùng kênh 0 cho di chuyển
                move_sound_playing = true;
                SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Player move sound");
            }
        } else {
            if (move_sound_playing) {  // Chỉ dừng nếu trước đó đang di chuyển
                Mix_HaltChannel(0);  // Dừng đúng kênh 0
                move_sound_playing = false;
                SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Player stop move sound");
            }
        }

        
    }

    void Player::fire_bullet(const SDL_Event &event)
    {
        if (event.key.keysym.sym == SDLK_SPACE)
        {
            Player::bullets.push_back(Bullet(x + w / 2, y, speed));
            Mix_PlayChannel(-1, shoot_sound, 0);
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
