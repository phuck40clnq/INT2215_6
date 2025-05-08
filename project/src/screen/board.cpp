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
    name_font = name;
    close_button.set_font(name);
}

void Board::set_text(std::vector<const char*> texts, SDL_Color text_color)
{
    this->text_color = text_color;
    this->lines = texts;
}

void Board::render(bool draw_transparent, SDL_Color color)
{
    if (!active) return;

    if (draw_transparent)   this->draw_transparent();

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &rect);


    if (!font->get_font(name_font) || lines.empty()) return;
    int line_height = TTF_FontHeight(font->get_font(name_font));
    int line_spacing = text_rect.y;

    for (int i = 0, l = lines.size(); i < l; i++) 
    {
        if (i == 0)
        {
            render_text(renderer, lines[i], text_rect.x, line_spacing, font->get_font(name_font), 0, text_color, true);
            line_spacing += line_height + 5;
            continue;
        }
        render_text(renderer, lines[i], text_rect.x, line_spacing, font->get_font(name_font), 0, text_color);
        line_spacing += line_height + 5;
    }

    close_button.render(renderer, -1, -1, false, 0, {200, 200, 200, 255});

    // Render buttons
    int mouse_x, mouse_y;
    SDL_GetMouseState(&mouse_x, &mouse_y);
    for (auto& button : buttons)
    {
        button.render(renderer, mouse_x, mouse_y, true);
    }

    // Set render again
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

void Board::draw_transparent()
{
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 120);
    SDL_RenderFillRect(renderer, nullptr);

    // Set render again
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

void Board::handle_event(SDL_Event& event)
{
    if (!active) return;
    handle_close_button_click(event);
    handle_button_click(event);
}

void Board::handle_close_button_click(SDL_Event& event)
{
    if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) 
    {
        int x = event.button.x;
        int y = event.button.y;

        if (close_button.is_touch(x, y))
        {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Close button clicked");
            music->playsound("click_button", 2, false);
            active = false;
        }
    }
}

void Board::handle_button_click(SDL_Event& event)
{
    if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) 
    {
        int x, y;
        SDL_GetMouseState(&x, &y);

        for (auto& button : buttons)
        {
            if (!button.is_touch(x, y)) continue;
            music->playsound("click_button", 2, false);
            if (button_callback)
            {
                button_callback(button.get_text());
            }
        }
    }
}

void Board::clean()
{}

void Board::add_button(const char* text, float fx, float fy, float button_x_offset, float button_y_offset, float button_spacing, float button_width, float button_height)
{
    if (fx == 0.f && fy == 0.f)
    {
        fx = button_x_offset + 550;
        fy = button_y_offset + button_count * (button_height + button_spacing) + 100;
    }
    
    Button button(font, fx, fy, button_width, button_height, text);
    button.set_font(name_font);
    buttons.push_back(button);

    button_count++;
}