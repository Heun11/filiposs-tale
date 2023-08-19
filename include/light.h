#ifndef LIGHT_H
#define LIGHT_H

typedef struct{
    int tile_x;
    int tile_y;
    int light_map_w;
    int light_map_h;
    float* light_map;
}LIGHT_LightSource;

typedef struct{
    int w;
    int h;
    int ts;
    int s_len;
    int s_len_now;
    float default_l;
    LIGHT_LightSource** srcs;
}LIGHT_Light;

#define LIGHT_Kill_Light(l) \
    for(int i=0;i<l.s_len_now;i++){ \
        free(l.srcs[i]->light_map); \
    } \
    free(l.srcs); 

extern float LIGHT_Player_LightMap[];
extern float LIGHT_Torch_LightMap[];

#include"main.h"

void LIGHT_Add_LightMap_To_LightSource(LIGHT_LightSource* s, float* l_map);

void LIGHT_Add_LightSource_To_Light(LIGHT_Light* l, LIGHT_LightSource* s);
void LIGHT_Render_Light(LIGHT_Light* l, int x_o, int y_o);

#endif