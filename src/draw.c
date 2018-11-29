#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <SDL2/SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "comm.h"

int
image_init(Image *img)
{
	int  i;
	char path[NAME_MAX];

	if (!(img->surface = malloc(img->frame * sizeof(img->surface))))
		return -1;

	memset(img->surface, 0, img->frame * sizeof(img->surface));

	if (img->opts & NOINIT)
		return 0;

	for (i = 0; i < img->frame; i++) {
		snprintf(path, sizeof(path), "res/%s_%d.bmp", img->path, i);
		if (!(img->surface[i] = SDL_LoadBMP(path)))
			return -1;
	}

	return 0;
}

int
image_draw(SDL_Renderer *ren, Image *img)
{
	SDL_Rect *ps,  *pd;
	SDL_Rect src,  dst;

	if (img->opts & NODRAW)
		return 0;

	ps  = &src;
	src = (SDL_Rect){
		0,
		0,
		img->shapex,
		img->shapey,
	};

	pd  = &dst;
	dst = (SDL_Rect){
		img->posx,
		img->posy,
		img->shapex,
		img->shapey,
	};

	if (!(img->opts & NOAFRAME) &&
	    ++img->aframe >= img->frame)
		img->aframe = 0;

	if (img->time + img->delay >= GETTIME())
		goto draw;

	img->time = GETTIME();

	if (img->texture) {
		SDL_DestroyTexture(img->texture);
		img->texture = NULL;
	}

	if (!(img->texture = SDL_CreateTextureFromSurface(ren,
	    img->surface[img->aframe])))
		return -1;

draw:
	if (img->opts & NORECT)
		ps = pd = NULL;

	SDL_RenderCopy(ren, img->texture, ps, pd);

	return 0;
}

void
image_free(Image *img)
{
	int i;

	SDL_DestroyTexture(img->texture);
	img->texture = NULL;

	for (i = 0; i < img->frame; i++)
		SDL_FreeSurface(img->surface[i]);
	img->surface = NULL;
}

int
image_text(Image *img, TTF_Font *fon, const char *txt)
{
	SDL_Color color;
	int w, h;

	color = (SDL_Color){
		255,
		255,
		255
	};

	TTF_SizeText(font, txt, &w, &h);
	img->shapex = w;
	img->shapey = h;

	if (img->surface[0])
		SDL_FreeSurface(img->surface[0]);

	if (!(img->surface[0] = TTF_RenderText_Solid(fon, txt, color)))
		return -1;

	return 0;
}
