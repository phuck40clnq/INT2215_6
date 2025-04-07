#include "../include/Game_gameover.h"
#include "../include/Game_state.h"

#include <cstring>

#include "../func/render_text.h"

void Game_Gameover::init(SDL_Renderer* renderer)
{
    // Load music
    // if (!music.loadmusic("background1", "../music/background1.mp3"))   return;
    // if (!music.loadsound("touch_button", "../music/buttontouch.mp3")) return;

    music.setvolume();

    // Load font
    font = TTF_OpenFont("../font/font1.ttf", 35);
    if (font == NULL)
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "TTF_OpenFont font_gameover failed: %s", IMG_GetError());
        return;
    }

    // Load background
    // texture = IMG_LoadTexture(renderer, "../images/background.jpg");
    // if (texture == NULL)
    // {
    //     SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "IMG_LoadTexture background failed: %s", IMG_GetError());
    //     return;
    // }

    return;
}

void Game_Gameover::create_buttons()
{
    buttons.push_back(Button(300, 150, 200, 50, "Menu"));
    buttons.push_back(Button(300, 250, 200, 50, "Retry"));
    buttons.push_back(Button(300, 350, 200, 50, "Exit"));

    if (font)
    {
        for (auto& button : buttons) 
            button.set_font(font);
    }
}

void Game_Gameover::handle_event()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT) set_running(false);

        if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            int x, y;
            SDL_GetMouseState(&x, &y);

            for (auto& button : buttons)
            {
                if (!button.is_touch(x, y)) continue;
                if (strcmp(button.get_text(), "Menu") == 0)    set_state(MENU);
                if (strcmp(button.get_text(), "Retry") == 0)    set_state(PLAYING);
                if (strcmp(button.get_text(), "Exit") == 0)    set_running(false);
            }
        }
    }
}

void Game_Gameover::render(SDL_Renderer* renderer)
{
    SDL_Rect tmp = {0, 0, 800, 600};
    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
    SDL_RenderFillRect(renderer, &tmp);

    if (texture) 
    {
        SDL_Rect background_gameover = {0, 0, 800, 600};
        SDL_RenderCopy(renderer, texture, nullptr, &background_gameover);
    }

    int mouse_x, mouse_y;
    SDL_GetMouseState(&mouse_x, &mouse_y);

    for (auto& button : buttons) 
    {
        button.render(renderer, mouse_x, mouse_y);
    }
}

void Game_Gameover::clean()
{
    if (texture)
    {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
    if (font)
    {
        TTF_CloseFont(font);
        font = nullptr;
    }

    buttons.clear();
}