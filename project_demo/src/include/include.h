#pragma once
#ifndef INCLUDE_H
#define INCLUDE_H

#include <random>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <unordered_map>
#include <vector>

#include "animation.h"
#include "bullet.h"
#include "enemy.h"
#include "game.h"
#include "GameObject.h"
#include "music.h"
#include "player.h"

// Fps
#define fps 60

// Max number of enemies
#define max_enemies 20
#define ENEMY 6

// Size of window
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#endif