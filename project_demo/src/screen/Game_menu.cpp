#include "../include/Game_menu.h"
#include "../include/Game_state.h"

#include <cstring>

#include "../func/render_text.h"

void Game_Menu::init(SDL_Renderer* renderer)
{
    // Load music
    // if (!music.loadmusic("background1", "../music/background1.mp3"))   return;
    // if (!music.loadsound("touch_button", "../music/buttontouch.mp3")) return;

    music.setvolume();

    // Load font
    font = TTF_OpenFont("../font/font3.ttf", 30);
    if (font == NULL)
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "TTF_OpenFont font_menu failed: %s", IMG_GetError());
        return;
    }

    welcome_font = TTF_OpenFont("../font/font3.ttf", 100);
    if (welcome_font == NULL)
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "TTF_OpenFont font_menu failed: %s", IMG_GetError());
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

void Game_Menu::create_buttons()
{
    buttons.push_back(Button(300, 270, 200, 50, "Play"));
    buttons.push_back(Button(300, 350, 200, 50, "Instruction"));
    buttons.push_back(Button(300, 420, 200, 50, "Exit"));
    if (font)
    {
        for (auto& button : buttons) 
            button.set_font(font);
    }
}

void Game_Menu::handle_event()
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
                if (strcmp(button.get_text(), "Play") == 0) set_state(PLAYING);
                if (strcmp(button.get_text(), "Exit") == 0) set_running(false);
            }
        }
    }
}

void Game_Menu::render(SDL_Renderer* renderer)
{
    SDL_Rect tmp = {0, 0, 800, 600};
    SDL_SetRenderDrawColor(renderer, 245, 245, 220, 255);   // Light beige
    SDL_RenderFillRect(renderer, &tmp);
    if (texture) 
    {
        SDL_Rect background_menu = {0, 0, 800, 600};
        SDL_RenderCopy(renderer, texture, nullptr, &background_menu);
    }

    render_text(renderer, "WELCOME", 200, 130, welcome_font);

    int mouse_x, mouse_y;
    SDL_GetMouseState(&mouse_x, &mouse_y);

    for (auto& button : buttons) 
    {
        button.render(renderer, mouse_x, mouse_y);
    }

}

void Game_Menu::clean()
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
    if (welcome_font)
    {
        TTF_CloseFont(welcome_font);
        welcome_font = nullptr;
    }

    buttons.clear();
}