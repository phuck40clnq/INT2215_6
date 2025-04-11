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
            game.enemies.push_back(new Enemy(game.enemy_texture, game.enemy_speed, game.enemy_hp));
            
            game.score += 1;
            game.player->player_exp += 2;
            game.player->combo_kill_count++;
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
                SDL_Log("Enemy_HP: %f", (*enemy)->hp);
                (*enemy)->hp -= bullet->damage;
                SDL_Log("Enemy_Hit: %f", (*enemy)->hp);
                SDL_Log("Bullet_Damage: %f", bullet->damage);
                bullet = bullets.erase(bullet);
                continue;
            }
            ++bullet;
        }
        
        ++enemy;
    }
}