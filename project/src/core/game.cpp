#include "../include/game.h"

// ---Initialize---
Game::Game()
{
    this->window = NULL;
    this->renderer = NULL;
    this->game = nullptr;
    this->menu = nullptr;
    this->gameover = nullptr;
}

void Game::set_setting_button()
{
    setting->add_button("Resume", 0, 0, 10, 10, 5, 150, 50);
    setting->add_button("Mute", 0, 0, 10, 10, 5, 150, 50);
    setting->add_button("Unmute", 0, 0, 10, 10, 5, 150, 50);
    setting->add_button("Restart", 0, 0, 10, 10, 5, 150, 50);

    setting->add_button("MENU", 100, 480);
    setting->add_button("GAME", 350, 480);
    setting->add_button("END", 600, 480);
}

void Game::set_quit_button()
{
    quit->add_button("YES", 500, 200, 10, 10, 5, 150, 50);
    quit->add_button("NO", 200, 200, 10, 10, 5, 150, 50);
}

void Game::handle_setting_button(const char* text)
{
    if (strcmp(text, "Mute") == 0)
    {
        music.mute();
    }
    else if (strcmp(text, "Unmute") == 0)
    {
        music.unmute();
    }
    else if (strcmp(text, "Resume") == 0)
    {
        setting->set_active(false);
        pop_overlay(); // Pop overlay
    }
    else if (strcmp(text, "Restart") == 0)
    {
        if (instruction->is_active())
            instruction->set_active(false);

        if (setting->is_active())
            setting->set_active(false);

        set_overlay(OVERLAY::NONE);

        restart_game();
        set_state(GAME_STATE::PLAYING);
    }
    else if (strcmp(text, "MENU") == 0)
    {
        set_overlay(OVERLAY::NONE);
        set_state(GAME_STATE::MENU);
    }
    else if (strcmp(text, "GAME") == 0)
    {
        set_overlay(OVERLAY::NONE);
        set_state(GAME_STATE::PLAYING);
    }
    else if (strcmp(text, "END") == 0)
    {
        set_overlay(OVERLAY::NONE);
        set_state(GAME_STATE::GAME_OVER);
    }
    return;
}

void Game::handle_quit_button(const char* text)
{

    if (strcmp(text, "YES") == 0)
    {
        set_running(false);
    }
    else if (strcmp(text, "NO") == 0)
    {
        quit->set_active(false);
        pop_overlay(); // Pop overlay
    }
    return;
}

bool Game::init(const char* title, int width, int height)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "SDL_Init failed: %s", SDL_GetError());
        return false;
    }

    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "SDL_CreateWindow failed: %s", SDL_GetError());
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "SDL_CreateRenderer failed: %s", SDL_GetError());
        return false;
    }

    texture = Texture(renderer);
    if (!texture.init())
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "IMG_Init failed: %s", IMG_GetError());
        return false;
    }

    // ---Init audio---
    if (!music.init())
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Music init failed: %s", Mix_GetError());
        return false;
    }

    if (!font.init())
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "TTF_Init failed: %s", TTF_GetError());
        return false;
    }

    // ---Load texture---
    texture.loadtexture("background_menu", "../images/background_menu.jpg");
    texture.loadtexture("background_playing", "../images/background_game.jpg");
    texture.loadtexture("background_gameover", "../images/background_gameover.png");

    // ---Load music---
    music.loadmusic("background_menu", "../music/background/Exotics.mp3");
    music.loadmusic("background_playing", "../music/background/Interstellar.mp3");
    music.loadmusic("background_gameover", "../music/background/Jesu.mp3");

    music.setvolume_music(30);
    music.setvolume(45, "background_playing");
    music.setvolume_sound(10);

    // ---Load font---
    font.loadfont("font1_80", "../font/font1.ttf", 80, { 0, 0, 0, 255 });
    font.loadfont("font1", "../font/font1.ttf", 30, { 0, 0, 0, 255 });
    font.loadfont("font2", "../font/font2.ttf", 30, { 0, 0, 0, 255 });
    font.loadfont("font3", "../font/font3.ttf", 30, { 0, 0, 0, 255 });
    font.loadfont("font4", "../font/font4.ttf", 30, { 0, 0, 0, 255 });
    font.loadfont("font5", "../font/font5.ttf", 30, { 0, 0, 0, 255 });
    font.loadfont("font6", "../font/font6.ttf", 30, { 0, 0, 0, 255 });
    font.loadfont("font7", "../font/font7.ttf", 30, { 0, 0, 0, 255 });
    font.loadfont("font8", "../font/font8.ttf", 40, { 0, 0, 0, 255 });

    font.loadfont("font5_35", "../font/font5.ttf", 35, { 0, 0, 0, 255 });
    font.loadfont("font6_80", "../font/font6.ttf", 150, { 100, 100, 100, 255 });

    
    this->instruction = new Board(&music, &font, renderer, 80, 60, 640, 480);
    instruction->set_font("font8");
    instruction->set_text({
        "INSTRUCTION",
        "1, Press Arrow keys to move.",
        "2, Press 'SPACE' to shoot.",
        "3, Press 'M' to mute/unmute the music.",
        "4, Press 'I' to show/hide the instruction.",
        "5, Press 'P' to pause the game.",
        "6, Press 'R' to restart the game.",
        "7, Press 'ESC' to exit.",
    });
    this->setting = new Board(&music, &font, renderer, 80, 60, 640, 480);
    setting->set_font("font5_35");
    setting->set_text({
        "PAUSE",
        "1. Press 'M' to mute/unmute the music.",
        "2. Press 'I' to show/hide the instruction.",
        "3. Press 'P' to pause the game.",
        "4. Press 'R' to restart the game.",
        "5. Press 'ESC' to exit.",
        " ",
        " ",
        "Comeback any state if you want."
    });
    set_setting_button();
    this->setting->set_button_callback([this](const char* text)
    {
        handle_setting_button(text);
    });

    this->quit = new Board(&music, &font, renderer, 50, 100, 700, 200);
    quit->set_font("font2");
    quit->set_text({
        "Do you really want to quit?",
    });
    set_quit_button();
    this->quit->set_button_callback([this](const char* text)
    {
        handle_quit_button(text);
    });


    // ---Success---
    set_running(true);
    SDL_Log("Game khởi động thành công!");
    return true;
}

// ---Running game---
void Game::handle_event()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            set_running(false);
            return;
        }
        if (event.type == SDL_KEYDOWN && !event.key.repeat)
        {
            // Muted/Unmuted
            if (event.key.keysym.sym == SDLK_m)
            {
                if (music.ismuted())
                    music.unmute();
                else
                    music.mute();
            }
            
            // Restart
            else if (event.key.keysym.sym == SDLK_r)
            {
                reset_game = true;
            }
        }
        else if (event.type == SDL_KEYUP)
        {
            if (event.key.keysym.sym == SDLK_r)
            {
                reset_game = false;
            }
        }

        handle_state(get_state(), event);
        handle_overlay(get_overlay(), event);
    }
}

void Game::handle_reset_game()
{
    if (!reset_game)    return;

    if (instruction->is_active())
        instruction->set_active(false);

    if (setting->is_active())
        setting->set_active(false);

    if (quit->is_active())
        quit->set_active(false);

    set_overlay(OVERLAY::NONE);

    restart_game();
    set_state(GAME_STATE::PLAYING);

    reset_game = false;
}

void Game::handle_state(GAME_STATE state, SDL_Event& event)
{
    if (get_state() == GAME_STATE::MENU)
    {
        new_menu();
        menu->handle_event(event);
    }
    else if (get_state() == GAME_STATE::PLAYING)
    {
        new_game();
        game->handle_event(event);
    }
    else if (get_state() == GAME_STATE::GAME_OVER)
    {
        new_gameover();
        gameover->handle_event(event);
    }
}

void Game::handle_overlay(OVERLAY overlay, SDL_Event& event)
{
    if (get_overlay() == OVERLAY::INSTRUCTION)
    {
        if (instruction->is_active())
        {
            instruction->handle_event(event);
        }
    }
    else if (get_overlay() == OVERLAY::PAUSE)
    {
        if (setting->is_active())
        {
            setting->handle_event(event);
        }
    }
    else if (get_overlay() == OVERLAY::QUIT)
    {
        if (quit->is_active())
        {
            quit->handle_event(event);
        }
    }
}

// ---Update game---
void Game::update()
{
    handle_reset_game();
    if (get_state() == GAME_STATE::PLAYING && game)
        game->update();
    if (get_state() == GAME_STATE::GAME_OVER && gameover)
        gameover->update();
}

// ---Renderer---
void Game::render()
{
    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
    SDL_RenderClear(renderer);

    render_state(get_state());
    render_overlay(get_overlay());

    SDL_RenderPresent(renderer);
}

void Game::render_state(GAME_STATE state)
{
    if (state == GAME_STATE::MENU)
    {
        new_menu();
        menu->render();
    }
    else if (state == GAME_STATE::PLAYING)
    {
        new_game();
        game->render();
    }
    else if (state == GAME_STATE::GAME_OVER)
    {
        new_gameover();
        gameover->render();
    }
}

void Game::render_overlay(OVERLAY overlay)
{
    if (overlay == OVERLAY::INSTRUCTION)
    {
        if (instruction->is_active())
        {
            instruction->render(false);
        }
    }
    else if (overlay == OVERLAY::PAUSE)
    {
        if (setting->is_active())
        {
            setting->render(true);
        }
    }
    else if (overlay == OVERLAY::QUIT)
    {
        if (quit->is_active())
        {
            quit->render(true);
        }
    }
}

// ---Clean screen for each case---
void Game::new_menu()
{
    if (menu == nullptr)
    {
        menu = new Game_Menu(renderer, &music, &font, &texture, instruction, setting, quit);
        music.stop_all();
        music.playmusic("background_menu", true);
    }
    if (game)
    {
        game->clean();
        game = nullptr;
    }
    if (gameover)
    {
        gameover->clean();
        gameover = nullptr;
    }
}

void Game::new_game()
{

    if (game == nullptr)
    {
        game = new Game_Playing(renderer, &music, &font, &texture, instruction, setting, quit);
        music.stop_all();
        music.playmusic("background_playing", true);
    }
    if (menu)
    {
        menu->clean();
        menu = nullptr;
    }
    if (gameover)
    {
        gameover->clean();
        gameover = nullptr;
    }
}

void Game::new_gameover()
{
    if (gameover == nullptr)
    {
        gameover = new Game_Gameover(renderer, &music, &font, &texture, instruction, setting, quit);
        music.stop_all();
        music.playmusic("background_gameover", true);
    }
    if (menu)
    {
        menu->clean();
        menu = nullptr;
    }
    if (game)
    {
        game->clean();
        game = nullptr;
    }
}

void Game::restart_game()
{
    if (game)
    {
        game->clean();
        delete game;
        game = nullptr;
    }

    game = new Game_Playing(renderer, &music, &font, &texture, instruction, setting, quit);
    music.stop_all();
    music.playmusic("background_playing", true);

    if (menu)
    {
        menu->clean();
        delete menu;
        menu = nullptr;
    }

    if (gameover)
    {
        gameover->clean();
        delete gameover;
        gameover = nullptr;
    }
}

// ---Handle fps---
void Game::start_frame()
{
    frame_start = SDL_GetTicks();
}

void Game::end_frame()
{
    unsigned frame_time = SDL_GetTicks() - frame_start;
    int frame_delay = 1000 / fps;

    if (frame_time < frame_delay)
    {
        SDL_Delay(frame_delay - frame_time);
    }
}

// ---Clean game---
void Game::clean()
{
    if (renderer)   SDL_DestroyRenderer(renderer);
    if (window)     SDL_DestroyWindow(window);

    clean_data();
    
    texture.clean();
    music.clean();
    font.clean();

    SDL_Quit();
    return;
}

void Game::clean_data()
{
    if (menu)
    {
        menu->clean();
        delete menu;
        menu = nullptr;
    }
    if (game)
    {
        game->clean();
        delete game;
        game = nullptr;
    }
    if (gameover)
    {
        gameover->clean();
        delete gameover;
        gameover = nullptr;
    }
    if (instruction)
    {
        instruction->clean();
        delete instruction;
        instruction = nullptr;
    }
    if (setting)
    {
        setting->clean();
        delete setting;
        setting = nullptr;
    }
    if (quit)
    {
        quit->clean();
        delete quit;
        quit = nullptr;
    }
}