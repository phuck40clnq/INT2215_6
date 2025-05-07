#include "../include/player.h"
#include "../include/render.h"

// Constructor
Player::Player(Music* music, Texture* texture, const char* texture_name, float x, float y, int w, int h, int frames)
    // : Object(texture, x, y, w, h), frames(frames) {
    : music(music), texture(texture), texture_player_name(texture_name), fx(x), fy(y), w(w), h(h), frames(frames)
    {
        // Set default values
        update_data();
        reset_data();
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
    update_data();
    reset_data();

    // Update shield
    update_shield();

    if (buff_timer.is_finished()) 
    {
        // Reset
        reset_data();

        buff_timer.reset();
        SDL_Log(">>> BUFF OFF");

        // Set color to normal
        player_color = {255, 255, 255, 255}; // White
        show_status_text("BUFF END", 500, fx - w / 2, fy - 35, 0, {200, 200, 200, 255});
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
        while (it != bullets.end())
        {
            it->update();
            if (!it->active())
                it = bullets.erase(it);
            else
                ++it;
        }
    }
    void Player::fire_bullet()
    {
        if (fired)
        {            
            int spacing = 20;
            int num_bullets = player_level / 3 + 1;
            if (num_bullets > 5) num_bullets = 5;
            for (int i = 0; i < num_bullets; i++)
            {
                int offset = i * spacing;
                float bullet_x = fx + w + offset;
                float bullet_y = fy + h / 2;
                // Player::bullets.push_back(Bullet(x + w / 2, y + h / 4, bullet_speed, bullet_damage));
                Player::bullets.push_back(Bullet(bullet_x, bullet_y, bullet_speed, bullet_damage, current_bullet_type));
            }
            music->playsound("player_shoot", 1);
            fired = false;
        }
    }
    void Player::move()
    {
        bool moved = false;
        
        if (keys[SDL_SCANCODE_UP])      { fy -= player_speed; if (fy < 80) fy = 85; moved = true; }
        if (keys[SDL_SCANCODE_DOWN])    { fy += player_speed; if (fy + h > 600) fy = 600 - h - 5; moved = true; }
        if (keys[SDL_SCANCODE_LEFT])    { fx -= player_speed; if (fx < 0) fx = 5; moved = true; }
        if (keys[SDL_SCANCODE_RIGHT])   { fx += player_speed; if (fx + w > 800) fx = 800 - w - 5; moved = true; }

        if (moved) 
        {
            if (!move_sound_playing) 
            {
                music->playsound("player_move", 0, true);
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

// ---Renderer---
void Player::render(SDL_Renderer* renderer)
{
    // Object::render(renderer);
    SDL_Color color = player_color;
    SDL_FRect dst = {fx, fy, float(w), float(h)};
    texture->render(texture_player_name, dst, color);
    render_shield(renderer);
    render_bullets(renderer);
    render_status_text(renderer);
    return;
}

void Player::render_bullets(SDL_Renderer* renderer)
    {
        for (auto& bullet : bullets)
        {
            bullet.render(renderer);
        }
    }

void Player::show_status_text(const char* text, Uint32 ms, int x, int y, int angle, SDL_Color color)
{
    status_text = text;
    status_time_duration = ms;
    status_text_x = x;
    status_text_y = y;
    status_text_angle = angle;
    status_text_color = color;
    status_timer.start(ms);
}
void Player::render_status_text(SDL_Renderer* renderer)
{
    if (!font) return;
    if (!status_timer.is_active()) return;

    float ratio = float (status_timer.time_delay_left()) / status_time_duration;
    Uint8 alpha = Uint8 (ratio * status_text_color.a);
    SDL_Color faded_color = status_text_color;
    faded_color.a = alpha;

    render_text(renderer, status_text, status_text_x, status_text_y, this->font, status_text_angle, faded_color);
}

void Player::clean()
{
    bullets.clear();
    return;
}


// ---Features---
void Player::combo()
{
    Uint32 current_time = SDL_GetTicks();

    if (buff)
    {
        buff_player(5, current_time);
        buff = false;
    }

    // Locked combos
    if (current_time - last_combo_reset_time < 15000)
        return;

    // Reset combo
    if (current_time - last_combo_time < 5000)
    {
        if (combo_kill_count >= 5 && !buff_timer.is_active())
        {
            buff_player(3, current_time);
        }
    }

    else
    {
        // Reset combo
        combo_kill_count = 0;
        last_combo_time = current_time;
        SDL_Log(">>> ----------------COMBO KILL: %d", combo_kill_count);
    }
}

void Player::buff_player(int sec, Uint32 current_time)
{
    update_data_buff_combo();

    // Buff 3 sec
    buff_timer.start(sec * 1000);
    SDL_Log("-------->>> BUFF - COMBO KILL: %d", combo_kill_count);

    // Buff speed
    player_speed += buff_player_speed;
    if (player_speed > 5.f) player_speed = 5.f;

    // Buff bullet speed and damage
    bullet_speed += buff_bullet_speed;
    if (bullet_speed > 10.f) bullet_speed = 10.f;
    bullet_damage += buff_bullet_damage;
    if (bullet_damage > 10.f) bullet_damage = 10.f;

    last_combo_reset_time = current_time;

    // Change color
    player_color = {255, 255, 0, 255}; // Yellow
    show_status_text("BUFF!", 1000, fx - w / 2, fy - 40, -35, {255, 215, 0, 255});
}

// Update data
void Player::update_data_buff_combo()
{
    this->buff_player_speed = base_player_speed * player_level * 0.05f;
    this->buff_bullet_speed = base_bullet_speed * player_level * 0.05f;
    this->buff_bullet_damage = base_bullet_damage * player_level * 0.05f;
}

void Player::reset_data()
{
    this->player_speed = base_player_speed;
    this->bullet_speed = base_bullet_speed;
    this->bullet_damage = base_bullet_damage;
}

void Player::update_data()
{
    this->base_player_speed = 2.f + player_level * 0.05f + increase_player_speed;
    // if (base_player_speed > 5.f) base_player_speed = 5.f;

    this->base_bullet_speed = 5.f + player_level * 0.05f + increase_bullet_speed;
    // if (base_bullet_speed > 10.f) base_bullet_speed = 10.f;

    this->base_bullet_damage = 2.f + player_level * 0.05f + increase_bullet_damage;
}

// ---Item---
// Shield
void Player::buff_shield(Uint32 timer)
{
    is_shield_active = true;
    shield_timer.start(timer);
    SDL_Log(">>> SHIELD ON");
    show_status_text("SHIELD ON", 500, fx - w / 2, fy - 35, -20, {100, 200, 255, 255});
}

void Player::update_shield()
{
    if (is_shield_active && shield_timer.is_finished())
    {
        is_shield_active = false;
        shield_timer.reset();
        SDL_Log(">>> SHIELD OFF");
        show_status_text("SHIELD OFF", 500, fx - w / 2 - 10, fy - 45, 0, {100, 200, 255, 255});
    }
}

void Player::draw_circle(SDL_Renderer* renderer, float cx, float cy, float r, SDL_Color color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    float thickness = 2.f;

    for (float y = -r; y <= r; y += 1.f)
    {
        for (float x = -r; x <= r; x += 1.f)
        {
            float dist = x * x + y * y;
            if (dist >= (r - thickness) * (r - thickness) && dist <= r * r)
            {
                SDL_RenderDrawPointF(renderer, cx + x, cy + y);
            }
        }
    }

    return;
}

void Player::render_shield(SDL_Renderer* renderer)
{
    if (!is_shield_active) return;
    SDL_BlendMode previous_mode;
    SDL_GetRenderDrawBlendMode(renderer, &previous_mode);

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    
    SDL_Color shield_color = {50, 120, 255, 180};

    float cx = fx + w / 2.0f;
    float cy = fy + h / 2.0f;

    float radius = (float)w * 0.7f;

    draw_circle(renderer, cx, cy, radius, shield_color);

    // Reset blend mode
    SDL_SetRenderDrawBlendMode(renderer, previous_mode);
}

void Player::reset_default()
{
    reset_data();

    current_bullet_type = BULLET_TYPE::DEFAULT;

    if (buff_timer.is_active())
    {
        buff = false;
        buff_timer.reset();

        player_color = {255, 255, 255, 255};
    }
    show_status_text("BUFF OFF", 250, fx - w / 2, fy - 35, 0, {200, 200, 200, 255});

    if (shield_timer.is_active())
    {
        is_shield_active = false;
        shield_timer.reset();
    }
    show_status_text("SHIELD OFF", 500, fx - w / 2 - 10, fy - 45, 0, {100, 200, 255, 255});

    SDL_Log(">>> Player reset to default after enemy eats Boom!");
}