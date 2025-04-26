#include "../include/Game_playing.h"
#include <SDL2/SDL_image.h>
#include <string>

#include "../func/handle_collision.h"
#include "../func/render.h"
#include "../func/level_up.h"

Game_Playing::Game_Playing(SDL_Renderer* renderer, Music* music, Font* font, Board* instruction, Board* setting)
{ 
    this->renderer = renderer;
    this->music = music;
    this->font = font;
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

void Game_Playing::init()
{
    // Load music
    music->loadsound("player_move", "../music/sound_effect/player_move_sound.wav");
    music->loadsound("player_shoot", "../music/sound_effect/gun_shoot.wav");


    // For player
    player_texture = IMG_LoadTexture(renderer, "../images/player.png");
    if (!player_texture)
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "LoadTexture player failed: %s", IMG_GetError());
        return;
    }

    player = new Player(music, player_texture);
    if (player == NULL)
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "LoadTexture player failed: %s", IMG_GetError());
        return;
    }

    // For enemy
    enemy_texture = IMG_LoadTexture(renderer, "../images/enemy.png");
    if (!enemy_texture)
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "LoadTexture enemy failed: %s", IMG_GetError());
        return;
    }

    for (int i = 0; i < ENEMY; i++)
    {
        Enemy *enemy = new Enemy(music, enemy_texture, enemy_speed, enemy_hp, 800, 80+86*i);
        if (enemy == NULL)
        {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Không thể tạo enemy!\n");
            return;
        }
        enemies.push_back(enemy);
    }

    // Load background
    background = IMG_LoadTexture(renderer, "../images/background_playing.jpg");
    if (!background)
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "IMG_LoadTexture background failed: %s", IMG_GetError());
        return;
    }

    time_delay.start(1000);
    time_delay_enemy.start(12000);

    return;
}


void Game_Playing::handle_event(SDL_Event& event)
{
    player->handle_event(event);
    for (auto& enemy : enemies)
        enemy->handle_event(event);
    // Check for collision
    handle_collision(*this);
}

// Update game
void Game_Playing::update()
{
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

    update_feature_level(*this);

    return;
}

// Renderer
void Game_Playing::render()
{
    if (background)
    {
        SDL_Rect background_playing = {0, 0, 800, 600};
        SDL_RenderCopy(renderer, background, NULL, &background_playing);
    }

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

    // Destroy IMGs
    if (player_texture) 
    {
        SDL_DestroyTexture(player_texture);
        player_texture = nullptr;
    }
    if (enemy_texture)
    {
        SDL_DestroyTexture(enemy_texture);
        enemy_texture = nullptr;
    }
    if (background)
    {
        SDL_DestroyTexture(background);
        background = nullptr;
    }

    buttons.clear();
}
