#include "../include/Game_setting.h"

Game_setting::Game_setting(SDL_Renderer* renderer, int x, int y, int w, int h)
{
    board = new Board(renderer, x, y, w, h, 1);

    int button_w = w - 60;
    int button_h = 40;
    int spacing = 15;
    int start_y = y + 60;

    const char* labels[] = {"Resume", "Sound", "Instruction", "Menu", "Exit"};

    int num_buttons = sizeof(labels) / sizeof(labels[0]);

    for (int i = 0; i < num_buttons; ++i)
    {
        Button button(x + 30, start_y + i * (button_h + spacing), button_w, button_h, labels[i]);
        buttons.push_back(button);
    }
}

void Game_setting::clean()
{
    delete board;
}

void Game_setting::set_font(TTF_Font* font)
{
    board->set_text({"SETTING"});
    for (auto& button : buttons)
        button.set_font(font);
}

void Game_setting::render(bool draw_transparent)
{
    board->render(draw_transparent);
    
    // Render buttons
    int mouse_x, mouse_y;
    SDL_GetMouseState(&mouse_x, &mouse_y);
    for (auto& button : buttons)
        button.render(board->get_renderer(), mouse_x, mouse_y, false);
}

void Game_setting::handle_event(SDL_Event& event)
{
    if (!board->is_active()) return;
    board->handle_event();
}
