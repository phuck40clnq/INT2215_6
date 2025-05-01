#include "../include/Game_menu.h"
#include "../include/Game_state.h"
#include "../include/render.h"

#include <cstring>



Game_Menu::Game_Menu(SDL_Renderer* renderer, Music* music, Font* font, Texture* texture, Board* instruction, Board* setting)
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

void Game_Menu::init()
{
    // Load Texture

    // Load music
    music->loadsound("click_button", "../music/sound_effect/soft_click.wav");

    return;
}

void Game_Menu::create_buttons()
{
    buttons.push_back(Button(font, 300, 270, 200, 50, "Play"));
    buttons.push_back(Button(font, 300, 350, 200, 50, "Instruction"));
    buttons.push_back(Button(font, 300, 430, 200, 50, "Setting"));
    buttons.push_back(Button(font, 300, 510, 200, 50, "Exit"));
    for (auto& button : buttons) 
        button.set_font("font1");
}

void Game_Menu::handle_event(SDL_Event& event)
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

void Game_Menu::handle_button_click(Button& button)
{
    if (strcmp(button.get_text(), "Play") == 0) set_state(GAME_STATE::PLAYING);
    else if (strcmp(button.get_text(), "Instruction") == 0)
    {
        set_overlay(OVERLAY::INSTRUCTION);
        if (instruction)
            instruction->set_active(true);
    }
    else if (strcmp(button.get_text(), "Setting") == 0)
    {
        set_state(GAME_STATE::SETTING);
        if (setting)
            setting->set_active(true);
    }
    else if (strcmp(button.get_text(), "Exit") == 0) set_running(false);
}

void Game_Menu::render()
{
    // SDL_Rect tmp = {0, 0, 800, 600};
    // SDL_SetRenderDrawColor(renderer, 245, 245, 220, 255);   // Light beige
    // SDL_RenderFillRect(renderer, &tmp);
    SDL_FRect background_menu = {0, 0, 800, 600};
    texture->render("background_menu", background_menu, {255, 255, 255, 255}, false, false);

    render_text(renderer, "WELCOME", 200, 130, font->get_font("font1"));

    int mouse_x, mouse_y;
    SDL_GetMouseState(&mouse_x, &mouse_y);

    for (auto& button : buttons) 
    {
        button.render(renderer, mouse_x, mouse_y);
    }
}

void Game_Menu::clean()
{
    buttons.clear();
}