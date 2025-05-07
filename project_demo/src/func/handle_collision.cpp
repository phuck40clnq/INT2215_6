#include "../include/handle_collision.h"

#include <random>

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
        handle_collision_player_enemy(enemy, game.player, game);
        if (game.player->is_dead)
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
        SDL_FRect tmp = (*enemy)->get_rect();

        // New normal enemy
        game.enemies_to_delete.push_back(*enemy);
        enemy = game.enemies.erase(enemy);
        game.enemies_to_add.push_back(new Enemy(game.music, game.texture, "texture_enemy", game.enemy_speed, game.enemy_hp, 820));

        game.score += 1;
        game.player->player_exp += 2;
        game.player->combo_kill_count++;

        // New boom (random)
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_int_distribution<> dist(0, 99); // Random from 0 to 99
        int rand = dist(gen);
        if (rand < 20) // 20 %
        {
            game.add_item_to_game(game.texture, "texture_boom", tmp.x + 17.5, tmp.y + 22, 50, 50, ITEM_EFFECT::BOOM, ITEM_TRIGGER::NONE);
        }
        if (rand >= 90) // 10 %
        {
            game.add_item_to_game(game.texture, "texture_buff_player_exp", tmp.x + 17.5, tmp.y + 22, 50, 50, ITEM_EFFECT::EXP, ITEM_TRIGGER::TIME_BASED, 200, -1, -1, -1);
        }
    }

    // Boss
    else
    {
        // Get the died boss position
        SDL_FRect tmp = (*enemy)->get_rect();
        game.add_item_to_game(game.texture, "texture_buff_player_exp", -1, -1, 50, 50, ITEM_EFFECT::EXP, ITEM_TRIGGER::TIME_BASED, 200, -1, -1, -1);
        game.add_item_to_game(game.texture, "texture_buff_player_shield", -1, -1, 50, 50, ITEM_EFFECT::SHIELD, ITEM_TRIGGER::ENEMY_COUNT, -1, -1, 7, -1);

        // Split into 2 normal enemies
        game.enemies_to_add.push_back(new Enemy(game.music, game.texture, "texture_enemy", game.enemy_speed * 2, game.enemy_hp * 0.5, tmp.x + 20, tmp.y, 85, 85));
        game.enemies_to_add.push_back(new Enemy(game.music, game.texture, "texture_enemy", game.enemy_speed * 2, game.enemy_hp * 0.5, tmp.x + 20, tmp.y + 85, 85, 85));
        game.current_enemy++;

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
            if (bullet->get_type() == BULLET_TYPE::ELECTRIC)
            {
                if (!bullet->has_hit_enemy(*enemy))
                {
                    apply_bullet_effect_on_enemy(enemy, *bullet, game);
                    bullet->mark_hit_enemy(*enemy);
                }
                ++bullet;
            }
            else
            {
                apply_bullet_effect_on_enemy(enemy, *bullet, game);
                bullet = bullets.erase(bullet);
            }
            continue;
        }
        ++bullet;
    }
}

void apply_bullet_effect_on_enemy(std::vector<Enemy*>::iterator enemy, Bullet& bullet, Game_Playing& game)
{
    switch (bullet.get_type())
    {
        case BULLET_TYPE::EXPLOSION:
            (*enemy)->hp -= bullet.damage * 2.f;
            break;
            
        case BULLET_TYPE::ICE:
            (*enemy)->hp -= bullet.damage;
            if (!(*enemy)->is_frozen)
            {
                (*enemy)->freeze_duration.start(1000); // 1s froze
                (*enemy)->is_frozen = true;
            }
            else if (!(*enemy)->is_iced) 
            {
                (*enemy)->ice_speed = (*enemy)->original_speed * 0.5f;   // Apply slowing effect
                // (*enemy)->ice_speed = (*enemy)->speed * 0.5f;  // If want freeze 3s when condition
                (*enemy)->ice_effect_duration.start(3000); // 3s slow
                (*enemy)->is_iced = true;
            }
            break;

        case BULLET_TYPE::POISON:
            (*enemy)->hp -= bullet.damage;
            if (!(*enemy)->is_poisoned) 
            {
                (*enemy)->is_poisoned = true;
                (*enemy)->poison_damage = bullet.damage * 0.5f; // Damage of poison
                (*enemy)->poison_tick_delay.start(1000);        // Damage each second
                (*enemy)->poison_effect_duration.start(3000);  // Start poison damage last 3s
            }
            break;
        
        case BULLET_TYPE::ELECTRIC:
            (*enemy)->hp -= bullet.damage;
            (*enemy)->stun_duration.start(200);  // Short stun duration
            (*enemy)->is_stun = true;
            break;

        default:
            (*enemy)->hp -= bullet.damage;
            break;
    }
}

// ---Player - Enemy---
void handle_collision_player_enemy(std::vector<Enemy*>::iterator enemy, Player* player, Game_Playing& game)
{
    if (!check_collision(player->get_rect(), (*enemy)->get_rect()))
    {
        return;
    }
    if (player->shield_active())
    {
        SDL_Log(">>> Player is shielded!");
        return;
    }

    // player->is_dead = true;
    return;
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
            if (item->get_effect() == ITEM_EFFECT::BOOM)
            {
                player->is_dead = true;
                break;
            }
            item->apply_buff(game);
            item->set_active(false);
            if (item->get_effect() == ITEM_EFFECT::BUFF_BULLET_TYPE || item->get_effect() == ITEM_EFFECT::BUFF_BULLET_DAMAGE)
                game.player->buff = true;
        }
    }

    return;
}

// ---Enemy - Item---
void handle_collision_enemy_item(std::vector<Enemy*>::iterator enemy, std::vector<Item*>& items, Game_Playing& game)
{
    for (auto& item : items)
    {
        if (!item->active())
            continue;

        if (check_collision((*enemy)->get_rect(), item->get_rect()) && (item->get_effect() == ITEM_EFFECT::BOOM))
        {
            (*enemy)->hp = (*enemy)->max_hp;
            item->apply_buff(game);
            item->set_active(false);
            game.items_to_delete.push_back(item); // Appear once
        }
    }

    return;
}
