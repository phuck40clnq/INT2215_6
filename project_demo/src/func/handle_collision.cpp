#include "handle_collision.h"

bool check_collision(const SDL_Rect &a, const SDL_Rect &b)
{
    if (a.x + a.w < b.x || a.x > b.x + b.w || a.y + a.h < b.y || a.y > b.y + b.h)
        return false;
    return true;
}

void handle_collision(Game_Playing &game)
{
    std::vector<Enemy*> enemies_to_delete;
    std::vector<Enemy*> enemies_to_add;

    for (auto enemy = game.enemies.begin(); enemy != game.enemies.end(); )
    {
        if (!(*enemy)->active())
        {
            // Not boss
            if ((*enemy)->is_boss == false)
            {
                // New normal enemy
                enemies_to_delete.push_back(*enemy);
                enemy = game.enemies.erase(enemy);
                game.enemies.push_back(new Enemy(game.music, game.enemy_texture, game.enemy_speed, game.enemy_hp));
                
                game.score += 1;
                game.player->player_exp += 2;
                game.player->combo_kill_count++;
            }

            // Boss
            else
            {
                // Get the died boss position
                SDL_Rect tmp = (*enemy)->get_rect();

                // Split into 2 normal enemies
                enemies_to_add.push_back(new Enemy(game.music, game.enemy_texture, game.enemy_speed * 2, game.enemy_hp * 0.5, tmp.x + 20, tmp.y, 85, 85));
                enemies_to_add.push_back(new Enemy(game.music, game.enemy_texture, game.enemy_speed * 2, game.enemy_hp * 0.5, tmp.x + 20, tmp.y + 85, 85, 85));

                SDL_Log(">>> Boss died! Splitting into 2 enemies.");

                enemies_to_delete.push_back(*enemy);
                enemy = game.enemies.erase(enemy);

                game.score += 5;
                game.player->player_exp += 10;
                game.player->buff = true;
            }
            continue;
        }

        else if (check_collision(game.player->get_rect(), (*enemy)->get_rect()))
        {
            set_state(GAME_STATE::GAME_OVER);
            break;
        }

        auto& bullets = game.player->get_bullets();
        for (auto bullet = bullets.begin(); bullet != bullets.end(); )
        {
            if (!bullet->active())
            {
                bullet = bullets.erase(bullet);
                continue;
            }
            if (check_collision(bullet->get_rect(), (*enemy)->get_rect()))
            {
                // Enemy hit
                (*enemy)->hit_delay.start(100);
                (*enemy)->move_delay.start(50);
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

     // Delete enemies
    for (auto& delete_enemy : enemies_to_delete)
    {
         delete delete_enemy;
    }

    // Add enemies
    for (auto& add_enemy : enemies_to_add)
    {
        game.enemies.push_back(add_enemy);
    }
}

void enemy_die(Game_Playing &game, Enemy **enemy)
{}