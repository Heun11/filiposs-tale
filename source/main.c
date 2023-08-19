#include<stdio.h>
#include<math.h>

#include"main.h"

SDL_Renderer* rend;
SDL_Texture* tex;
TTF_Font* font;
int SCREEN_WIDTH;
int SCREEN_HEIGHT;
float elapsed;

int main(int argc, char** argv)
{
	
	if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER|SDL_INIT_AUDIO)!=0){
		SDL_Quit();
		return 1;
	}
	
	SDL_DisplayMode DM;
	SDL_GetCurrentDisplayMode(0, &DM);
	SCREEN_WIDTH = DM.w;
	SCREEN_HEIGHT = DM.h;
	Uint32 win_flags = SDL_WINDOW_FULLSCREEN_DESKTOP;
	SDL_Window* win = SDL_CreateWindow("Archer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, win_flags);
	// SCREEN_WIDTH = 800;
	// SCREEN_HEIGHT = 600;
	// SDL_Window* win = SDL_CreateWindow("Archer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	if(!win){
		SDL_Quit();
		return 1;
	}

	Uint32 render_flags = SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC;
	rend = SDL_CreateRenderer(win, -1, render_flags);
	if(!rend){
		SDL_DestroyWindow(win);
		SDL_Quit();
		return 1;
	}
	SDL_SetRenderDrawBlendMode(rend, SDL_BLENDMODE_BLEND);
	
	SDL_Surface* tileset = IMG_Load("resources/archer-tileset.png");
	tex = SDL_CreateTextureFromSurface(rend, tileset);
	SDL_FreeSurface(tileset);

	TILES_Load_Tiles();

	char save_file[] = "resources/save.dat";
	TOOLS_SaveData save_data = {1,0};
	FILE* f = fopen(save_file, "r");
	if(f==NULL){
		TOOLS_Save_Data(save_file, &save_data);
	}
	else{
		TOOLS_Load_Data(save_file, &save_data);
	}
	int level_count = save_data.level_i;
	int level_start = 0;
	int game_start = 1;

	PLAYER_Player player = PLAYER_Create_Player();
	int key;

	TTF_Init();
	font = TTF_OpenFont("resources/Gelio Fasolada.ttf", 50);
	SDL_Color text_color = {252, 3, 215};

	elapsed = 0.016f;
	char fps_str[10];
	// int fps = 60;

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 0, 2048);
	Mix_Music* backMusic = Mix_LoadMUS("resources/soundtrack.mp3");
	Mix_PlayMusic(backMusic, -1);

	int run = 1;
	while(run){

		Uint64 start = SDL_GetPerformanceCounter();

		SDL_Event event;
		while(SDL_PollEvent(&event)){
			switch(event.type){
				case SDL_QUIT:
					run = 0;
					break;
				case SDL_KEYDOWN:
					key = event.key.keysym.scancode;
					PLAYER_Key_Down_Player(&player, key);
					switch(key){
						case SDL_SCANCODE_ESCAPE:
							run = 0;
							break;
						default:
							break;
					}
					break;
				case SDL_KEYUP:
					key = event.key.keysym.scancode;
					PLAYER_Key_Up_Player(&player, key);
					switch(key){
						default:
							break;
					}
					break;
			}
		}

		SDL_RenderClear(rend);

		if(game_start){
			game_start = LEVELS_Menu();
		}
		else if(!level_start){
			level_start = LEVELS_level_0(&player);
		}
		else if(level_count==0){
			TOOLS_SDL_Text_RenderCopy(rend, font, "Game Over!", SCREEN_WIDTH/2-400, SCREEN_HEIGHT/7, 800, 300, (SDL_Color){176,27,27});
			SDL_Rect button = {SCREEN_WIDTH/2-200,SCREEN_HEIGHT/2,400,200};
			TOOLS_SDL_Text_RenderCopy(rend, font, "retry?", button.x, button.y, button.w, button.h, (SDL_Color){255,255,255});

			int mouse_x, mouse_y, buttons;
			buttons = SDL_GetMouseState(&mouse_x, &mouse_y);
			if(buttons & SDL_BUTTON(SDL_BUTTON_LEFT)){
				SDL_Rect mouse = {mouse_x-5, mouse_y-5, 10,10};
				if(TOOLS_Collide_Rect(mouse, button)){
					save_data.level_i = 1;
					TOOLS_Save_Data(save_file, &save_data);
					player = PLAYER_Create_Player();
					level_count = 1;
					level_start = 0;
				}
			}
		}
		else if(level_count==1){
			if(save_data.level_i!=1){
				save_data.level_i = 1;
				TOOLS_Save_Data(save_file, &save_data);
				level_start = 0;
			}
			else{
				level_count = LEVELS_level_1(&player);
			}
		}
		else if(level_count==2){
			if(save_data.level_i!=2){
				save_data.level_i = 2;
				TOOLS_Save_Data(save_file, &save_data);
				level_start = 0;
			}
			else{
				level_count = LEVELS_level_2(&player);
			}
		}
		else if(level_count==3){
			if(save_data.level_i!=3){
				save_data.level_i = 3;
				TOOLS_Save_Data(save_file, &save_data);
				level_start = 0;
			}
			else{
				level_count = LEVELS_level_3(&player);
			}
		}
		else{
			TOOLS_SDL_Text_RenderCopy(rend, font, "To Be Continued!", SCREEN_WIDTH/2-400, SCREEN_HEIGHT/7, 800, 300, (SDL_Color){176,27,27});
			SDL_Rect button = {SCREEN_WIDTH/2-200,SCREEN_HEIGHT/2,400,200};
			TOOLS_SDL_Text_RenderCopy(rend, font, "retry?", button.x, button.y, button.w, button.h, (SDL_Color){255,255,255});

			int mouse_x, mouse_y, buttons;
			buttons = SDL_GetMouseState(&mouse_x, &mouse_y);
			if(buttons & SDL_BUTTON(SDL_BUTTON_LEFT)){
				SDL_Rect mouse = {mouse_x-5, mouse_y-5, 10,10};
				if(TOOLS_Collide_Rect(mouse, button)){
					save_data.level_i = 1;
					TOOLS_Save_Data(save_file, &save_data);
					player = PLAYER_Create_Player();
					level_count = 1;
					level_start = 0;
				}
			}
		}

		// fps = (int)(1.0f/elapsed);
		// snprintf(fps_str, 10, "fps:%d", fps);
		TOOLS_SDL_Text_RenderCopy(rend, font, fps_str, 10, 10, 150, 80, text_color);
        SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
		SDL_RenderPresent(rend);
	
		Uint64 end = SDL_GetPerformanceCounter();
		elapsed = (end - start) / (float)SDL_GetPerformanceFrequency();
		// printf("fps %f\n", 1.0f/elapsed);
		// SDL_Delay(elapsed);
	}
	
	SDL_DestroyRenderer(rend);
	SDL_DestroyWindow(win);
	SDL_Quit();
	TTF_Quit();
	return 0;
}