#include <SDL2/SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "comm.h"

static Image IMap04[] = {
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
	/* couch */
	{
		NULL,
		NULL,
		0,
		1,
		0,
		80,
		NOAFRAME|DYNAMIC,
		365,
		285,
		256,
		128,
		"cch00"
	},
	/* fat00 */
	{
		NULL,
		NULL,
		0,
		1,
		0,
		80,
		NOAFRAME|DYNAMIC,
		490,
		300,
		128,
		128,
		"fat00"
	},
	/* chd00 */
	{
		NULL,
		NULL,
		0,
		1,
		0,
		80,
		NOAFRAME|DYNAMIC,
		360,
		300,
		128,
		128,
		"chd00"
	},
	/* fdg00 */
	{
		NULL,
		NULL,
		0,
		1,
		0,
		80,
		NOAFRAME|DYNAMIC,
		635,
		240,
		128,
		200,
		"fdg00"
	},
	/* bed */
	{
		NULL,
		NULL,
		0,
		1,
		0,
		80,
		NOAFRAME|DYNAMIC,
		755,
		305,
		256,
		128,
		"bed00"
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
		40,
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

static int blockmove;

static int die(void);
static int init(void);
static int keydown(int);
static int keyup(int);
static int update(void);

static char *strmsg[][64] = {
	/* CHD00 */
	{
		"Hi",
	},
	/* FAT00 */
	{
		"Hello",
	},
};

Map Map04 = {
	IMap04,
	die,
	init,
	keydown,
	keyup,
	update,
	NELEM(IMap04)
};

static void
startmsg(int n)
{
	blockmove = 1;

	Map04.img[7].opts  = NOAFRAME|~NODRAW;
	Map04.img[8].opts &= ~NODRAW;

	image_text(&Map04.img[8], font, strmsg[n][0]);
}

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
	if (blockmove) {
		if (key == SDLK_x) {
				Map04.img[7].opts |= NODRAW;
				Map04.img[8].opts |= NODRAW;
				blockmove = 0;
		}
		return 0;
	}
	switch (key) {
	case SDLK_LEFT:
		if (Map04.img[6].posx-5 <= -45)
			break;
		Map04.img[6].posx -= 5;
		if (++Map04.img[6].aframe >= Map04.img[6].frame)
			Map04.img[6].aframe = 3;
		break;
	case SDLK_RIGHT:
		if (Map04.img[6].posx+5 >= 945)
			break;
		Map04.img[6].posx += 5;
		if (++Map04.img[6].aframe >= Map04.img[6].frame/2)
			Map04.img[6].aframe = 0;
		break;
	case SDLK_UP:
		Map04.img[6].posy -= 5;
		break;
	case SDLK_DOWN:
		Map04.img[6].posy += 5;
		break;
	case SDLK_x:
		if (Map04.img[6].posx >= -20 && Map04.img[6].posx <= 40)
			return 3;
		if (Map04.img[6].posx == 360)
			startmsg(0);
		if (Map04.img[6].posx >= 480 && Map04.img[6].posx <= 500)
			startmsg(1);
		printf("x: %d\ny: %d\n\n", Map04.img[6].posx, Map04.img[6].posy);
		break;
	}

	return 0;
}

static int
keyup(int key)
{
	switch (key) {
	case SDLK_LEFT:
		Map04.img[6].aframe = 3;
		break;
	case SDLK_RIGHT:
		Map04.img[6].aframe = 0;
		break;
	}

	return 0;
}

static int
update(void)
{
	return 0;
}
