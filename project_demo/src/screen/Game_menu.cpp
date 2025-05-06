#include "../include/Game_menu.h"
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
    texture->loadtexture("texture_pause", "../images/setting_button.png");

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
        button.set_font("font2");
}

// ---Handle event---
void Game_Menu::handle_event(SDL_Event& event)
{
    handle_click(event);
}

void Game_Menu::handle_button_click(Button& button)
{
    if (strcmp(button.get_text(), "Play") == 0) set_state(GAME_STATE::PLAYING);
    else if (strcmp(button.get_text(), "Instruction") == 0)
    {
        set_overlay(OVERLAY::INSTRUCTION);
        instruction->set_active(true);
    }
    else if (strcmp(button.get_text(), "Setting") == 0)
    {
        set_overlay(OVERLAY::PAUSE);
        setting->set_active(true);
    }
    else if (strcmp(button.get_text(), "Exit") == 0) set_running(false);
}

void Game_Menu::handle_click(SDL_Event& event)
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

// ---Overlay---
void Game_Menu::handle_overlay(SDL_Event& event)
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

void Game_Menu::toggle_overlay(OVERLAY overlay, Board* board)
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

// ---Render---
void Game_Menu::render()
{
    // SDL_Rect tmp = {0, 0, 800, 600};
    // SDL_SetRenderDrawColor(renderer, 245, 245, 220, 255);   // Light beige
    // SDL_RenderFillRect(renderer, &tmp);
    SDL_FRect background_menu = {0, 0, 800, 600};
    SDL_FRect pause_rect = { 760, 0, 40, 40 };

    texture->render("background_menu", background_menu, {255, 255, 255, 255}, false, false);
    texture->render("texture_pause", pause_rect, { 255, 255, 255, 128 }, true, true);

    render_text(renderer, "WELCOME", 200, 130, font->get_font("font1_80"));

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