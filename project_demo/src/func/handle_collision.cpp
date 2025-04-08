#include "handle_collision.h"

bool check_collision(const SDL_Rect &a, const SDL_Rect &b)
{
    if (a.x + a.w < b.x || a.x > b.x + b.w || a.y + a.h < b.y || a.y > b.y + b.h)
        return false;
    return true;
}

void handle_collision(Game_Playing &game)
{
    for (auto enemy = game.enemies.begin(); enemy != game.enemies.end(); )
    {
        if (!(*enemy)->active())
        {
            delete *enemy;
            enemy = game.enemies.erase(enemy);
            game.enemies.push_back(new Enemy(game.enemy_texture));
            
            game.score += 10;
            game.player->player_exp += 2;
            continue;
        }
        if (check_collision(game.player->get_rect(), (*enemy)->get_rect()))
        {
            set_state(GAME_OVER);
            break;
        }

        auto &bullets = game.player->get_bullets();
        for (auto bullet = bullets.begin(); bullet != bullets.end(); )
        {
            if (!bullet->active())
            {
                bullet = bullets.erase(bullet);
                continue;
            }
            if (check_collision(bullet->get_rect(), (*enemy)->get_rect()))
            {
                (*enemy)->hp -= 2;
                bullet = bullets.erase(bullet);
                continue;
            }
            ++bullet;
        }
        
        ++enemy;
    }
}