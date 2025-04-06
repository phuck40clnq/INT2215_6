#include "../include/Game_menu.h"
#include "../include/Game_state.h"

#include <cstring>

void Game_Menu::init(SDL_Renderer* renderer)
{
    // Load music
    // if (!music.loadmusic("background1", "../music/background1.mp3"))   return;
    // if (!music.loadsound("touch_button", "../music/buttontouch.mp3")) return;

    music.setvolume();
    // Load background
    texture = IMG_LoadTexture(renderer, "../images/background.jpg");
    if (texture == NULL)
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "IMG_LoadTexture background failed: %s", IMG_GetError());
        return;
    }

    return;
}

void Game_Menu::create_buttons()
{
    buttons.push_back(Button(300, 200, 200, 50, "Play"));
    buttons.push_back(Button(300, 300, 200, 50, "Exit"));
    for (auto& button : buttons) 
        button.set_font(font);
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

                const char* button_text = button.get_text();

                if (strcmp(button.get_text(), "Play") == 0) set_state(PLAYING);
                if (strcmp(button.get_text(), "Exit") == 0) set_running(false);
            }
        }
    }
}

void Game_Menu::render(SDL_Renderer* renderer)
{
    if (texture) 
    {
        SDL_Rect background_menu = {0, 0, 800, 600};
        SDL_RenderCopy(renderer, texture, nullptr, &background_menu);
    }

    int mouse_x, mouse_y;
    SDL_GetMouseState(&mouse_x, &mouse_y);

    for (auto& button : buttons) 
    {
        button.render(renderer, mouse_x, mouse_y);
    }

}

void Game_Menu::clean()
{
    if (!texture) SDL_DestroyTexture(texture);
    if (font != nullptr) TTF_CloseFont(font);

    buttons.clear();
}