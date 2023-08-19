#include"particle.h"

void PARTICLE_Init_Particles(PARTICLE_Particles* ps, int src_x, int src_y, int size, int src_w, int src_h)
{
    if(ps->init!=1){
        ps->init = 1;
        ps->src_x = src_x;
        ps->src_y = src_y;
        ps->src_w = src_w;
        ps->src_h = src_h;
        ps->size = size;
        ps->ps = malloc(size*sizeof(PARTICLE_Particle));
        ps->delayed = 1;
        for(int i=0;i<size;i++){
            ps->ps[i].x = src_x;
            ps->ps[i].y = src_y;
            ps->ps[i].w = src_w;
            ps->ps[i].h = src_h;
            ps->ps[i].l_t = 0.f;
            ps->ps[i].a = 0.f;
        }
    }
}

void PARTICLE_Render_Smoke(PARTICLE_Particles* ps, int life_time, int ts)
{
    for(int i=0;i<(int)ps->delayed;i++){
        ps->ps[i].y -= ts*elapsed*(TOOLS_Random_Float(2)+0.1);
        ps->ps[i].x += ts*elapsed*(TOOLS_Random_Float(6)-3);
        ps->ps[i].l_t += life_time/(1.f/elapsed);
        ps->ps[i].a += life_time/(1.f/elapsed)/life_time;

        if(ps->ps[i].l_t>=life_time){
            ps->ps[i].l_t = 0.f;
            ps->ps[i].x = ps->src_x;
            ps->ps[i].y = ps->src_y;
            ps->ps[i].a = 0.f;
        }

        SDL_SetRenderDrawColor(rend, 252, 255, 240, (int)(255-255*ps->ps[i].a));
        SDL_RenderFillRect(rend, &(SDL_Rect){ps->ps[i].x, ps->ps[i].y, ps->ps[i].w, ps->ps[i].h});
    }
    if(ps->delayed<ps->size-1){
        ps->delayed+=0.1;
    }
}
