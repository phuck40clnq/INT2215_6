#include "../include/Game_playing.h"
#include <SDL2/SDL_image.h>
#include <string>

#include "../func/handle_collision.h"
#include "../func/render_text.h"

void Game_Playing::create_buttons()
{
    buttons.push_back(Button(10, 10, 170, 50, "Time: "));
    buttons.push_back(Button(220, 10, 120, 50, "Score: "));
    buttons.push_back(Button(370, 10, 125, 50, "Level: "));
    buttons.push_back(Button(520, 10, 150, 50, "Exp: "));


    for (auto& button : buttons) 
        button.set_font(font1);
}

void Game_Playing::render_for_buttons(SDL_Renderer* renderer, int score, int time_seconds)
{
    int minutes = time_seconds / 60;
    int seconds = time_seconds % 60;

    std::string time_text = "";
    if (minutes < 10) time_text += "0";
    time_text += std::to_string(minutes) + ":";

    if (seconds < 10) time_text += "0";
    time_text += std::to_string(seconds);

    std::string score_text = "" + std::to_string(score);

    std::string level_text = "";
    if (player->player_level < 10) level_text += "0";
    level_text += std::to_string(player->player_level);

    std::string exp_text = "" + std::to_string(player->player_exp) + " / " + std::to_string(player->exp_next_level);

    render_text(renderer, time_text.c_str(), 90, 21, font2);
    render_text(renderer, score_text.c_str(), 310, 21, font2);
    render_text(renderer, level_text.c_str(), 455, 21, font2);
    render_text(renderer, exp_text.c_str(), 585, 21, font2);
}

void Game_Playing::init(SDL_Renderer* renderer)
{
    // Load music
    // if (!music.loadmusic("background", "../music/background.mp3"))   return;
    // if (!music.loadsound("shoot", "../music/gun_shoot.wav"))    return;
    // if (!music.loadsound("explosion", "../music/explosion.mp3")) return;

    music.setvolume();

    // Load font
    font1 = TTF_OpenFont("../font/font3.ttf", 30);
    if (font1 == NULL)
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "TTF_OpenFont font_playing failed: %s", IMG_GetError());
        return;
    }
    font2 = TTF_OpenFont("../font/font2.ttf", 28);
    if (font2 == NULL)
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "TTF_OpenFont font_playing failed: %s", IMG_GetError());
        return;
    }

    // For player
    player_texture = IMG_LoadTexture(renderer, "../images/player.png");
    if (!player_texture)
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "LoadTexture player failed: %s", IMG_GetError());
        return;
    }

    player = new Player(player_texture);
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
        Enemy *enemy = new Enemy(enemy_texture, 800, 80+85*i);
        if (enemy == NULL)
        {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Không thể tạo enemy!\n");
            return;
        }
        enemies.push_back(enemy);
    }

    // Load background
    background = IMG_LoadTexture(renderer, "../images/background.jpg");
    if (!background)
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "IMG_LoadTexture background failed: %s", IMG_GetError());
        return;
    }

    return;
}


void Game_Playing::handle_event()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT) set_running(false);

        player->handle_event(event);
        for (auto &enemy : enemies)
            enemy->handle_event(event);
    }
    // Check for collision
    handle_collision(*this);
}

// Update game
void Game_Playing::update()
{
    if (player) player->update();
    for (auto &enemy : enemies)
    {
        enemy->update();
    }
    return;
}

// Renderer
void Game_Playing::render(SDL_Renderer* renderer)
{
    if (background)
    {
        SDL_Rect background_playing = {0, 0, 800, 600};
        SDL_RenderCopy(renderer, background, NULL, &background_playing);
    }

    player->render(renderer);
    for (auto &enemy : enemies) enemy->render(renderer);

    int mouse_x, mouse_y;
    SDL_GetMouseState(&mouse_x, &mouse_y);

    for (auto& button : buttons) 
    {
        button.render(renderer, mouse_x, mouse_y, false, -1);
    }

    render_for_buttons(renderer, score, time_seconds);

    Uint32 current_time = SDL_GetTicks();

    if (current_time - last_time >= 1000) 
    {
        time_seconds++;
        last_time = current_time;
    }

    return;
}

void Game_Playing::clean()
{
    if (player)
    {
        delete player;
        player = nullptr;
    }

    for (auto &enemy : enemies)
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

    if (font1)
    {
        TTF_CloseFont(font1);
        font1 = nullptr;
    }

    if (font2)
    {
        TTF_CloseFont(font2);
        font2 = nullptr;
    }

    buttons.clear();
}
