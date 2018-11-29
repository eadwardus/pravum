#include <SDL2/SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "comm.h"

static Image IMap02[] = {
	/* background */
	{
		NULL,
		NULL,
		0,
		1,
		0,
		100,
		NOAFRAME|NORECT,
		0,
		0,
		64,
		64,
		"bg01"
	},
	/* house */
	{
		NULL,
		NULL,
		0,
		1,
		0,
		80,
		NOAFRAME|DYNAMIC,
		0,
		180,
		356,
		228,
		"house0"
	},
	/* character */
	{
		NULL,
		NULL,
		0,
		6,
		0,
		80,
		NOAFRAME|DYNAMIC,
		155,
		300,
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
		NODRAW|NOAFRAME,
		0,
		0,
		0,
		0,
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
		20,
		420,
		0,
		0,
		NULL
	},
};

static int die(void);
static int init(void);
static int keydown(int);
static int keyup(int);
static int update(void);

Map Map02 = {
	IMap02,
	die,
	init,
	keydown,
	keyup,
	update,
	NELEM(IMap02)
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
		if (Map02.img[2].posx-5 <= -45)
			break;
		Map02.img[2].posx -= 5;
		if (++Map02.img[2].aframe >= Map02.img[2].frame)
			Map02.img[2].aframe = 3;
		break;
	case SDLK_RIGHT:
		if (Map02.img[2].posx+5 >= 975)
			return 3;
		Map02.img[2].posx += 5;
		if (++Map02.img[2].aframe >= Map02.img[2].frame/2)
			Map02.img[2].aframe = 0;
		break;
	case SDLK_UP:
		Map02.img[2].posy -= 5;
		break;
	case SDLK_DOWN:
		Map02.img[2].posy += 5;
		break;
	case SDLK_x:
		printf("x: %d\ny: %d\n\n", Map02.img[2].posx, Map02.img[2].posy);
		break;
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
