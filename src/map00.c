#include <stddef.h>

#include <SDL2/SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "comm.h"

static Image IMap00[] = {
	/* background */
	{
		NULL,
		NULL,
		0,
		1,
		0,
		3,
		NORECT,
		0,
		0,
		64,
		64,
		"bg00"
	},
	/* title */
	{
		NULL,
		NULL,
		0,
		1,
		0,
		0,
		NORECT,
		0,
		0,
		0,
		0,
		"t00"
	},
	/* buttons  */
	{
		NULL,
		NULL,
		0,
		2,
		0,
		0,
		NOAFRAME|NORECT,
		0,
		0,
		0,
		0,
		"btn00"
	}
};

static int die(void);
static int init(void);
static int keydown(int);
static int keyup(int);
static int update(void);

Map Map00 = {
	IMap00,
	die,
	init,
	keydown,
	keyup,
	update,
	NELEM(IMap00)
};

static int
die(void)
{
	Mix_FreeMusic(music);
	return 0;
}

static int
init(void)
{
	if (!(music = Mix_LoadMUS("res/001.ogg")))
		return -1;

	Mix_PlayMusic(music, -1);

	return 0;
}

static int
keydown(int key)
{
	switch (key) {
	case SDLK_UP:
		if (--Map00.img[2].aframe < 0)
			Map00.img[2].aframe = Map00.img[2].frame-1;
		break;
	case SDLK_DOWN:
		if (++Map00.img[2].aframe >= Map00.img[2].frame)
			Map00.img[2].aframe = 0;
		break;
	case SDLK_x:
		switch (Map00.img[2].aframe) {
		case 0:
			return 1;
		case 1:
			return -1;
		}
	}
	return 0;
}

static int
keyup(int key)
{
	return 0;
}

static int
update(void)
{
	return 0;
}
