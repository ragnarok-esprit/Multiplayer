#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>

typedef struct image
{ 
	SDL_Rect positiond;
	SDL_Rect positionc;
        SDL_Surface* back;
           
}image;


void init_splitscreen(image* I1,image *I2,int screenw);
