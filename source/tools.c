#include"tools.h"

int TOOLS_Random_Number(int start, int stop)
{
	if(SRAND_CALL!=-1){
		srand(time(0));
		SRAND_CALL = -1;
	}
	return (rand()%(stop-start+1))+start;
}

float TOOLS_Random_Float(float stop)
{
	if(SRAND_CALL!=-1){
		srand(time(0));
		SRAND_CALL = -1;
	}
	return ((float)rand()/RAND_MAX)*stop;
}

void get_error()
{
	printf("Error with sdl: %s\n", SDL_GetError());
	fflush(stdout);
	exit(0);
}

void TOOLS_SDL_Text_RenderCopy(SDL_Renderer* r, TTF_Font* f, char* s, int x, int y, int w, int h, SDL_Color c)
{
	SDL_Surface* surf = TTF_RenderText_Blended_Wrapped(f, s, c, w);
	SDL_Texture* t = SDL_CreateTextureFromSurface(r, surf);
	SDL_FreeSurface(surf);
	SDL_RenderCopy(r, t, NULL, &(SDL_Rect){x, y, w, h});
	SDL_DestroyTexture(t);
}

TOOLS_TileMap TOOLS_Load_TileMap_From_File_To_Array(char* filename)
{
	TOOLS_TileMap m;
	FILE* f;
	f = fopen(filename, "r");
	fscanf(f, "%d %d", &m.w, &m.h);
	m.l0 = malloc(m.w*m.h*sizeof(int));
	m.l1 = malloc(m.w*m.h*sizeof(int));
	m.l2 = malloc(m.w*m.h*sizeof(int));
	for(int i=0;i<m.h*m.w;i++){
		fscanf(f, "%d", &m.l0[i]);
	}
	for(int i=0;i<m.h*m.w;i++){
		fscanf(f, "%d", &m.l1[i]);
	}
	for(int i=0;i<m.h*m.w;i++){
		fscanf(f, "%d", &m.l2[i]);
	}
	fclose(f);
	return m;
}

void TOOLS_Free_Tilemap(TOOLS_TileMap* m)
{
	free(m->l0);
	free(m->l1);
	free(m->l2);
}

SDL_Rect TOOLS_Get_Image_Src(int x, int y, int t_w, int t_h)
{
	SDL_Rect r = {x*t_w, y*t_h, t_w, t_h};
	return r;
}

void TOOLS_Render_Image_From_Texture(SDL_Renderer* rend, SDL_Texture* tex, SDL_Rect* src, int x, int y, int w, int h)
{
	SDL_Rect dest = {x, y, w, h};
	SDL_RenderCopy(rend, tex, src, &dest);
}

int TOOLS_Collide_Rect(SDL_Rect r1, SDL_Rect r2)
{
	return r1.x<r2.x+r2.w &&
		r1.x+r1.w>r2.x &&
		r1.y<r2.y+r2.h &&
		r1.y+r1.h>r2.y;
}

void TOOLS_Play_Animation(SDL_Renderer* r, SDL_Rect* images, float* anim_c, int fps, int start, int end, int x, int y, int w, int h)
{
	float n = (float)fps/(1.0f/elapsed);
	*anim_c+=n;
	if(*anim_c>=end+1){
		*anim_c = start;
	}
	TOOLS_Render_Image_From_Texture(rend, tex, &images[(int)*anim_c], x, y, w, h);
}

void TOOLS_Save_Data(char* filename, TOOLS_SaveData* d)
{
	FILE* file;
	file = fopen(filename, "w");
	// if(file==NULL){
	// 	fprintf(stderr, "\nError Opening File\n");
	// 	exit(1);
	// }
	fwrite(d, sizeof(TOOLS_SaveData), 1, file);
	fclose(file);
}

void TOOLS_Load_Data(char* filename, TOOLS_SaveData* d)
{
	FILE* file;
	file = fopen(filename, "r");
	// if(file==NULL){
	// 	fprintf(stderr, "\nError Opening File\n");
	// 	exit(1);
	// }
	fread(d, sizeof(TOOLS_SaveData), 1, file);
	fclose(file);
}