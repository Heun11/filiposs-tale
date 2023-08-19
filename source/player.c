#include"player.h"

PLAYER_Player PLAYER_Create_Player()
{
    PLAYER_Player p = {.x=-1,.y=-1,.rect={-1,-1,-1,-1},.speed=-1,.x_vel=0,.y_vel=0,.gravity=-1,.jump_speed=-1,
        .on_ground=0,.last=0,.l=0,.r=0,.dead=0,.blink=0};
    return p;
}

void PLAYER_Set_Player(PLAYER_Player* p, int ts, int map_w, int map_h, int x_o, int y_o, int x, int y)
{
    p->blink = 0;
    p->dead = 0;
    p->rect.w = ts;
    p->rect.h = ts;
    p->rect.x = x*ts+x_o;
    p->rect.y = y*ts+y_o;
    p->x = p->rect.x;
    p->y = p->rect.y;
    p->speed = (float)ts*6;
    p->gravity = (float)ts*70;
    p->jump_speed = -p->gravity/3;
}

void PLAYER_Key_Down_Player(PLAYER_Player* p, int key)
{
    if(key==SDL_SCANCODE_A){
        p->l = 1;
        p->last = 1;
    }
    else if(key==SDL_SCANCODE_D){
        p->r = 1;
        p->last = 0;
    }
    
    if(key==SDL_SCANCODE_W){
        if(!p->blink){
            p->blink = 1;
        }
        else{
            p->blink = 0;
        }
    }

    if(key==SDL_SCANCODE_SPACE){
        if(p->on_ground){
            p->y_vel = p->jump_speed + elapsed*p->gravity;
            p->on_ground = 0;
        }
    }
}

void PLAYER_Key_Up_Player(PLAYER_Player* p, int key)
{
    if(key==SDL_SCANCODE_A){
        p->l = 0;
    }
    else if(key==SDL_SCANCODE_D){
        p->r = 0;
    }
}

void PLAYER_Collision_Horizontal(PLAYER_Player* p, SDL_Rect t, int type)
{
    if(type>=1&&type<=23){
        if(TOOLS_Collide_Rect(p->rect, t)){
            if(p->x_vel>0){
                p->x = (float)(t.x-p->rect.w);
                p->rect.x = (int)p->x;
            }
            else if(p->x_vel<0){
                p->x = (float)(t.x+t.w);
                p->rect.x = (int)p->x;
            }
        }
    }
}

void PLAYER_Collision_Vertical(PLAYER_Player* p, SDL_Rect t, int type)
{
    if(type>=1&&type<=23){
        if(TOOLS_Collide_Rect(p->rect, t)){
            if(p->y_vel>0){
                p->y = (float)(t.y-p->rect.h);
                p->rect.y = (int)p->y;
                p->y_vel = 0;
                p->on_ground = 1;
            }
            else if(p->y_vel<0){
                p->y = (float)(t.y+t.h);
                p->rect.y = (int)p->y;
                p->y_vel = 0;
            }
        }
    }
}

float anim_r_c = 0;
float anim_l_c = 0;

void PLAYER_Update_Player(PLAYER_Player* p, TOOLS_TileMap* m, int ts, int x_o, int y_o, LEVEL_Block* blocks, int* active_blocks, int blocks_len)
{
    if(p->r&&!p->l){
        p->x_vel = 1;
    }
    else if(p->l&&!p->r){
        p->x_vel = -1;
    }
    else{
        p->x_vel = 0;
    }

    p->y_vel = p->y_vel + elapsed*p->gravity;
    p->y = p->y + elapsed*p->y_vel;
    p->rect.y = (int)p->y;

    for(int i=0;i<m->h;i++){
        for(int j=0;j<m->w;j++){
            SDL_Rect t = {j*ts+x_o, i*ts+y_o, ts, ts};
            PLAYER_Collision_Vertical(p, t, m->l1[i*m->w+j]);    
        }
    }
    if(blocks!=NULL && active_blocks!=NULL){
        for(int i=0;i<blocks_len;i++){
            if(active_blocks[i]==1){
                SDL_Rect t = {blocks[i].x*ts+x_o, blocks[i].y*ts+y_o, ts, ts};
                PLAYER_Collision_Vertical(p, t, blocks[i].t);
            }
        }
    }

    p->x += (p->x_vel*p->speed*elapsed);
    p->rect.x = (int)p->x;

    for(int i=0;i<m->h;i++){
        for(int j=0;j<m->w;j++){
            SDL_Rect t = {j*ts+x_o, i*ts+y_o, ts, ts};
            PLAYER_Collision_Horizontal(p, t, m->l1[i*m->w+j]);
        }
    }
    if(blocks!=NULL && active_blocks!=NULL){
        for(int i=0;i<blocks_len;i++){
            if(active_blocks[i]==1){
                SDL_Rect t = {blocks[i].x*ts+x_o, blocks[i].y*ts+y_o, ts, ts};
                PLAYER_Collision_Horizontal(p, t, blocks[i].t);
            }
        }
    }

    if(p->x_vel>0){
        TOOLS_Play_Animation(rend, archer_right, &anim_r_c, 5, 1, 2, p->rect.x,p->rect.y,p->rect.w,p->rect.h);
    }
    else if(p->x_vel<0){
        TOOLS_Play_Animation(rend, archer_left, &anim_l_c, 5, 1, 2, p->rect.x,p->rect.y,p->rect.w,p->rect.h);
    }
    else{
        if(p->last){
            TOOLS_Render_Image_From_Texture(rend, tex, &archer_left[0], p->rect.x, p->rect.y, p->rect.w, p->rect.h);
        }
        else{
            TOOLS_Render_Image_From_Texture(rend, tex, &archer_right[0], p->rect.x, p->rect.y, p->rect.w, p->rect.h);
        }
    }

    if(p->blink){
        SDL_RenderFillRect(rend, &(SDL_Rect){0,0,SCREEN_WIDTH,SCREEN_HEIGHT});
	    TOOLS_SDL_Text_RenderCopy(rend, font, "(-)(-)", SCREEN_WIDTH/2-400, SCREEN_HEIGHT/4, 800, 300, (SDL_Color){176,27,27});
    }
}
