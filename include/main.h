#ifndef MAIN_H
#define MAIN_H

#include"sdl.h"
#include"tools.h"
#include"stdio.h"
#include"stdlib.h"
#include"math.h"

#define TILE_SIZE_REAL 16
#define TS 64 // for speed calculations

extern SDL_Renderer* rend;
extern SDL_Texture* tex;
extern TTF_Font* font;

extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
extern float elapsed;

#include"tiles.h"
#include"player.h"
#include"light.h"
#include"levels.h"

#endif