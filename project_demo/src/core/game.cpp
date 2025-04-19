#include "../include/game.h"

// Initialize
Game::Game()
{ 
    this->window = NULL;
    this->renderer = NULL;
    this->game = nullptr;
    this->menu = nullptr;
    this->gameover = nullptr;
    this->instruction = nullptr;
    // this->setting = nullptr;
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

    if (TTF_Init() == -1)
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

    // Init audio
    if (!music.init())
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Music init failed: %s", Mix_GetError());
        return false;
    }

    // Load music
    music.loadmusic("background_menu", "../music/background/Exotics.mp3");
    music.loadmusic("background_playing", "../music/background/Interstellar.mp3");
    music.loadmusic("background_gameover", "../music/background/Exotics.mp3");


    // Success
    set_running(true);
    SDL_Log("Game khởi động thành công!");
    return true;
}

// Running game
void Game::handle_event()
{
    if (get_state() == MENU)
    {
        new_menu();
        menu->handle_event();
    }
    else if (get_state() == SETTING)
    {
        return;
    }
    else if (get_state() == INSTRUCTION)
    {
        new_instruction();
        instruction->handle_event();
    }
    else if (get_state() == PLAYING)
    {
        new_game();
        game->handle_event();
    }
    else if (get_state() == GAME_OVER)
    {
        new_gameover();
        gameover->handle_event();
    }
}

// Update game
void Game::update()
{
    if (get_state() == PLAYING && game)
        game->update();
}

// Renderer
void Game::render()
{
    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
    SDL_RenderClear(renderer);

    if (get_state() == MENU)
    {
        new_menu();
        menu->render(renderer);
    }
    else if (get_state() == SETTING)
    {
        return;
    }
    else if (get_state() == INSTRUCTION)
    {
        new_instruction();
        instruction->render();
    }
    else if (get_state() == PLAYING)
    {
        new_game();
        game->render(renderer);
    }
    else if (get_state() == GAME_OVER)
    {
        new_gameover();
        gameover->render(renderer);
    }

    SDL_RenderPresent(renderer);
}

// Clean screen for each case
void Game::new_menu()
{
    if (menu == nullptr)
    {
        menu = new Game_Menu(renderer, &music);
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
    if (instruction)
    {
        instruction->clean();
        delete instruction;
        instruction = nullptr;
    }
}

void Game::new_game()
{

    if (game == nullptr)
    {
        game = new Game_Playing(renderer, &music);
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
    if (instruction)
    {
        instruction->clean();
        delete instruction;
        instruction = nullptr;
    }
}

void Game::new_gameover()
{
    if (gameover == nullptr)
    {
        gameover = new Game_Gameover(renderer, &music);
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
    if (instruction)
    {
        instruction->clean();
        delete instruction;
        instruction = nullptr;
    }
}

void Game::new_instruction()
{
    if (instruction == nullptr)    instruction = new Board(renderer, SCREEN_WIDTH / 2 - 360, SCREEN_HEIGHT / 2 - 270, 720, 540, 2);

    instruction->set_text({
        "INSTRUCTION",
        "1. Nhấn phím mũi tên lên/xuống, trái/phải để di chuyển",
        "2. Nhấn phím Space để bắn",
    });

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
    if (gameover)
    {
        gameover->clean();
        gameover = nullptr;
    }
}

// Handle fps
void Game::maintain_FPS()
{
    unsigned frame_start = SDL_GetTicks();

    int frame_time = SDL_GetTicks() - frame_start;
    int frame_delay = 1000 / fps;

    if (frame_time < frame_delay)
    {
        SDL_Delay(frame_delay - frame_time);
    }
}

// Clean game
void Game::clean()
{
    if (renderer)   SDL_DestroyRenderer(renderer);
    if (window)     SDL_DestroyWindow(window);

    clean_data();
    
    music.clean();

    Mix_Quit();
    IMG_Quit();
    TTF_Quit();
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
}