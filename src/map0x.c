#include <SDL2/SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "comm.h"

static Image IMap0x[] = {

};

static int die(void);
static int init(void);
static int keydown(int);
static int keyup(int);
static int update(void);

Map Map0x = {
	IMap0x,
	die,
	init,
	keydown,
	keyup,
	update,
	NELEM(IMap0x)
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
