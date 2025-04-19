#include "../include/board.h"
#include "../include/Game_state.h"

Board::Board(SDL_Renderer* renderer, int x, int y, int w, int h, int key) : rect{x, y, w, h}, close_button(rect.x + rect.w - 30, rect.y + 5, 25, 25, "X")
{
    this->renderer = renderer;
    this->active = true;
    this->text_rect = {rect.x + 10, rect.y + 10, rect.w - 20, rect.h - 20};
    this->text_color = {255, 255, 255, 255}; // White

    if (key == 1)   font = TTF_OpenFont("../font/font1.ttf", 20);
    else if (key == 2)  font = TTF_OpenFont("../font/font2.ttf", 20);
    else if (key == 3)  font = TTF_OpenFont("../font/font3.ttf", 20);

    if (font == NULL)
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "TTF_OpenFont instruction failed: %s", TTF_GetError());
        return;
    }

    close_button.set_font(this->font);

    // this->close_button = Button(rect.x + rect.w - 30, rect.y + 5, 25, 25, "X");
}

void Board::set_text(std::vector<const char*> texts, SDL_Color color)
{
    this->text_color = color;
    this->lines = texts;


}

void Board::render(bool draw_transparent)
{
    if (!active) return;

    if (draw_transparent)   this->draw_transparent();

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black
    SDL_RenderFillRect(renderer, &rect);


    if (!font || lines.empty()) return;
    int line_height = TTF_FontHeight(font);
    int line_spacing = text_rect.y;

    for (auto& line : lines) 
    {
        render_text(renderer, line, text_rect.x, line_spacing, font, 0, text_color);
        line_spacing += line_height + 5;
    }

    close_button.render(renderer, -1, -1, false);

    // Set render again
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

void Board::draw_transparent()
{
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 128);
    SDL_RenderFillRect(renderer, nullptr);

    // Set render again
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

void Board::handle_event()
{
    if (!active) return;

    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT) set_running(false);
        if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) 
        {
            int x = event.button.x;
            int y = event.button.y;
            if (close_button.is_touch(x, y))  set_state(MENU);
        }
    }
}

void Board::clean()
{
    if (font)
    {
        TTF_CloseFont(font);
        font = nullptr;
    }
}