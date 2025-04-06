#include "../include/player.h"

// Constructor
Player::Player(SDL_Texture *texture, int x, int y, int w, int h, int frames)
    // : Object(texture, x, y, w, h), frames(frames) {
    : texture(texture), x(x), y(y), w(w), h(h), frames(frames)
    {

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
    if (event.type == SDL_KEYDOWN && !event.key.repeat)
    {
        fire_bullet(event);
        keys[event.key.keysym.scancode] = true;
    }
    else if (event.type == SDL_KEYUP)
    {
        keys[event.key.keysym.scancode] = false;

        if (!keys[SDL_SCANCODE_UP] && !keys[SDL_SCANCODE_DOWN] && !keys[SDL_SCANCODE_LEFT] && !keys[SDL_SCANCODE_RIGHT])
        {
            Mix_HaltChannel(0);
            move_sound_playing = false;
        }

    }
    
}


void Player::fire_bullet(const SDL_Event &event)
{
    if (event.key.keysym.sym == SDLK_SPACE)
    {
        Player::bullets.push_back(Bullet(x + w / 2, y + h / 4, speed_bullet));
        Mix_PlayChannel(1, shoot_sound, 0);
    }
}


// Update
void Player::update()
{
    move();
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

    void Player::move()
    {
        bool moved = false;
        
        if (keys[SDL_SCANCODE_UP])      { if (y < 0) y = 5; y -= 2; moved = true; }
        if (keys[SDL_SCANCODE_DOWN])    { if (y + h > 600) y = 600 - h - 5; y += 2; moved = true; }
        if (keys[SDL_SCANCODE_LEFT])    { if (x < 0) x = 5; x -= 2; moved = true; }
        if (keys[SDL_SCANCODE_RIGHT])   { if (x + w > 800) x = 800 - w - 5; x += 2; moved = true; }

        if (moved) 
        {
            if (!move_sound_playing) 
            {
                Mix_PlayChannel(0, move_sound, -1);
                move_sound_playing = true;
            }
        } 
        else 
        {
            if (move_sound_playing) 
            {
                Mix_HaltChannel(0);
                move_sound_playing = false;
            }
        }
    }


// Renderer
void Player::render(SDL_Renderer *renderer)
{
    // Object::render(renderer);
    SDL_Rect dst = {x, y, w, h};
    SDL_RenderCopy(renderer, texture, NULL, &dst);
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
