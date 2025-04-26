#include "../include/Game_gameover.h"
#include "../include/Game_state.h"

#include <cstring>

#include "../func/render.h"

Game_Gameover::Game_Gameover(SDL_Renderer* renderer, Music* music, Font* font, Board* instruction, Board* setting)
{ 
    this->renderer = renderer;
    this->music = music;
    this->font = font;
    this->instruction = instruction;
    this->setting = setting;
    init(); 
    create_buttons(); 
}

void Game_Gameover::init()
{
    // Load music
    music->loadsound("click_button", "../music/sound_effect/click.wav");

    // Load background
    texture = IMG_LoadTexture(renderer, "../images/background_gameover.png");
    if (texture == NULL)
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "IMG_LoadTexture background failed: %s", IMG_GetError());
        return;
    }

    return;
}

void Game_Gameover::create_buttons()
{
    buttons.push_back(Button(font, 300, 100, 200, 50, "Menu"));
    buttons.push_back(Button(font, 300, 200, 200, 50, "Retry"));
    buttons.push_back(Button(font, 300, 300, 200, 50, "Instruction"));
    buttons.push_back(Button(font, 300, 400, 200, 50, "Exit"));

    for (auto& button : buttons) 
        button.set_font("font1");
}

void Game_Gameover::handle_event(SDL_Event& event)
{
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
    }
}

void Game_Gameover::handle_button_click(Button& button)
{
    if (strcmp(button.get_text(), "Menu") == 0) set_state(GAME_STATE::MENU);
    else if (strcmp(button.get_text(), "Retry") == 0) set_state(GAME_STATE::PLAYING);
    else if (strcmp(button.get_text(), "Instruction") == 0)
    {
        set_overlay(OVERLAY::INSTRUCTION);
        instruction->set_active(true);
    }
    else if (strcmp(button.get_text(), "Setting") == 0)
    {
        set_state(GAME_STATE::SETTING);
        setting->set_active(true);
    }
    else if (strcmp(button.get_text(), "Exit") == 0) set_running(false);
}

void Game_Gameover::render()
{
    // SDL_Rect tmp = {0, 0, 800, 600};
    // SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
    // SDL_RenderFillRect(renderer, &tmp);

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

    buttons.clear();
}