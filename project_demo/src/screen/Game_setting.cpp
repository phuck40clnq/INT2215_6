#include "../include/Game_setting.h"
#include "../include/Game_state.h"

#include <cstring>

Game_setting::Game_setting(Music* music, Font* font, SDL_Renderer* renderer, int x, int y, int w, int h)
{
    this->music = music;
    this->font = font;
    this->renderer = renderer;

    music->loadsound("click_button", "../music/sound_effect/soft_click.wav");
    music->loadsound("click_setting_buttons", "../music/sound_effect/click.wav");

    board = new Board(music, font, renderer, x, y, w, h);


    int button_w = w - 60;
    int button_h = 40;
    int spacing = 15;
    int start_y = y + 60;

    const char* labels[] = {"Resume", "Sound", "Instruction", "Menu", "Exit"};

    int num_buttons = sizeof(labels) / sizeof(labels[0]);

    for (int i = 0; i < num_buttons; ++i)
    {
        Button button(font, x + 30, start_y + i * (button_h + spacing), button_w, button_h, labels[i]);
        buttons.push_back(button);
        buttons[i].set_font("font1");
    }

    this->instruction = nullptr;
}

void Game_setting::render(bool draw_transparent)
{
    board->render(draw_transparent);
    
    // Render buttons
    int mouse_x, mouse_y;
    SDL_GetMouseState(&mouse_x, &mouse_y);
    for (auto& button : buttons)
        button.render(renderer, mouse_x, mouse_y, false);
}

// ---Handle event---
void Game_setting::handle_event(SDL_Event& event)
{
    if (!board->is_active()) return;
    board->handle_event(event);

    if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
    {
        int x, y;
        SDL_GetMouseState(&x, &y);

        for (auto& button : buttons)
        {
            if (!button.is_touch(x, y)) continue;
            music->playsound("click_button", 2, false);
            if (strcmp(button.get_text(), "Play") == 0) set_state(GAME_STATE::PLAYING);
            if (strcmp(button.get_text(), "Instruction") == 0) set_overlay(OVERLAY::INSTRUCTION);
            if (strcmp(button.get_text(), "Setting") == 0) set_overlay(OVERLAY::PAUSE);
            if (strcmp(button.get_text(), "Exit") == 0) set_running(false);
        }
    }
}

// ---Clean---
void Game_setting::clean()
{
    if (board)
    {
        board->clean();
        delete board;
        board = nullptr;
    }

    buttons.clear();
}