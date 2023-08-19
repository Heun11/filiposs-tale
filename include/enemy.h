#ifndef ENEMY_H
#define ENEMY_H

#include"sdl.h"

typedef struct{
    int init;
    float x;
    float y;
    SDL_Rect r;
    int last;
    float x_vel;
    float y_vel;
    int on_ground;
    int can_attack;
    int speed;
}ENEMY_Enemy;

#include"main.h"

void ENEMY_Init_Enemy(ENEMY_Enemy* e, int x, int y, int w, int h, int x_vel, float s_s, float s_e);
void ENEMY_Collision_Horizontal(ENEMY_Enemy* e, SDL_Rect t);
void ENEMY_Collision_Vertical(ENEMY_Enemy* e, SDL_Rect t);

void ENEMY_Update_Rat(ENEMY_Enemy* e, TOOLS_TileMap* m, int ts, int x_o, int y_o, LEVEL_Block* blocks, int* active_blocks, int blocks_len, PLAYER_Player* p);
void ENEMY_Update_Harpy(ENEMY_Enemy* e, TOOLS_TileMap* m, int ts, int x_o, int y_o, LEVEL_Block* blocks, int* active_blocks, int blocks_len, PLAYER_Player* p);
void ENEMY_Update_Ghost(ENEMY_Enemy* e, int ts, PLAYER_Player* p);

#endif