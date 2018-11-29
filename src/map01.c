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
		1,
		0,
		100,
		NOAFRAME|NORECT,
		0,
		0,
		64,
		64,
		"bgh0"
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
		875,
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

static char *strmsg[] =
{
	"You should go pray for help and mercy.",
	"diseases, hunger and war has been tormenting this land.",
	"sadly we have been suffering with misfortunes",
	"A so good city, with a lot of good people",
};

static int strnum     = NELEM(strmsg);
static int blockmove  = 1;

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
	Map01.img[2].opts  = ~NODRAW|NOAFRAME;
	Map01.img[3].opts &= ~NODRAW;
	image_text(&Map01.img[3], font, strmsg[--strnum]);
	return 0;
}

static int
keydown(int key)
{
	if (blockmove) {
		if (key == SDLK_x) {
			image_text(&Map01.img[3], font, strmsg[strnum-1]);
			if (--strnum < 0) {
				Map01.img[2].opts |= NODRAW;
				Map01.img[3].opts |= NODRAW;
				blockmove = 0;
			}
		}
		return 0;
	}

	switch (key) {
	case SDLK_LEFT:
		if (Map01.img[1].posx-5 <= -45)
			break;
		Map01.img[1].posx -= 5;
		if (++Map01.img[1].aframe >= Map01.img[1].frame)
			Map01.img[1].aframe = 3;
		break;
	case SDLK_RIGHT:
		if (Map01.img[1].posx+5 >= 945)
			break;
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
		printf("x: %d\ny: %d\n\n", Map01.img[1].posx, Map01.img[1].posy);
		if (Map01.img[1].posx >= -20 && Map01.img[1].posx <= 40)
			return 2;
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
	return 0;
}
