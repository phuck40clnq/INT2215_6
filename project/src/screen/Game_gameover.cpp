#include "../include/Game_gameover.h"
#include <cstring>

Game_Gameover::Game_Gameover(SDL_Renderer* renderer, Music* music, Font* font, Texture* texture, Board* instruction, Board* setting, Board* quit)
{ 
    this->renderer = renderer;
    this->music = music;
    this->font = font;
    this->texture = texture;
    this->instruction = instruction;
    this->setting = setting;
    this->quit = quit;
    init(); 
    create_buttons(); 
}

void Game_Gameover::init()
{
    // Load Texture
    texture->loadtexture("texture_pause", "../images/setting_button.png");

    // Load music
    music->loadsound("click_button", "../music/sound_effect/click.wav");
    return;
}

void Game_Gameover::create_buttons()
{
    buttons.push_back(Button(font, 300, 100, 200, 50, "Menu"));
    buttons.push_back(Button(font, 300, 200, 200, 50, "Retry"));
    buttons.push_back(Button(font, 300, 300, 200, 50, "Instruction"));
    buttons.push_back(Button(font, 300, 400, 200, 50, "Exit"));

    for (auto& button : buttons) 
        button.set_font("font3");
}

// ---Handle event---
void Game_Gameover::handle_event(SDL_Event& event)
{
    handle_overlay(event);

    if (get_overlay() == OVERLAY::PAUSE || get_overlay() == OVERLAY::INSTRUCTION || get_overlay() == OVERLAY::QUIT)    return;
    handle_click(event);
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
    // else if (strcmp(button.get_text(), "Setting") == 0)
    // {
    //     set_overlay(OVERLAY::PAUSE);
    //     setting->set_active(true);
    // }
    else if (strcmp(button.get_text(), "Exit") == 0)
    {
        set_overlay(OVERLAY::QUIT);
        quit->set_active(true);
    }
}

void Game_Gameover::handle_click(SDL_Event& event)
{
    if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
    {
        int x, y;
        SDL_GetMouseState(&x, &y);

        for (auto& button : buttons)
        {
            if (!button.is_touch(x, y)) continue;
            music->playsound("click_button", 2, false);
            handle_button_click(button);
        }

        SDL_FRect pause_rect = {760, 0, 40, 40};
        if (texture->is_touch(x, y, pause_rect))
        {
            music->playsound("click_button", 2, false);
            set_overlay(OVERLAY::PAUSE);
            setting->set_active(true);
        }
    }
}

// ---Overlay---
void Game_Gameover::handle_overlay(SDL_Event& event)
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
    if (!quit->is_active() && get_overlay() == OVERLAY::QUIT)
    {
        quit->set_active(false);
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
        else if (event.key.keysym.sym == SDLK_ESCAPE)
        {
            toggle_overlay(OVERLAY::QUIT, quit); // Toggle QUIT
        }
    }
}

void Game_Gameover::toggle_overlay(OVERLAY overlay, Board* board)
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

// ---Update---
void Game_Gameover::update()
{
    background_x -= background_speed;
    if (background_x <= -800.f) background_x = 0.f;

    return;
}

// ---Render---
void Game_Gameover::render()
{
    // SDL_FRect tmp = {0, 0, 800, 600};
    // SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
    // SDL_RenderFillRect(renderer, &tmp);

    SDL_FRect background_gameover1 = {background_x, 0, 800, 600};
    SDL_FRect background_gameover2 = {background_x + 800, 0, 800, 600};
    SDL_FRect pause_rect = { 760, 0, 40, 40 };

    texture->render("background_gameover", background_gameover1, {255, 255, 255, 255}, false, false);
    texture->render("background_gameover", background_gameover2, {255, 255, 255, 255}, false, false);

    texture->render("texture_pause", pause_rect, { 255, 255, 255, 128 }, true, true);

    int mouse_x, mouse_y;
    SDL_GetMouseState(&mouse_x, &mouse_y);

    for (auto& button : buttons) 
    {
        button.render(renderer, mouse_x, mouse_y);
    }
}

void Game_Gameover::clean()
{
    buttons.clear();
}