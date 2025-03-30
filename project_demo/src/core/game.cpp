#include "game.h"

// Initialize
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
    // music.loadmusic("background", "../music/background.mp3");
    music.loadsound("shoot", "../music/gun_shoot.wav");
    // music.loadsound("explosion", "../music/explosion.mp3");

    // For player
    player_texture = IMG_LoadTexture(renderer, "../images/player.png");
    if (!player_texture)
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "LoadTexture player failed: %s", IMG_GetError());
        return false;
    }

    player = new Player(player_texture, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 100, 100, 1);
    if (player == NULL)
    {
        printf("Không thể tạo player!\n");
        return false;
    }

    // For enemy
    enemy_texture = IMG_LoadTexture(renderer, "../images/enemy.png");
    if (!enemy_texture)
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "LoadTexture enemy failed: %s", IMG_GetError());
        return false;
    }

    for (int i = 0; i < max_enemies; i++)
    {
        Enemy *enemy = new Enemy(enemy_texture, 800, 100 * i, 100, 100, 1, 1, 1, 5);
        if (enemy == NULL)
        {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Không thể tạo enemy!\n");
            return false;
        }
        enemies.push_back(enemy);
    }

    // Load background
    background = IMG_LoadTexture(renderer, "../images/background.jpg");
    if (background == NULL)
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "IMG_LoadTexture background failed: %s", IMG_GetError());
        return false;
    }

    // Success
    isRunning = true;
    SDL_Log("Game khởi động thành công!");
    return true;
}

// Running game
void Game::handle_event()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
            isRunning = false;

        player->handle_event(event);
        for (auto &enemy : enemies)
        enemy->handle_event(event);
    }
    handle_collision();
}

    bool Game::check_collision(const SDL_Rect &a, const SDL_Rect &b)
    {
        if (a.x + a.w < b.x || a.x > b.x + b.w || a.y + a.h < b.y || a.y > b.y + b.h)
            return false;
        return true;
    }

    void Game::handle_collision()
    {
        for (auto enemy = enemies.begin(); enemy != enemies.end(); )
        {
            if ((*enemy)->active() && check_collision(player->get_rect(), (*enemy)->get_rect()))
            {
                isRunning = false;
                break;
            }

            auto &bullets = player->get_bullets();
            for (auto bullet = bullets.begin(); bullet != bullets.end(); )
            {
                if (!bullet->active())
                {
                    bullet = bullets.erase(bullet);
                    continue;
                }
                if (check_collision(bullet->get_rect(), (*enemy)->get_rect()))
                {
                    (*enemy)->hp -= 1;
                    SDL_Log("HP: %d", (*enemy)->hp);
                    bullet = bullets.erase(bullet);
                    continue;
                }
                ++bullet;
            }
            if ((*enemy)->hp <= 0)
            {
                delete *enemy;
                enemy = enemies.erase(enemy);
                continue;
            }
            ++enemy;
        }
    }

// Update game
void Game::update_game()
{
    if (player) player->update();
    for (auto &enemy : enemies)
    {
        enemy->update();
    }
    return;
}

// Renderer
void Game::render()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, background, NULL, NULL);

    player->render(renderer);
    for (auto &enemy : enemies) enemy->render(renderer);

    SDL_RenderPresent(renderer);
    return;
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
    if (player)
    {
        delete player;
        player = nullptr;
    }

    // Destroy IMGs
    if (player_texture) SDL_DestroyTexture(player_texture);
    if (enemy_texture)  SDL_DestroyTexture(enemy_texture);
    if (background) SDL_DestroyTexture(background);
    for (auto &enemy : enemies)
    {
        if (enemy)  delete enemy;
        enemy = nullptr;
    }
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
    return;
}

Game::~Game()
{
    clean();
}