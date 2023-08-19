#include"levels.h"

struct LEVELS_level_render_info LEVELS_Get_Level_Render_Info(TOOLS_TileMap* map)
{
    float n1;
    float n2;
    struct LEVELS_level_render_info i; 
    n1 = (float)SCREEN_WIDTH/(float)SCREEN_HEIGHT;
    n2 = (float)map->w/(float)map->h;
    i.x_o = 0;
    i.y_o = 0;
    if(n2>n1){
        i.ts = SCREEN_WIDTH/map->w;
        i.y_o = SCREEN_HEIGHT/2-(map->h*i.ts)/2;
    }
    else{
        i.ts = SCREEN_HEIGHT/map->h;
        i.x_o = SCREEN_WIDTH/2-(map->w*i.ts)/2;
    }
    return i;
}

void LEVELS_Render_Tile(int l, int x, int y, int tile, int off_x, int off_y, int tile_w, int tile_h)
{
    if(l==0){
        if(tile==1){
            TOOLS_Render_Image_From_Texture(rend, tex, &backBrick, off_x+x*tile_w, off_y+y*tile_h, tile_w, tile_h);
        }
        if(tile==2){
            TOOLS_Render_Image_From_Texture(rend, tex, &backBrick, off_x+x*tile_w, off_y+y*tile_h, tile_w, tile_h);
        }
	}
    if(l==1){
        if(tile>=1 && tile<=9){
            TOOLS_Render_Image_From_Texture(rend, tex, &bricks[tile-1], off_x+x*tile_w, off_y+y*tile_h, tile_w, tile_h);
        }
        if(tile>=10 && tile<=18){
            TOOLS_Render_Image_From_Texture(rend, tex, &woods[tile-9-1], off_x+x*tile_w, off_y+y*tile_h, tile_w, tile_h);
        }
        if(tile>=19 && tile<=22){
            TOOLS_Render_Image_From_Texture(rend, tex, &woodBricks[tile-18-1], off_x+x*tile_w, off_y+y*tile_h, tile_w, tile_h);
        }
        if(tile==23){
            TOOLS_Render_Image_From_Texture(rend, tex, &grid, off_x+x*tile_w, off_y+y*tile_h, tile_w, tile_h);
        }
	}
    if(l==2){
        if(tile==1){
            TOOLS_Render_Image_From_Texture(rend, tex, &barrel, off_x+x*tile_w, off_y+y*tile_h, tile_w, tile_h);
        }
        if(tile==2){
            TOOLS_Render_Image_From_Texture(rend, tex, &box, off_x+x*tile_w, off_y+y*tile_h, tile_w, tile_h);
        }
        if(tile==3){
            TOOLS_Render_Image_From_Texture(rend, tex, &moss, off_x+x*tile_w, off_y+y*tile_h, tile_w, tile_h);
        }
        if(tile==4){
            TOOLS_Render_Image_From_Texture(rend, tex, &chains, off_x+x*tile_w, off_y+y*tile_h, tile_w, tile_h);
        }
        if(tile==5){
            TOOLS_Render_Image_From_Texture(rend, tex, &banner, off_x+x*tile_w, off_y+y*tile_h, tile_w, tile_h);
        }
        if(tile==6){
            TOOLS_Render_Image_From_Texture(rend, tex, &doors[0], off_x+x*tile_w, off_y+y*tile_h, tile_w, tile_h);
        }
	}
}

void LEVELS_Render_Level_From_Tilemap(TOOLS_TileMap* map, int off_x, int off_y, int tile_w, int tile_h)
{
    for(int i=0;i<map->h*map->w;i++){
        int x = i%map->w; 
        int y = i/map->w;
        int t0 = map->l0[i];
        int t1 = map->l1[i];
        int t2 = map->l2[i];
        LEVELS_Render_Tile(0, x, y, t0, off_x, off_y, tile_w, tile_h);
        LEVELS_Render_Tile(1, x, y, t1, off_x, off_y, tile_w, tile_h);
        LEVELS_Render_Tile(2, x, y, t2, off_x, off_y, tile_w, tile_h);
	}
}

int LEVELS_Menu()
{
	TOOLS_SDL_Text_RenderCopy(rend, font, "Filippos's tale:\nOne day, a long time ago, a legendary battle was taking place in ancient Greece.\nBattle between Greece and Persia.\nYou were fighting as a proud warrior of Greece but sadly,\nYou died.\nSo this is it?\nThis is the end?\nNo.\nYou will find the way out of underworld no matter the cost.", SCREEN_WIDTH/2-SCREEN_WIDTH/4, SCREEN_HEIGHT/7, SCREEN_WIDTH/2, SCREEN_HEIGHT/2, (SDL_Color){176,27,27});
    SDL_Rect button = {SCREEN_WIDTH/2-SCREEN_WIDTH/16,SCREEN_HEIGHT/1.5,SCREEN_WIDTH/8,SCREEN_HEIGHT/4};
	TOOLS_SDL_Text_RenderCopy(rend, font, "play!", button.x, button.y, button.w, button.h, (SDL_Color){255,255,255});

    int mouse_x, mouse_y, buttons;
    buttons = SDL_GetMouseState(&mouse_x, &mouse_y);
    if(buttons & SDL_BUTTON(SDL_BUTTON_LEFT)){
        SDL_Rect mouse = {mouse_x-5, mouse_y-5, 10,10};
        if(TOOLS_Collide_Rect(mouse, button)){
            return 0;
        }
    }
    return 1;
}

int LEVELS_level_0(PLAYER_Player* player)
{
    TOOLS_TileMap map = TOOLS_Load_TileMap_From_File_To_Array("resources/level0.map");
    struct LEVELS_level_render_info info = LEVELS_Get_Level_Render_Info(&map);
    LEVELS_Render_Level_From_Tilemap(&map, info.x_o, info.y_o, info.ts, info.ts);

    SDL_Rect info_r = {info.x_o+info.ts*2, info.y_o+info.ts*1, info.ts*6, info.ts*1};
    TOOLS_SDL_Text_RenderCopy(rend, font, "Move: A D SPACE!", info_r.x, info_r.y, info_r.w, info_r.h, (SDL_Color){176,27,27});

    SDL_Rect doors_r = {9*info.ts+info.x_o, 3*info.ts+info.y_o, info.ts, info.ts};
    TOOLS_Render_Image_From_Texture(rend, tex, &doors[1], doors_r.x, doors_r.y, doors_r.w, doors_r.h);

    if((player->rect.x==-1&&player->rect.y==-1)||(player->rect.w!=info.ts&&player->rect.h!=info.ts)){
        PLAYER_Set_Player(player, info.ts, map.w, map.h, info.x_o, info.y_o, 1, 3);   
    }
    PLAYER_Update_Player(player, &map, info.ts, info.x_o, info.y_o, NULL, NULL, 0);

    LIGHT_Light light = {map.w*3, map.h*3, info.ts/3, 7, 0, 0.f};
    light.srcs = malloc(light.s_len*sizeof(LIGHT_LightSource*));

    LIGHT_LightSource p_light = {(player->rect.x-info.x_o)/light.ts+1,(player->rect.y-info.y_o)/light.ts+1,15,15};
    LIGHT_Add_LightMap_To_LightSource(&p_light, LIGHT_Player_LightMap);
    LIGHT_Add_LightSource_To_Light(&light, &p_light);

    LIGHT_LightSource d_light = {(1*info.ts+info.x_o)/light.ts+1,(3*info.ts+info.y_o)/light.ts+1,19,19};
    LIGHT_Add_LightMap_To_LightSource(&d_light, LIGHT_Torch_LightMap);
    LIGHT_Add_LightSource_To_Light(&light, &d_light);

    LIGHT_Render_Light(&light, info.x_o, info.y_o);
    LIGHT_Kill_Light(light);

    if(TOOLS_Collide_Rect(player->rect, doors_r)){
        return 1;
    }

    TOOLS_Free_Tilemap(&map);
    return 0;
}

float anim_t_c = 0;

int LEVELS_level_1(PLAYER_Player* player)
{
    TOOLS_TileMap map = TOOLS_Load_TileMap_From_File_To_Array("resources/level1.map");
    struct LEVELS_level_render_info info = LEVELS_Get_Level_Render_Info(&map);
    LEVELS_Render_Level_From_Tilemap(&map, info.x_o, info.y_o, info.ts, info.ts);

    int blocks_len = 0;
    LEVEL_Block blocks[] = {

    };
    int active_blocks[] = {
        
    };

    SDL_Rect doors_r = {18*info.ts+info.x_o, 2*info.ts+info.y_o, info.ts, info.ts};
    TOOLS_Render_Image_From_Texture(rend, tex, &doors[1], doors_r.x, doors_r.y, doors_r.w, doors_r.h);

    SDL_Rect torch_r[6] = {
        {4*info.ts+info.x_o, 11*info.ts+info.y_o, info.ts, info.ts},
        {8*info.ts+info.x_o, 4*info.ts+info.y_o, info.ts, info.ts},
        {10*info.ts+info.x_o, 9*info.ts+info.y_o, info.ts, info.ts},
        {15*info.ts+info.x_o, 6*info.ts+info.y_o, info.ts, info.ts},
        {14*info.ts+info.x_o, 12*info.ts+info.y_o, info.ts, info.ts},
        {17*info.ts+info.x_o, 2*info.ts+info.y_o, info.ts, info.ts}
    };

    static PARTICLE_Particles ps[6];
    for(int i=0;i<6;i++){
        PARTICLE_Init_Particles(&ps[i], torch_r[i].x+info.ts/2-info.ts/12, torch_r[i].y, 10, info.ts/6, info.ts/6);
        PARTICLE_Render_Smoke(&ps[i], 20, info.ts);

        TOOLS_Play_Animation(rend, torch, &anim_t_c, 1, 0, 1, torch_r[i].x, torch_r[i].y, torch_r[i].w, torch_r[i].h);
    }

    for(int i=0;i<blocks_len;i++){
        if(active_blocks[i]==1 && blocks[i].t>0){
            LEVELS_Render_Tile(1, blocks[i].x, blocks[i].y, blocks[i].t, info.x_o, info.y_o, info.ts, info.ts);
        }
    }

    if((player->rect.x==-1&&player->rect.y==-1)||(player->rect.w!=info.ts&&player->rect.h!=info.ts)){
        PLAYER_Set_Player(player, info.ts, map.w, map.h, info.x_o, info.y_o, 1, 10);   
    }
    PLAYER_Update_Player(player, &map, info.ts, info.x_o, info.y_o, blocks, active_blocks, blocks_len);
    static ENEMY_Enemy rat[10];
    for(int i=0;i<10;i++){
        ENEMY_Init_Enemy(&rat[i], info.x_o+17*info.ts, info.y_o+17*info.ts, info.ts, info.ts, 1, 10.f, 20.f);
        ENEMY_Update_Rat(&rat[i], &map, info.ts, info.x_o, info.y_o, blocks, active_blocks, blocks_len, player);
    }

    static ENEMY_Enemy harpy[3];
    for(int i=0;i<3;i++){
        ENEMY_Init_Enemy(&harpy[i], info.x_o+2*info.ts, info.y_o+2*info.ts, info.ts, info.ts, 0, 1.f, 3.f);
        ENEMY_Update_Harpy(&harpy[i], &map, info.ts, info.x_o, info.y_o, blocks, active_blocks, blocks_len, player);
    }

    LIGHT_Light light = {map.w*3, map.h*3, info.ts/3, 7, 0, 0.f};
    light.srcs = malloc(light.s_len*sizeof(LIGHT_LightSource*));

    LIGHT_LightSource p_light = {(player->rect.x-info.x_o)/light.ts+1,(player->rect.y-info.y_o)/light.ts+1,15,15};
    LIGHT_Add_LightMap_To_LightSource(&p_light, LIGHT_Player_LightMap);
    LIGHT_Add_LightSource_To_Light(&light, &p_light);

    LIGHT_LightSource t_light[6];
    for(int i=0;i<6;i++){
        t_light[i].tile_x = (torch_r[i].x-info.x_o)/light.ts+1;
        t_light[i].tile_y = (torch_r[i].y-info.y_o)/light.ts+1;
        t_light[i].light_map_w = 19;
        t_light[i].light_map_h = 19;

        LIGHT_Add_LightMap_To_LightSource(&t_light[i], LIGHT_Torch_LightMap);
        LIGHT_Add_LightSource_To_Light(&light, &t_light[i]);
    }

    LIGHT_Render_Light(&light, info.x_o, info.y_o);
    LIGHT_Kill_Light(light);

    TOOLS_Free_Tilemap(&map);

    if(TOOLS_Collide_Rect(player->rect, doors_r) || player->dead){
        for(int i=0;i<10;i++){
            rat[i].init = 0;
        }
        for(int i=0;i<3;i++){
            harpy[i].init = 0;
        }
        for(int i=0;i<6;i++){
            ps[i].init = 0;
        }
        if(TOOLS_Collide_Rect(player->rect, doors_r)){
            return 2;
        }
        else if(player->dead){
            return 0;
        }
    }
    return 1;
}

int LEVELS_level_2(PLAYER_Player* player)
{
    TOOLS_TileMap map = TOOLS_Load_TileMap_From_File_To_Array("resources/level2.map");
    struct LEVELS_level_render_info info = LEVELS_Get_Level_Render_Info(&map);
    LEVELS_Render_Level_From_Tilemap(&map, info.x_o, info.y_o, info.ts, info.ts);

    int spikes_len = 8;
    int spikes_r[][3] = {
        {9,18,0},{20,16,0},{22,16,0},{11,12,0},{1,9,0},{7,7,0},{12,7,0}
    };

    for(int i=0;i<spikes_len;i++){
        TOOLS_Render_Image_From_Texture(rend, tex, &spikes[spikes_r[i][2]], info.x_o+info.ts*spikes_r[i][0], info.y_o+info.ts*spikes_r[i][1], info.ts, info.ts);
        if(TOOLS_Collide_Rect(player->rect, (SDL_Rect){info.x_o+info.ts*spikes_r[i][0], info.y_o+info.ts*spikes_r[i][1], info.ts, info.ts})){
            player->dead = 1;
        }
    }

    static ENEMY_Enemy ghost1;
    ENEMY_Init_Enemy(&ghost1, -200,-200,info.ts,info.ts,1,1,2);
    ENEMY_Update_Ghost(&ghost1, info.ts, player);

    static ENEMY_Enemy ghost2;
    ENEMY_Init_Enemy(&ghost2, 8000,3000,info.ts,info.ts,1,1,2);
    ENEMY_Update_Ghost(&ghost2, info.ts, player);

    SDL_Rect doors_r = {1*info.ts+info.x_o, 2*info.ts+info.y_o, info.ts, info.ts};
    TOOLS_Render_Image_From_Texture(rend, tex, &doors[1], doors_r.x, doors_r.y, doors_r.w, doors_r.h);

    SDL_Rect torch_r[11] = {
        {6*info.ts+info.x_o, 16*info.ts+info.y_o, info.ts, info.ts},
        {14*info.ts+info.x_o, 16*info.ts+info.y_o, info.ts, info.ts},
        {23*info.ts+info.x_o, 15*info.ts+info.y_o, info.ts, info.ts},
        {25*info.ts+info.x_o, 11*info.ts+info.y_o, info.ts, info.ts},
        {18*info.ts+info.x_o, 11*info.ts+info.y_o, info.ts, info.ts},
        {3*info.ts+info.x_o, 8*info.ts+info.y_o, info.ts, info.ts},
        {15*info.ts+info.x_o, 5*info.ts+info.y_o, info.ts, info.ts},
        {25*info.ts+info.x_o, 3*info.ts+info.y_o, info.ts, info.ts},
        {6*info.ts+info.x_o, 1*info.ts+info.y_o, info.ts, info.ts},
        {18*info.ts+info.x_o, 15*info.ts+info.y_o, info.ts, info.ts},
        {30*info.ts+info.x_o, 30*info.ts+info.y_o, info.ts, info.ts}
    };

    static PARTICLE_Particles ps[11];
    for(int i=0;i<11;i++){
        PARTICLE_Init_Particles(&ps[i], torch_r[i].x+info.ts/2-info.ts/12, torch_r[i].y, 10, info.ts/6, info.ts/6);
        PARTICLE_Render_Smoke(&ps[i], 20, info.ts);

        TOOLS_Play_Animation(rend, torch, &anim_t_c, 1, 0, 1, torch_r[i].x, torch_r[i].y, torch_r[i].w, torch_r[i].h);
    }

    if((player->rect.x==-1&&player->rect.y==-1)||(player->rect.w!=info.ts&&player->rect.h!=info.ts)){
        PLAYER_Set_Player(player, info.ts, map.w, map.h, info.x_o, info.y_o, 5, 16);  
    }
    PLAYER_Update_Player(player, &map, info.ts, info.x_o, info.y_o, NULL, NULL, 0);

    LIGHT_Light light = {map.w*3, map.h*3, info.ts/3, 17, 0, .0f};
    light.srcs = malloc(light.s_len*sizeof(LIGHT_LightSource*));

    LIGHT_LightSource p_light = {(player->rect.x-info.x_o)/light.ts+1,(player->rect.y-info.y_o)/light.ts+1,15,15};
    LIGHT_Add_LightMap_To_LightSource(&p_light, LIGHT_Player_LightMap);
    LIGHT_Add_LightSource_To_Light(&light, &p_light);

    LIGHT_LightSource t_light[11];
    for(int i=0;i<11;i++){
        t_light[i].tile_x = (torch_r[i].x-info.x_o)/light.ts+1;
        t_light[i].tile_y = (torch_r[i].y-info.y_o)/light.ts+1;
        t_light[i].light_map_w = 19;
        t_light[i].light_map_h = 19;

        LIGHT_Add_LightMap_To_LightSource(&t_light[i], LIGHT_Torch_LightMap);
        LIGHT_Add_LightSource_To_Light(&light, &t_light[i]);
    }

    LIGHT_Render_Light(&light, info.x_o, info.y_o);
    LIGHT_Kill_Light(light);

    TOOLS_Free_Tilemap(&map);

    if(TOOLS_Collide_Rect(player->rect, doors_r) || player->dead){
        for(int i=0;i<11;i++){
            ps[i].init = 0;
        }
        ghost1.init = 0;
        ghost2.init = 0;
        if(TOOLS_Collide_Rect(player->rect, doors_r)){
            return 3;
        }
        else if(player->dead){
            return 0;
        }
    }
    return 2;
}

int LEVELS_level_3(PLAYER_Player* player)
{
    TOOLS_TileMap map = TOOLS_Load_TileMap_From_File_To_Array("resources/level3.map");
    struct LEVELS_level_render_info info = LEVELS_Get_Level_Render_Info(&map);
    LEVELS_Render_Level_From_Tilemap(&map, info.x_o, info.y_o, info.ts, info.ts);

    SDL_Rect doors_r = {28*info.ts+info.x_o, 4*info.ts+info.y_o, info.ts, info.ts};
    TOOLS_Render_Image_From_Texture(rend, tex, &doors[1], doors_r.x, doors_r.y, doors_r.w, doors_r.h);

    SDL_Rect torch_r[7] = {
        {7*info.ts+info.x_o, 14*info.ts+info.y_o, info.ts, info.ts},
        {4*info.ts+info.x_o, 9*info.ts+info.y_o, info.ts, info.ts},
        {10*info.ts+info.x_o, 8*info.ts+info.y_o, info.ts, info.ts},
        {2*info.ts+info.x_o, 2*info.ts+info.y_o, info.ts, info.ts},
        {17*info.ts+info.x_o, 2*info.ts+info.y_o, info.ts, info.ts},
        {24*info.ts+info.x_o, 15*info.ts+info.y_o, info.ts, info.ts},
        {26*info.ts+info.x_o, 4*info.ts+info.y_o, info.ts, info.ts}
    };

    static PARTICLE_Particles ps[7];
    for(int i=0;i<7;i++){
        PARTICLE_Init_Particles(&ps[i], torch_r[i].x+info.ts/2-info.ts/12, torch_r[i].y, 10, info.ts/6, info.ts/6);
        PARTICLE_Render_Smoke(&ps[i], 20, info.ts);

        TOOLS_Play_Animation(rend, torch, &anim_t_c, 1, 0, 1, torch_r[i].x, torch_r[i].y, torch_r[i].w, torch_r[i].h);
    }

    if((player->rect.x==-1&&player->rect.y==-1)||(player->rect.w!=info.ts&&player->rect.h!=info.ts)){
        PLAYER_Set_Player(player, info.ts, map.w, map.h, info.x_o, info.y_o, 7, 16);  
    }
    PLAYER_Update_Player(player, &map, info.ts, info.x_o, info.y_o, NULL, NULL, 0);

    static ENEMY_Enemy rat1;
    ENEMY_Init_Enemy(&rat1, info.x_o+16*info.ts, info.y_o+2*info.ts, info.ts, info.ts, 1, 5.f, 10.f);
    ENEMY_Update_Rat(&rat1, &map, info.ts, info.x_o, info.y_o, NULL, NULL, 0, player);

    static ENEMY_Enemy rat2;
    ENEMY_Init_Enemy(&rat2, info.x_o+16*info.ts, info.y_o+2*info.ts, info.ts, info.ts, -1, 5.f, 10.f);
    ENEMY_Update_Rat(&rat2, &map, info.ts, info.x_o, info.y_o, NULL, NULL, 0, player);

    static ENEMY_Enemy harphy;
    ENEMY_Init_Enemy(&harphy, info.x_o+3*info.ts, info.y_o+3*info.ts, info.ts, info.ts, -1, 1.f, 2.f);
    ENEMY_Update_Harpy(&harphy, &map, info.ts, info.x_o, info.y_o, NULL, NULL, 0, player);

    static ENEMY_Enemy ghost;
    ENEMY_Init_Enemy(&ghost, info.x_o+20*info.ts, info.y_o+16*info.ts, info.ts, info.ts, -1, 1.f, 2.f);
    ENEMY_Update_Ghost(&ghost, info.ts, player);

    LIGHT_Light light = {map.w*3, map.h*3, info.ts/3, 12, 0, .0f};
    light.srcs = malloc(light.s_len*sizeof(LIGHT_LightSource*));

    LIGHT_LightSource p_light = {(player->rect.x-info.x_o)/light.ts+1,(player->rect.y-info.y_o)/light.ts+1,15,15};
    LIGHT_Add_LightMap_To_LightSource(&p_light, LIGHT_Player_LightMap);
    LIGHT_Add_LightSource_To_Light(&light, &p_light);

    LIGHT_LightSource t_light[7];
    for(int i=0;i<7;i++){
        t_light[i].tile_x = (torch_r[i].x-info.x_o)/light.ts+1;
        t_light[i].tile_y = (torch_r[i].y-info.y_o)/light.ts+1;
        t_light[i].light_map_w = 19;
        t_light[i].light_map_h = 19;

        LIGHT_Add_LightMap_To_LightSource(&t_light[i], LIGHT_Torch_LightMap);
        LIGHT_Add_LightSource_To_Light(&light, &t_light[i]);
    }

    LIGHT_Render_Light(&light, info.x_o, info.y_o);
    LIGHT_Kill_Light(light);

    TOOLS_Free_Tilemap(&map);

    if(TOOLS_Collide_Rect(player->rect, doors_r) || player->dead){
        for(int i=0;i<7;i++){
            ps[i].init = 0;
        }
        rat1.init = 0;
        rat2.init = 0;
        harphy.init = 0;
        ghost.init = 0;
        if(TOOLS_Collide_Rect(player->rect, doors_r)){
            return 4;
        }
        else if(player->dead){
            return 0;
        }
    }
    return 3;
}
