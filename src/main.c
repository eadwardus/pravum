#include <err.h>
#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "comm.h"

#define HEIGHT 512
#define WIDTH  1024
#define WINNAME "pravum"

static Map *maps[] = {
	&Map00,
	&Map01,
	&Map02,
	&Map03,
	&Map04,
};

TTF_Font  *font;
Mix_Music *music;

int
main(void)
{
	SDL_Event    ev;
	SDL_Renderer *ren;
	SDL_Window   *win;
	int          n, m, i;

	n = 3; /* rep */
	m = 0;

	if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) < 0)
		errx(1, "SDL_Init: %s", SDL_GetError());

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) < 0)
		errx(1, "SDL_OpenAudio: %s", Mix_GetError());

	if (Mix_Init(MIX_INIT_OGG) != MIX_INIT_OGG)
		errx(1, "MIX_Init: %s", Mix_GetError());

	if (TTF_Init() < 0)
		errx(1, "TTF_Init: %s", TTF_GetError());

	if (!(win = SDL_CreateWindow(WINNAME, SDL_WINDOWPOS_CENTERED,
	    SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0)))
		errx(1, "SDL_CreateWindow: %s", SDL_GetError());
	if (!(ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED)))
		errx(1, "SDL_CreateRenderer: %s", SDL_GetError());

	if (!(font = TTF_OpenFont("res/Vera.ttf", 32)))
		errx(1, "TTF_OpenFont: %s", TTF_GetError());

init:
	m = n;

	for (i = 0; i < maps[m]->nimg; i++)
		if (image_init(&maps[m]->img[i]))
			err(1, "img_init %s %d %d", maps[m]->img[i].path, m, i);

	maps[m]->init();

	for (;;) {
		while (SDL_PollEvent(&ev)) {
			switch (ev.type) {
			case SDL_KEYUP:
				maps[m]->keyup(ev.key.keysym.sym);
				break;
			case SDL_KEYDOWN:
				if ((n = maps[m]->keydown(ev.key.keysym.sym)))
					goto die;
				break;
			case SDL_QUIT:
				goto end;
			}
		}

		maps[m]->update();

		SDL_RenderClear(ren);
		for (i = 0; i < maps[m]->nimg; i++)
			if (image_draw(ren, &maps[m]->img[i]))
				err(1, "img_draw");
		SDL_RenderPresent(ren);
		continue;
die:
		for (i = 0; i < maps[m]->nimg; i++)
			image_free(&maps[m]->img[i]);
		maps[m]->die();
		if (n < 0) goto end;
		goto init;
	}

end:
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();
	TTF_Quit();
	Mix_CloseAudio();
	Mix_Quit();
	return 0;
}
