#ifndef PLAYER_H
#define PLAYER_H

#include"sdl.h"

typedef struct{
    float x;
    float y;
    SDL_Rect rect;
    int last;
    float x_vel;
    float y_vel;
    float speed;
    float gravity;
    float jump_speed;
    int on_ground;
    int l;
    int r;
    int dead;
    int blink;
}PLAYER_Player;

#include"main.h"
#include"levels.h"

PLAYER_Player PLAYER_Create_Player();
void PLAYER_Set_Player(PLAYER_Player* p, int ts, int map_w, int map_h, int x_o, int y_o, int x, int y);
void PLAYER_Key_Up_Player(PLAYER_Player* p, int key);
void PLAYER_Key_Down_Player(PLAYER_Player* p, int key);
void PLAYER_Collision_Horizontal(PLAYER_Player* p, SDL_Rect t, int type);
void PLAYER_Collision_Vertical(PLAYER_Player* p, SDL_Rect t, int type);
void PLAYER_Update_Player(PLAYER_Player* p, TOOLS_TileMap* m, int ts, int x_o, int y_o, LEVEL_Block* blocks, int* active_blocks, int blocks_len);

#endif