#include "../include/handle_collision.h"

// ---Collision check---
bool check_collision(const SDL_FRect &a, const SDL_FRect &b)
{
    if (a.x + a.w < b.x || a.x > b.x + b.w || a.y + a.h < b.y || a.y > b.y + b.h)
        return false;
    return true;
}

// Handle collision between player and enemy, enemy and bullet, player and item, enemy and item
void handle_collision(Game_Playing &game)
{
    for (auto enemy = game.enemies.begin(); enemy != game.enemies.end(); )
    {
        // Check if the enemy is dead
        if (!(*enemy)->active())
        {
            enemy = handle_enemy_death(enemy, game);
            continue;
        }

        // Collision player-enemy
        if (handle_collision_player_enemy(enemy, game.player, game))
        {
            set_state(GAME_STATE::GAME_OVER);
            break;
        }

        // Collision enemy-bullet
        handle_collision_enemy_bullet(enemy, game.player->get_bullets(), game);

        // Collision with item
        handle_collision_player_item(game.player, game.get_items(), game);
        handle_collision_enemy_item(enemy, game.get_items(), game);
        
        ++enemy;
    }
}

// ---Enemy active---
std::vector<Enemy*>::iterator handle_enemy_death(std::vector<Enemy*>::iterator enemy, Game_Playing& game)
{
    // Not active
    // Not boss
    if ((*enemy)->is_boss == false)
    {
        // New normal enemy
        game.enemies_to_delete.push_back(*enemy);
        enemy = game.enemies.erase(enemy);
        game.enemies_to_add.push_back(new Enemy(game.music, game.texture, "texture_enemy", game.enemy_speed, game.enemy_hp, 820));
        
        game.score += 1;
        game.player->player_exp += 2;
        game.player->combo_kill_count++;
    }

    // Boss
    else
    {
        // Get the died boss position
        SDL_FRect tmp = (*enemy)->get_rect();

        // Split into 2 normal enemies
        game.enemies_to_add.push_back(new Enemy(game.music, game.texture, "texture_enemy", game.enemy_speed * 2, game.enemy_hp * 0.5, tmp.x + 20, tmp.y, 85, 85));
        game.enemies_to_add.push_back(new Enemy(game.music, game.texture, "texture_enemy", game.enemy_speed * 2, game.enemy_hp * 0.5, tmp.x + 20, tmp.y + 85, 85, 85));

        SDL_Log(">>> Boss died! Splitting into 2 enemies.");

        game.enemies_to_delete.push_back(*enemy);
        enemy = game.enemies.erase(enemy);

        game.score += 5;
        game.player->player_exp += 10;
        game.player->buff = true;
    }

    return enemy;
}

// ---Enemy - Bullet---
void handle_collision_enemy_bullet(std::vector<Enemy*>::iterator enemy, std::vector<Bullet>& bullets, Game_Playing& game)
{
    for (auto bullet = bullets.begin(); bullet != bullets.end();)
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
            (*enemy)->hp -= bullet->damage;
            bullet = bullets.erase(bullet);
            continue;
        }
        ++bullet;
    }
}

// ---Player - Enemy---
bool handle_collision_player_enemy(std::vector<Enemy*>::iterator enemy, Player* player, Game_Playing& game)
{
    if (!check_collision(player->get_rect(), (*enemy)->get_rect()))
    {
        return false;
    }
    if (player->shield_active())
    {
        SDL_Log(">>> Player is shielded!");
        return false;
    }
    return true;
}

// ---Player - Item---
void handle_collision_player_item(Player* player, std::vector<Item*>& items, Game_Playing& game)
{
    for (auto& item : items)
    {
        if (!item->active())
            continue;

        if (check_collision(player->get_rect(), item->get_rect()))
        {
            item->apply_buff(game);
            item->set_active(false);  // hoặc flag đặc biệt nếu cần
            game.items_to_delete.push_back(item); // đánh dấu để xóa sau
            game.player->buff = true;
        }
    }

    return;
}

// ---Enemy - Item---
void handle_collision_enemy_item(std::vector<Enemy*>::iterator enemy, std::vector<Item*>& items, Game_Playing& game)
{
    return;
}
