#include <stddef.h>

#include <SDL2/SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "comm.h"

static Image IMap01[] = {
	/* background */
	{
		NULL,
		NULL,
		0,
		4,
		0,
		100,
		NOAFRAME|NORECT,
		0,
		0,
		64,
		64,
		"bg01"
	},
	/* main character */
	{
		NULL,
		NULL,
		0,
		6,
		0,
		80,
		NOAFRAME|DYNAMIC,
		300,
		725,
		128,
		128,
		"char"
	},
	/* text background */
	{
		NULL,
		NULL,
		0,
		1,
		0,
		0,
		NODRAW,
		300,
		725,
		128,
		128,
		"msg"
	},
	/* text */
	{
		NULL,
		NULL,
		0,
		1,
		0,
		0,
		NOINIT|NODRAW|NOAFRAME,
		530,
		900,
		500,
		64,
		NULL
	},
};

static int die(void);
static int init(void);
static int keydown(int);
static int keyup(int);
static int update(void);

Map Map01 = {
	IMap01,
	die,
	init,
	keydown,
	keyup,
	update,
	NELEM(IMap01)
};

static int
die(void)
{
	return 0;
}

static int
init(void)
{
	return 0;
}

static int
keydown(int key)
{
	switch (key) {
	case SDLK_LEFT:
		Map01.img[1].posx -= 5;
		if (++Map01.img[1].aframe >= Map01.img[1].frame)
			Map01.img[1].aframe = 3;
		break;
	case SDLK_RIGHT:
		Map01.img[1].posx += 5;
		if (++Map01.img[1].aframe >= Map01.img[1].frame/2)
			Map01.img[1].aframe = 0;
		break;
	case SDLK_UP:
		Map01.img[1].posy -= 5;
		break;
	case SDLK_DOWN:
		Map01.img[1].posy += 5;
		break;
	case SDLK_x:
		Map01.img[2].opts |= NODRAW;
		Map01.img[3].opts |= NODRAW;
		break;
	}

	return 0;
}

static int
keyup(int key)
{
	switch (key) {
	case SDLK_LEFT:
		Map01.img[1].aframe = 3;
		break;
	case SDLK_RIGHT:
		Map01.img[1].aframe = 0;
		break;
	}
	return 0;
}

static int
update(void)
{
	if (Map01.img[1].posx == 970) {
		if (Map01.img[0].aframe < 3)
			Map01.img[0].aframe++;
		if (Map01.img[0].aframe > 1)
			return 0;
		Map01.img[2].opts   = ~NODRAW;
		Map01.img[3].opts  &= ~NODRAW;
		image_text(&Map01.img[3], font, "Videam cum oculis deorum");
	}
	return 0;
}
