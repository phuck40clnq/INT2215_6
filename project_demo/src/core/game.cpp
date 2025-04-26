#include "../include/game.h"

// ---Initialize---
Game::Game()
{ 
    this->window = NULL;
    this->renderer = NULL;
    this->game = nullptr;
    this->menu = nullptr;
    this->gameover = nullptr;
    // this->pause = nullptr;
}

bool Game::init(const char* title, int width, int height)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "SDL_Init failed: %s", SDL_GetError());
        return false;
    }

    if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) == 0)
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "IMG_Init failed: %s", IMG_GetError());
        return false;
    }

    if (!font.init())
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "TTF_Init failed: %s", TTF_GetError());
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

    // ---Init audio---
    if (!music.init())
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Music init failed: %s", Mix_GetError());
        return false;
    }

    // ---Load music---
    music.loadmusic("background_menu", "../music/background/Exotics.mp3");
    music.loadmusic("background_playing", "../music/background/Interstellar.mp3");
    music.loadmusic("background_gameover", "../music/background/Jesu.mp3");

    music.setvolume(50);

    // ---Load font---
    font.loadfont("font1", "../font/font1.ttf", 30, { 0, 0, 0, 255 });
    font.loadfont("font2", "../font/font2.ttf", 50, { 0, 0, 0, 255 });
    font.loadfont("font3", "../font/font3.ttf", 50, { 0, 0, 0, 255 });

    this->instruction = new Board(&music, &font, renderer, 40, 30, 720, 540);
    instruction->set_font("font1");
    instruction->set_text({
        "INSTRUCTION",
        "1. Press 'ESC' to exit the game.",
        "2. Press Arrow keys to move.",
        "3. Press 'SPACE' to shoot.",
        "4. Press 'P' to pause the game.",
        "5. Press 'R' to restart the game.",
    });
    this->pause = new Board(&music, &font, renderer, 80, 60, 640, 480);
    pause->set_font("font1");
    pause->set_text({
        "PAUSE",
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
        if (get_overlay() == OVERLAY::INSTRUCTION)
        {
            if (instruction->is_active())
            {
                instruction->handle_event(event);
            }
        }
        if (get_overlay() == OVERLAY::PAUSE)
        {
            if (pause->is_active())
            {
                pause->handle_event(event);
            }
        }
    }
}

// ---Update game---
void Game::update()
{
    if (get_state() == GAME_STATE::PLAYING && game)
        game->update();
}

// ---Renderer---
void Game::render()
{
    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
    SDL_RenderClear(renderer);

    if (get_state() == GAME_STATE::MENU)
    {
        new_menu();
        menu->render();
    }
    else if (get_state() == GAME_STATE::PLAYING)
    {
        new_game();
        game->render();
    }
    else if (get_state() == GAME_STATE::GAME_OVER)
    {
        new_gameover();
        gameover->render();
    }
    if (get_overlay() == OVERLAY::INSTRUCTION)
    {
        if (instruction->is_active())
        {
            instruction->render(true);
        }
        else
            set_state(get_previous_state());
    }
    if (get_overlay() == OVERLAY::PAUSE)
    {
        if (pause->is_active())
        {
            pause->render(true);
        }
        else
            set_state(get_previous_state());
    }

    SDL_RenderPresent(renderer);
}

// ---Clean screen for each case---
void Game::new_menu()
{
    if (menu == nullptr)
    {
        menu = new Game_Menu(renderer, &music, &font, instruction, pause);
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
        game = new Game_Playing(renderer, &music, &font, instruction, pause);
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
        gameover = new Game_Gameover(renderer, &music, &font, instruction, pause);
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
    
    music.clean();
    font.clean();

    IMG_Quit();
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
    if (pause)
    {
        pause->clean();
        delete pause;
        pause = nullptr;
    }
}