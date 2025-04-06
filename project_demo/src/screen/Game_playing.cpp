#include "../include/Game_playing.h"
#include <SDL2/SDL_image.h>

#include "../func/handle_collision.h"

void Game_Playing::create_buttons()
{
    // buttons.push_back(Button(300, 200, 200, 50, "Play"));
    // buttons.push_back(Button(300, 300, 200, 50, "Quit"));
    for (auto& button : buttons) 
        button.set_font(font);
}

void Game_Playing::init(SDL_Renderer* renderer)
{
    // Load music
    // if (!music.loadmusic("background", "../music/background.mp3"))   return;
    if (!music.loadsound("shoot", "../music/gun_shoot.wav"))    return;
    // if (!music.loadsound("explosion", "../music/explosion.mp3")) return;

    music.setvolume();

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

    for (int i = 0; i < 6; i++)
    {
        Enemy *enemy = new Enemy(enemy_texture, 800, 100*i);
        if (enemy == NULL)
        {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Không thể tạo enemy!\n");
            return;
        }
        enemies.push_back(enemy);
    }

    // Load background
    background = IMG_LoadTexture(renderer, "../images/background.jpg");
    if (background == NULL)
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
    //if (background)
    // {
        SDL_Rect background_playing = {0, 0, 800, 600};
        SDL_RenderCopy(renderer, background, NULL, &background_playing);
        // SDL_RenderCopy(renderer, background, NULL, NULL);
    // }

    player->render(renderer);
    for (auto &enemy : enemies) enemy->render(renderer);

    return;
}

void Game_Playing::clean()
{
    if (player)
    {
        delete player;
        player = nullptr;
    }

    // Destroy IMGs
    if (player_texture) SDL_DestroyTexture(player_texture);
    if (enemy_texture)  SDL_DestroyTexture(enemy_texture);
    if (background) SDL_DestroyTexture(background);
    for (auto &enemy : enemies)
    {
        if (enemy)  delete enemy;
        enemy = nullptr;
    }

    if (font != nullptr) TTF_CloseFont(font);

    buttons.clear();
}
