#include "../include/handle_collision.h"
#include "../include/level_up.h"
#include "../include/Game_playing.h"

#include <SDL2/SDL_image.h>
#include <string>

Game_Playing::Game_Playing(SDL_Renderer* renderer, Music* music, Font* font, Texture* texture, Board* instruction, Board* setting)
{ 
    this->renderer = renderer;
    this->music = music;
    this->font = font;
    this->texture = texture;
    this->instruction = instruction;
    this->setting = setting;
    init(); 
    create_buttons(); 
}

void Game_Playing::create_buttons()
{
    buttons.push_back(Button(font, 10, 10, 170, 50, "Time: "));
    buttons.push_back(Button(font, 220, 10, 160, 50, "Score: "));
    buttons.push_back(Button(font, 410, 10, 125, 50, "Level: "));
    buttons.push_back(Button(font, 560, 10, 155, 50, "Exp: "));


    for (auto& button : buttons) 
        button.set_font("font1");
}

void Game_Playing::render_for_buttons(int score, int time_seconds)
{
    int minutes = time_seconds / 60;
    int seconds = time_seconds % 60;

    std::string time_text = "";
    if (minutes < 10) time_text += "0";
    time_text += std::to_string(minutes) + ":";

    if (seconds < 10) time_text += "0";
    time_text += std::to_string(seconds);

    std::string score_text = "";
    if (score < 10) score_text += "0";
    score_text += std::to_string(score);

    std::string level_text = "";
    if (player->player_level < 10) level_text += "0";
    level_text += std::to_string(player->player_level);

    std::string exp_text = "" + std::to_string(player->player_exp) + " / " + std::to_string(player->exp_next_level);

    render_text(renderer, time_text.c_str(), 90, 21, font->get_font("font2"));
    render_text(renderer, score_text.c_str(), 310, 21, font->get_font("font2"));
    render_text(renderer, level_text.c_str(), 495, 21, font->get_font("font2"));
    render_text(renderer, exp_text.c_str(), 625, 21, font->get_font("font2"));
}

void Game_Playing::loadtexture_item()
{
    // Increase bullet damage
    texture->loadtexture("texture_buff_bullet_damage", "../images/items/bullet_buff_damage_item.png");

    // Bullet type
    texture->loadtexture("texture_bullet_type_default", "../images/items/bullet_type_default_item.png");
    texture->loadtexture("texture_bullet_type_explosion", "../images/items/bullet_type_explosion_item.png");
    texture->loadtexture("texture_bullet_type_ice", "../images/items/bullet_type_ice_item.png");
    texture->loadtexture("texture_bullet_type_poison", "../images/items/bullet_type_poison_item.png");
    texture->loadtexture("texture_bullet_type_electric", "../images/items/bullet_type_electric_item.png");

    // Shield
    texture->loadtexture("texture_buff_player_shield", "../images/items/shield_item.png");

    // Exp
    texture->loadtexture("texture_buff_player_exp", "../images/items/coin_item.png");

    // Special
    texture->loadtexture("texture_special_item", "../images/items/star_item.png");

    // Boom
    texture->loadtexture("texture_boom", "../images/items/star_item.png");
}

// ---Init---
void Game_Playing::init()
{
    // Load texture
    texture->loadtexture("texture_player", "../images/player_texture.png");
    texture->loadtexture("texture_enemy", "../images/enemy_texture.png");
    texture->loadtexture("texture_pause", "../images/setting_button.png");
    texture->loadtexture("texture_item", "../images/star.jpg");

    loadtexture_item();

    // Load music
    music->loadsound("player_move", "../music/sound_effect/player_move_sound.wav");
    music->loadsound("player_shoot", "../music/sound_effect/gun_shoot.wav");


    // Player
    player = new Player(music, texture, "texture_player");
    if (player == NULL)
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "New player failed!\n");
        return;
    }
    player->font = font->get_font("font1");

    // Enemy
    for (int i = 0; i < ENEMY; i++)
    {
        Enemy *enemy = new Enemy(music, texture, "texture_enemy", enemy_speed, enemy_hp, 810, 82+86*i);
        if (enemy == NULL)
        {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Load enemyfailed!\n");
            return;
        }
        enemies_to_add.push_back(enemy);
    }

    time_delay.start(1000);
    time_delay_enemy.start(12000);

    add_all_items_to_game();

    return;
}

// ---Handle event---
void Game_Playing::handle_event(SDL_Event& event)
{
    handle_click(event);
    if (get_overlay() == OVERLAY::PAUSE || get_overlay() == OVERLAY::INSTRUCTION)    return;

    player->handle_event(event);
    for (auto& enemy : enemies)
        enemy->handle_event(event);
}

void Game_Playing::handle_click(SDL_Event& event)
{
    
    handle_overlay(event);

    if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
    {
        int x, y;
        SDL_GetMouseState(&x, &y);

        for (auto& button : buttons)
        {
            if (!button.is_touch(x, y)) continue;
            music->playsound("click_button", -1, false);
            handle_button_click(button);
        }

        SDL_FRect pause_rect = {760, 0, 40, 40};
        if (texture->is_touch(x, y, pause_rect))
        {
            music->playsound("click_button", -1, false);
            set_overlay(OVERLAY::PAUSE);
            setting->set_active(true);
        }
    }
}

void Game_Playing::handle_button_click(Button& button)
{
    return;
}

// ---Overlay---
void Game_Playing::handle_overlay(SDL_Event& event)
{
    // Check if overlay is active
    if (!setting->is_active() && get_overlay() == OVERLAY::PAUSE)
    {
        setting->set_active(false);
        pop_overlay();
    }
    if (!instruction->is_active() && get_overlay() == OVERLAY::INSTRUCTION)
    {
        instruction->set_active(false);
        pop_overlay();
    }

    // Handle key events for overlay
    if (event.type == SDL_KEYDOWN)
    {
        if (event.key.keysym.sym == SDLK_p)
        {
            toggle_overlay(OVERLAY::PAUSE, setting); // Toggle PAUSE
        }
        else if (event.key.keysym.sym == SDLK_i)
        {
            toggle_overlay(OVERLAY::INSTRUCTION, instruction); // Toggle INSTRUCTION
        }
    }
}

void Game_Playing::toggle_overlay(OVERLAY overlay, Board* board)
{
    if (get_overlay() == overlay)
    {
        pop_overlay();
        board->set_active(false);
    }
    else
    {
        set_overlay(overlay);
        board->set_active(true);
    }
}

// ---Update game---
void Game_Playing::update()
{
    if (get_overlay() == OVERLAY::PAUSE || get_overlay() == OVERLAY::INSTRUCTION)    return;

    // Update Items
    update_items();

    if (player) player->update();
    for (auto& enemy : enemies)
    {
        enemy->update();
    }

    // Update time
    if (time_delay.is_finished())
    {
        time_seconds++;
        time_delay.start(1000);
    }

    // Check for collision
    handle_collision(*this);

    // Update again
    clean_items();
    clean_enemy();

    update_feature_level(*this);

    return;
}

// ---Render---
void Game_Playing::render()
{
    SDL_FRect background_playing_rect = {0, 0, 800, 600};
    SDL_FRect pause_rect = { 760, 0, 40, 40 };

    texture->render("background_playing", background_playing_rect, { 255, 255, 255, 255 }, false, false);
    texture->render("texture_pause", pause_rect, { 255, 255, 255, 128 }, true, true);

    // Render items
    render_items();

    player->render(renderer);
    for (auto& enemy : enemies) enemy->render(renderer);

    // int mouse_x, mouse_y;
    // SDL_GetMouseState(&mouse_x, &mouse_y);

    for (auto& button : buttons) 
    {
        button.render(renderer, -1, -1, false, -1);
    }

    render_for_buttons(score, time_seconds);

    return;
}

void Game_Playing::clean()
{
    for (auto& item : items)
    {
        if (item)  delete item;
        item = nullptr;
    }
    items.clear();

    if (player)
    {
        delete player;
        player = nullptr;
    }

    for (auto& enemy : enemies)
    {
        if (enemy)  delete enemy;
        enemy = nullptr;
    }
    
    buttons.clear();
}

// Items
void Game_Playing::add_item_to_game(Texture* texture, const char* texture_name, float x, float y, float w, float h, ITEM_EFFECT effect, ITEM_TRIGGER trigger, Uint32 delay, int level, int enemy_count, int boss_defeated)
{
    Item* new_item = nullptr;

    switch (effect)
    {
        case ITEM_EFFECT::BUFF_BULLET_DAMAGE:
            new_item = new Buff_Bullet_Damage_Item(texture, texture_name, x, y, w, h, effect, trigger, delay, level, enemy_count, boss_defeated);
            break;

        case ITEM_EFFECT::BUFF_BULLET_TYPE:
            new_item = new Buff_Bullet_Type_Item(texture, texture_name, x, y, w, h, effect, trigger, delay, level, enemy_count, boss_defeated);
            break;

        case ITEM_EFFECT::SHIELD:
            new_item = new Buff_Player_Shield_Item(texture, texture_name, x, y, w, h, effect, trigger, delay, level, enemy_count, boss_defeated);
            break;

        case ITEM_EFFECT::EXP:
            new_item = new Buff_Player_Exp_Item(texture, texture_name, x, y, w, h, effect, trigger, delay, level, enemy_count, boss_defeated);
            break;

        case ITEM_EFFECT::BOOM:
            new_item = new Boom(texture, texture_name, x, y, w, h, effect, trigger, delay, level, enemy_count, boss_defeated);
            break;

        default:
            SDL_Log(">>> Unknown ITEM_EFFECT type!");
            return;
    }

    if (new_item == nullptr)
    {
        SDL_Log("Failed to create item with effect %d", (int)effect);
        return;
    }

    SDL_Log(">>> Item created with effect %d", (int)effect);
    items.push_back(new_item);
}

void Game_Playing::add_all_items_to_game()
{
    // level = 3
    add_item_to_game(texture, "texture_buff_bullet_damage", -1, -1, 50, 50, ITEM_EFFECT::BUFF_BULLET_DAMAGE, ITEM_TRIGGER::PLAYER_LEVEL, -1, 2, -1, -1);
    
    // 10 sec
    add_item_to_game(texture, "texture_bullet_type_default", -1, -1, 50, 50, ITEM_EFFECT::BUFF_BULLET_TYPE, ITEM_TRIGGER::TIME_BASED, 1000, -1, -1, -1);
    
    add_item_to_game(texture, "texture_bullet_type_default", -1, -1, 50, 50, ITEM_EFFECT::BUFF_BULLET_TYPE, ITEM_TRIGGER::TIME_BASED, 1000, -1, -1, -1);
    add_item_to_game(texture, "texture_bullet_type_default", -1, -1, 50, 50, ITEM_EFFECT::BUFF_BULLET_TYPE, ITEM_TRIGGER::TIME_BASED, 1000, -1, -1, -1);
    add_item_to_game(texture, "texture_bullet_type_default", -1, -1, 50, 50, ITEM_EFFECT::BUFF_BULLET_TYPE, ITEM_TRIGGER::TIME_BASED, 1000, -1, -1, -1);
    add_item_to_game(texture, "texture_bullet_type_default", -1, -1, 50, 50, ITEM_EFFECT::BUFF_BULLET_TYPE, ITEM_TRIGGER::TIME_BASED, 1000, -1, -1, -1);

    // current_enemy = 10;
    add_item_to_game(texture, "texture_buff_player_shield", -1, -1, 50, 50, ITEM_EFFECT::SHIELD, ITEM_TRIGGER::ENEMY_COUNT, -1, -1, 7, -1);
    
    // 5 sec
    add_item_to_game(texture, "texture_buff_player_exp", -1, -1, 50, 50, ITEM_EFFECT::EXP, ITEM_TRIGGER::TIME_BASED, 5000, -1, -1, -1);
}

void Game_Playing::update_items()
{
    // Buff item
    for (auto& item : items)
    {
        if (!item->active())
        {
            item->ready(*this);
        }
    }
}

void Game_Playing::render_items()
{
    for (auto& item : items)
    {
        if (item->active())
        {
            item->render(renderer);
        }
    }
}
