#include "../include/board.h"
#include "../include/Game_state.h"

Board::Board(Music* music, Font* font, SDL_Renderer* renderer, int x, int y, int w, int h) : rect{x, y, w, h}, close_button(font, rect.x + rect.w - 30, rect.y + 5, 25, 25, "X")
{
    this->music = music;
    this->font = font;
    this->renderer = renderer;
    this->active = true;
    this->text_rect = {rect.x + 10, rect.y + 10, rect.w - 20, rect.h - 20};
    this->text_color = {255, 255, 255, 255}; // White

    // this->close_button = Button(rect.x + rect.w - 30, rect.y + 5, 25, 25, "X");
}

void Board::set_font(const char* name)
{
    this->current_font = font->get_font(name);
    close_button.set_font(name);
}

void Board::set_text(std::vector<const char*> texts, SDL_Color text_color)
{
    this->text_color = text_color;
    this->lines = texts;
}

void Board::render(bool draw_transparent)
{
    if (!active) return;

    if (draw_transparent)   this->draw_transparent();

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black
    SDL_RenderFillRect(renderer, &rect);


    if (!current_font || lines.empty()) return;
    int line_height = TTF_FontHeight(current_font);
    int line_spacing = text_rect.y;

    for (auto& line : lines) 
    {
        render_text(renderer, line, text_rect.x, line_spacing, current_font, 0, text_color);
        line_spacing += line_height + 5;
    }

    close_button.render(renderer, -1, -1, true);

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

void Board::handle_event(SDL_Event& event)
{
    if (!active) return;

    if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) 
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Escape key pressed");
        active = false;
    }

    if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) 
    {
        int x = event.button.x;
        int y = event.button.y;

        if (close_button.is_touch(x, y))
        {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Close button clicked");
            music->playsound("click_button", -1, false);
            active = false;
        }
    }
}

void Board::clean()
{}