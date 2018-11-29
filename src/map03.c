#include <SDL2/SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "comm.h"

static Image IMap03[] = {
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
	/* house */
	{
		NULL,
		NULL,
		0,
		1,
		0,
		80,
		NOAFRAME|DYNAMIC,
		357,
		180,
		356,
		228,
		"house0"
	},
	/* wood notice */
	{
		NULL,
		NULL,
		0,
		1,
		0,
		80,
		NOAFRAME|DYNAMIC,
		745,
		265,
		263,
		144,
		"wnot0"
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
		0,
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

static int strnum;
static int strnmsg;
static int blockmove;

static int die(void);
static int init(void);
static int keydown(int);
static int keyup(int);
static int update(void);

static char *strmsg[][64] = {
	/* message board 01 */
	{
		"will happen soon, join the army to protect the nation.",
		"The king has announced that a new recruiting of soldiers",
		"News",
	},
	/* message board 02 */
	{
		"The king has announced an increase to taxes due to war.",
		"News",
	},
	/* message board 03 */
	{
		"the lost resources.",
		"for all the soldiers that we have lost and to recover",
		"The king has annouced that war needs to continue",
		"News",
	},
	/* message board 04 */
	{
		"and allowing internal problems to be solved internally.",
		"god's word, exempting the church from paying taxes",
		"The king has announced that will help spread",
		"News",
	},
	/* message board 05 */
	{
		"in this sacred event.",
		"bring your children to devote themselves to god",
		"The church has announced that baptism will occur soon,",
		"News",
	},
	/* message board 06 */
	{
		"probably a result of the lack of soldiers due to war.",
		"The complaints against theft and violence has increased,",
		"News",
	},
};

static int tabsize[] = { 3, 2, 4, 4, 4, 3 };

Map Map03 = {
	IMap03,
	die,
	init,
	keydown,
	keyup,
	update,
	NELEM(IMap03)
};

static void
startmsg(int n)
{
	blockmove = 1;

	Map03.img[5].opts  = ~NODRAW|NOAFRAME;
	Map03.img[6].opts &= ~NODRAW;

	strnmsg = n;
	strnum  = tabsize[n];

	image_text(&Map03.img[6], font, strmsg[strnmsg][--strnum]);
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
			image_text(&Map03.img[6], font,
			           strmsg[strnmsg][strnum-1]);
			if (--strnum < 0) {
				Map03.img[5].opts |= NODRAW;
				Map03.img[6].opts |= NODRAW;
				blockmove = 0;
			}
		}
		return 0;
	}

	switch (key) {
	case SDLK_LEFT:
		if (Map03.img[4].posx-5 <= -80)
			return 02;
		Map03.img[4].posx -= 5;
		if (++Map03.img[4].aframe >= Map03.img[4].frame)
			Map03.img[4].aframe = 3;
		break;
	case SDLK_RIGHT:
		Map03.img[4].posx += 5;
		if (++Map03.img[4].aframe >= Map03.img[4].frame/2)
			Map03.img[4].aframe = 0;
		break;
	case SDLK_UP:
		Map03.img[4].posy -= 5;
		break;
	case SDLK_DOWN:
		Map03.img[4].posy += 5;
		break;
	case SDLK_x:
		if (Map03.img[4].posx >= 155 && Map03.img[4].posx <= 170)
			return 4;

		if (Map03.img[4].posx >= 512 && Map03.img[4].posx <= 525)
			return 5;

		if (Map03.img[4].posx == 695)
			startmsg(0);

		if (Map03.img[4].posx == 735)
			startmsg(1);

		if (Map03.img[4].posx == 775)
			startmsg(2);

		if (Map03.img[4].posx == 820)
			startmsg(3);

		if (Map03.img[4].posx == 865)
			startmsg(4);

		if (Map03.img[4].posx == 905)
			startmsg(5);

		printf("x: %d\ny: %d\n\n", Map03.img[4].posx, Map03.img[4].posy);
		break;
	}

	return 0;
}

static int
keyup(int key)
{
	switch (key) {
	case SDLK_LEFT:
		Map03.img[4].aframe = 3;
		break;
	case SDLK_RIGHT:
		Map03.img[4].aframe = 0;
		break;
	}

	return 0;
}

static int
update(void)
{
	return 0;
}
