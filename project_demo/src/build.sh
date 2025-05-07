#!/bin/bash

# File name
SOURCES="
    game/main.cpp \
    core/game.cpp core/player.cpp core/GameObject.cpp core/enemy.cpp core/bullet.cpp core/texture.cpp core/music.cpp core/font.cpp\
    func/handle_collision.cpp func/render.cpp func/level_up.cpp \
    items/item.cpp items/buff_bullet_damage_item.cpp items/buff_bullet_type_item.cpp items/buff_player_exp_item.cpp items/buff_player_shield_item.cpp items/boom.cpp\
    screen/button.cpp screen/Game_gameover.cpp screen/Game_menu.cpp screen/Game_playing.cpp screen/Game_state.cpp screen/board.cpp \
"

OUTPUT="hic"

# Libraries
LIBS="-lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer"

# Compile
g++ $SOURCES -o "$OUTPUT" -std=c++11 $LIBS 2>> build.log

echo "Build!"
cat build.log


# Check if the compilation was successful
if [ $? -eq 0 ]; then
    echo "Run!"
    ./"$OUTPUT"

else
    echo "Error!"
fi
