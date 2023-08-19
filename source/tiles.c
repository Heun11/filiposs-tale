#include"tiles.h"

SDL_Rect archer_right[3];
SDL_Rect archer_left[3];
SDL_Rect bricks[9];
SDL_Rect woods[9];
SDL_Rect backBrick;
SDL_Rect doors[2];
SDL_Rect arrow[2];
SDL_Rect barrel;
SDL_Rect box;
SDL_Rect moss;
SDL_Rect spikes[4];
SDL_Rect target[2];
SDL_Rect rat[2];
SDL_Rect banner;
SDL_Rect chains;
SDL_Rect woodBricks[4];
SDL_Rect grid;
SDL_Rect torch[2];
SDL_Rect harphy[2];
SDL_Rect ghost;

void TILES_Load_Tiles()
{
    archer_right[0] = TOOLS_Get_Image_Src(0, 0, TILE_SIZE_REAL, TILE_SIZE_REAL);
    archer_right[1] = TOOLS_Get_Image_Src(1, 0, TILE_SIZE_REAL, TILE_SIZE_REAL);
    archer_right[2] = TOOLS_Get_Image_Src(2, 0, TILE_SIZE_REAL, TILE_SIZE_REAL);
	
    archer_left[0] = TOOLS_Get_Image_Src(3, 0, TILE_SIZE_REAL, TILE_SIZE_REAL);
    archer_left[1] = TOOLS_Get_Image_Src(4, 0, TILE_SIZE_REAL, TILE_SIZE_REAL);
    archer_left[2] = TOOLS_Get_Image_Src(5, 0, TILE_SIZE_REAL, TILE_SIZE_REAL);
	
	bricks[0] =	TOOLS_Get_Image_Src(0, 1, TILE_SIZE_REAL, TILE_SIZE_REAL);
	bricks[1] = TOOLS_Get_Image_Src(1, 1, TILE_SIZE_REAL, TILE_SIZE_REAL);
	bricks[2] = TOOLS_Get_Image_Src(2, 1, TILE_SIZE_REAL, TILE_SIZE_REAL);
	bricks[3] = TOOLS_Get_Image_Src(3, 1, TILE_SIZE_REAL, TILE_SIZE_REAL);
	bricks[4] = TOOLS_Get_Image_Src(4, 1, TILE_SIZE_REAL, TILE_SIZE_REAL);
	bricks[5] = TOOLS_Get_Image_Src(0, 2, TILE_SIZE_REAL, TILE_SIZE_REAL);
	bricks[6] = TOOLS_Get_Image_Src(1, 2, TILE_SIZE_REAL, TILE_SIZE_REAL);
	bricks[7] = TOOLS_Get_Image_Src(2, 2, TILE_SIZE_REAL, TILE_SIZE_REAL);
	bricks[8] = TOOLS_Get_Image_Src(3, 2, TILE_SIZE_REAL, TILE_SIZE_REAL);

    woods[0] =TOOLS_Get_Image_Src(0, 3, TILE_SIZE_REAL, TILE_SIZE_REAL);
	woods[1] = TOOLS_Get_Image_Src(1, 3, TILE_SIZE_REAL, TILE_SIZE_REAL);
	woods[2] = TOOLS_Get_Image_Src(2, 3, TILE_SIZE_REAL, TILE_SIZE_REAL);
	woods[3] = TOOLS_Get_Image_Src(3, 3, TILE_SIZE_REAL, TILE_SIZE_REAL);
	woods[4] = TOOLS_Get_Image_Src(4, 3, TILE_SIZE_REAL, TILE_SIZE_REAL);
	woods[5] = TOOLS_Get_Image_Src(0, 4, TILE_SIZE_REAL, TILE_SIZE_REAL);
	woods[6] = TOOLS_Get_Image_Src(1, 4, TILE_SIZE_REAL, TILE_SIZE_REAL);
	woods[7] = TOOLS_Get_Image_Src(2, 4, TILE_SIZE_REAL, TILE_SIZE_REAL);
	woods[8] = TOOLS_Get_Image_Src(3, 4, TILE_SIZE_REAL, TILE_SIZE_REAL);

	backBrick = TOOLS_Get_Image_Src(7, 3, TILE_SIZE_REAL, TILE_SIZE_REAL);

	doors[0] = TOOLS_Get_Image_Src(6, 0, TILE_SIZE_REAL, TILE_SIZE_REAL);
	doors[1] = TOOLS_Get_Image_Src(7, 0, TILE_SIZE_REAL, TILE_SIZE_REAL);

	barrel =  TOOLS_Get_Image_Src(5, 1, TILE_SIZE_REAL, TILE_SIZE_REAL);

	box =  TOOLS_Get_Image_Src(6, 1, TILE_SIZE_REAL, TILE_SIZE_REAL);

	moss =  TOOLS_Get_Image_Src(7, 1, TILE_SIZE_REAL, TILE_SIZE_REAL);

	spikes[0] = TOOLS_Get_Image_Src(4, 2, TILE_SIZE_REAL, TILE_SIZE_REAL);
	spikes[1] = TOOLS_Get_Image_Src(5, 2, TILE_SIZE_REAL, TILE_SIZE_REAL);
	spikes[2] = TOOLS_Get_Image_Src(6, 2, TILE_SIZE_REAL, TILE_SIZE_REAL);
	spikes[3] = TOOLS_Get_Image_Src(7, 2, TILE_SIZE_REAL, TILE_SIZE_REAL);

	target[0] = TOOLS_Get_Image_Src(5, 3, TILE_SIZE_REAL, TILE_SIZE_REAL);
	target[1] = TOOLS_Get_Image_Src(6, 3, TILE_SIZE_REAL, TILE_SIZE_REAL);

	rat[0] = TOOLS_Get_Image_Src(6, 4, TILE_SIZE_REAL, TILE_SIZE_REAL);
	rat[1] = TOOLS_Get_Image_Src(7, 4, TILE_SIZE_REAL, TILE_SIZE_REAL);

	chains = TOOLS_Get_Image_Src(4, 4, TILE_SIZE_REAL, TILE_SIZE_REAL);
	
	banner = TOOLS_Get_Image_Src(5, 4, TILE_SIZE_REAL, TILE_SIZE_REAL);

	woodBricks[0] = TOOLS_Get_Image_Src(0, 5, TILE_SIZE_REAL, TILE_SIZE_REAL);
	woodBricks[1] = TOOLS_Get_Image_Src(1, 5, TILE_SIZE_REAL, TILE_SIZE_REAL);
	woodBricks[2] = TOOLS_Get_Image_Src(2, 5, TILE_SIZE_REAL, TILE_SIZE_REAL);
	woodBricks[3] = TOOLS_Get_Image_Src(3, 5, TILE_SIZE_REAL, TILE_SIZE_REAL);

	arrow[0] = TOOLS_Get_Image_Src(4, 5, TILE_SIZE_REAL, TILE_SIZE_REAL);
	arrow[1] = TOOLS_Get_Image_Src(5, 5, TILE_SIZE_REAL, TILE_SIZE_REAL);

	grid = TOOLS_Get_Image_Src(6, 5, TILE_SIZE_REAL, TILE_SIZE_REAL);

	torch[0] = TOOLS_Get_Image_Src(6, 5, TILE_SIZE_REAL, TILE_SIZE_REAL);
	torch[1] = TOOLS_Get_Image_Src(7, 5, TILE_SIZE_REAL, TILE_SIZE_REAL);

	harphy[0] = TOOLS_Get_Image_Src(5, 3, TILE_SIZE_REAL, TILE_SIZE_REAL);
	harphy[1] = TOOLS_Get_Image_Src(5, 4, TILE_SIZE_REAL, TILE_SIZE_REAL);

	ghost = TOOLS_Get_Image_Src(5, 5, TILE_SIZE_REAL, TILE_SIZE_REAL);
}