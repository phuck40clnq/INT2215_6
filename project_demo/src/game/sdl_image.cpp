#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

using namespace std;

int main()
{
    // Khởi tạo SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        cout << "SDL_Init failed: " << SDL_GetError() << endl;
        return 1;
    }

    // Khởi tạo SDL_Image
    if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) == 0)
    {
        cout << "IMG_Init failed: " << IMG_GetError() << endl;
        SDL_Quit();
        return 1;
    }

    // Init audio
    if (Mix_Init(MIX_INIT_MP3) == 0)
    {
        cout << "Mix_Init failed: " << Mix_GetError() << endl;
        IMG_Quit();
        SDL_Quit();
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        cout << "Mix_OpenAudio failed: " << Mix_GetError() << endl;
        Mix_Quit();
        IMG_Quit();
        SDL_Quit();
    }

    cout << "SDL_Mixer initialized successfully!" << endl;

    // Tạo window
    SDL_Window *window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        cout << "SDL_CreateWindow failed: " << SDL_GetError() << endl;
        Mix_Quit();
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    // Tạo renderer
    SDL_Renderer *render = SDL_CreateRenderer(window, -1, 0);
    if (render == NULL)
    {
        cout << "SDL_CreateRenderer failed: " << SDL_GetError() << endl;
        SDL_DestroyWindow(window);
        Mix_Quit();
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    // Tải background và nhân vật
    SDL_Texture *background = IMG_LoadTexture(render, "../../images/background.jpg");
    SDL_Texture *player = IMG_LoadTexture(render, "../../images/player.png");
    if (!background || !player)
    {
        cout << "IMG_LoadTexture failed: " << IMG_GetError() << endl;
        SDL_DestroyRenderer(render);
        SDL_DestroyWindow(window);
        Mix_Quit();
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    // Tải nhạc nền và hiệu ứng âm thanh
    // Mix_Music *backgroundMusic = Mix_LoadMUS("music/background.mp3");
    // Mix_Chunk *moveSound = Mix_LoadWAV("sounds/move.wav");
    
    // if (!backgroundMusic || !moveSound) {
    //     cout << "Error loading sound: " << Mix_GetError() << endl;
    //     SDL_DestroyRenderer(render);
    //     SDL_DestroyWindow(window);
    //     Mix_Quit();
    //     IMG_Quit();
    //     SDL_Quit();
    //     return 1;
    // }

    // Mix_PlayMusic(backgroundMusic, -1);
    // Mix_Play

    SDL_Rect playerRect = { 400, 300, 50, 50 };

    SDL_Event event;
    bool running = true;
    
    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = false;
            }

            if (event.type == SDL_KEYDOWN)
            {
                switch(event.key.keysym.sym)
                {
                    case SDLK_UP:    playerRect.y -= 5; break;
                    case SDLK_DOWN:  playerRect.y += 5; break;
                    case SDLK_LEFT:  playerRect.x -= 5; break;
                    case SDLK_RIGHT: playerRect.x += 5; break;
                }
            }
        }

        SDL_RenderClear(render);
        SDL_RenderCopy(render, background, NULL, NULL);

        SDL_Rect rect = { 100, 100, 200, 200 };



        // SDL_SetRenderDrawBlendMode(render, SDL_BLENDMODE_BLEND);
        // // Vẽ một hình chữ nhật bán trong suốt
        // SDL_SetRenderDrawColor(render, 255, 0, 0, 128); // Màu đỏ với alpha 128 (nửa trong suốt)
        // SDL_RenderFillRect(render, &rect);


         // Vẽ nền với viền trong suốt
        SDL_SetRenderDrawBlendMode(render, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(render, 0, 0, 0, 180);  // Màu đen với alpha 180 (mờ)
        SDL_RenderFillRect(render, &rect);

        // Vẽ viền với độ trong suốt (alpha)
        SDL_SetRenderDrawColor(render, 0, 0, 0, 255);  // Màu đen không trong suốt (alpha = 255)
        SDL_RenderDrawRect(render, &rect);  // Vẽ viền của hình chữ nhật




        SDL_SetRenderDrawColor(render, 0, 0, 0, 255); // Đặt lại màu vẽ về đen

        SDL_RenderCopy(render, player, NULL, &playerRect);
        SDL_RenderPresent(render);
        SDL_Delay(10);
    }

    SDL_DestroyTexture(background);
    SDL_DestroyTexture(player);
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
    Mix_CloseAudio();
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}