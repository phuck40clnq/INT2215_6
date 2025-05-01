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

void Game_Playing::init()
{
    // Load texture
    texture->loadtexture("texture_player", "../images/player_texture.png");
    texture->loadtexture("texture_enemy", "../images/enemy_texture.png");
    texture->loadtexture("texture_pause", "../images/setting_button.png");

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

    // Enemy
    for (int i = 0; i < ENEMY; i++)
    {
        Enemy *enemy = new Enemy(music, texture, "texture_enemy", enemy_speed, enemy_hp, 800, 80+86*i);
        if (enemy == NULL)
        {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Load enemyfailed!\n");
            return;
        }
        enemies_to_add.push_back(enemy);
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
    // Check for collision
    handle_collision(*this);

    // Update enemies
    update_num_enemy();

    update_feature_level(*this);

    return;
}

// Renderer
void Game_Playing::render()
{
    SDL_FRect background_playing_rect = {0, 0, 800, 600};
    SDL_FRect pause_rect = { 740, 60, 60, 60 };

    texture->render("background_playing", background_playing_rect, { 255, 255, 255, 255 }, false, false);
    texture->render("texture_pause", pause_rect, { 255, 255, 255, 255 }, false, false);

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
    
    buttons.clear();
}
