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

        // Set default values
        this->normal_speed = 2.f + player_level * 0.05f;
        this->normal_bullet_speed = 5.f + player_level * 0.05f;
        this->normal_bullet_damage = 2.f + player_level * 0.05f;

        this->speed = 2.f + player_level * 0.05f;
        this->bullet_speed = 5.f + player_level * 0.05f;
        this->bullet_damage = 2.f + player_level * 0.05f;
        this->fx = x;
        this->fy = y;

        this->buff_speed = speed * player_level * 0.1f;
        this->buff_bullet_speed = bullet_speed * player_level * 0.1f;
        this->buff_bullet_damage = bullet_damage * player_level * 0.1f;
    }

// Handle event
void Player::handle_event(const SDL_Event &event)
{
    if (event.type == SDL_KEYDOWN && !event.key.repeat)
    {
        if (event.key.keysym.sym == SDLK_SPACE)
        {
            fired = true;
        }
        keys[event.key.keysym.scancode] = true;
    }
    else if (event.type == SDL_KEYUP)
    {
        if (event.key.keysym.sym == SDLK_SPACE)
        {
            fired = false;
        }
        keys[event.key.keysym.scancode] = false;

        if (!keys[SDL_SCANCODE_UP] && !keys[SDL_SCANCODE_DOWN] && !keys[SDL_SCANCODE_LEFT] && !keys[SDL_SCANCODE_RIGHT])
        {
            Mix_HaltChannel(0);
            move_sound_playing = false;
        }
    }
}


// Update
void Player::update()
{
    if (buff_timer.is_finished()) 
    {
        // Reset
        speed = normal_speed;
        bullet_speed = normal_bullet_speed;
        bullet_damage = normal_bullet_damage;

        buff_timer.reset();
        SDL_Log(">>> BUFF OFF");

        SDL_SetTextureColorMod(texture, 255, 255, 255);
    }
    fire_bullet();
    move();
    update_bullets();
    combo();
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

    void Player::fire_bullet()
    {
        if (fired)
        {
            for (int i = 0; i < player_level; i++)  Player::bullets.push_back(Bullet(x + w / 2, y + h / 4, bullet_speed, bullet_damage));
            Mix_PlayChannel(1, shoot_sound, 0);
            fired = false;
        }
    }


    void Player::move()
    {
        bool moved = false;
        
        if (keys[SDL_SCANCODE_UP])      { if (fy < 80) fy = 85; fy -= speed; moved = true; }
        if (keys[SDL_SCANCODE_DOWN])    { if (fy + h > 600) fy = 600 - h - 5; fy += speed; moved = true; }
        if (keys[SDL_SCANCODE_LEFT])    { if (fx < 0) fx = 5; fx -= speed; moved = true; }
        if (keys[SDL_SCANCODE_RIGHT])   { if (fx + w > 800) fx = 800 - w - 5; fx += speed; moved = true; }

        // Update position
        x = int (fx);
        y = int (fy);

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


// Features
void Player::combo()
{
    Uint32 current_time = SDL_GetTicks();

    // Locked combos
    if (current_time - last_combo_reset_time < 15000)
        return;

    // Reset combo
    // combo_kill_count > 0 && 
    if (current_time - last_combo_time < 5000)
    {
        if (combo_kill_count >= 5 && !buff_timer.is_active())
        {
            // Buff 3 sec
            buff_timer.start(3000);
            SDL_Log("-------->>> BUFF - COMBO KILL: %d", combo_kill_count);

            // Buff speed
            speed += buff_speed;

            // Buff bullet speed and damage
            bullet_speed += buff_bullet_speed;
            bullet_damage += buff_bullet_damage;

            last_combo_reset_time = current_time;

            // Others
            SDL_SetTextureColorMod(texture, 255, 255, 0);
        }
    }

    else
    {
        // Reset combo
        combo_kill_count = 0;
        last_combo_time = current_time;
        SDL_Log(">>> COMBO RESET");
        SDL_Log(">>> ----------------COMBO KILL: %d", combo_kill_count);
    }
}