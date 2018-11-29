AR= ar
CC= cc
RANLIB= ranlib

CPPFLAGS += -D_DEFAULT_SOURCE -D_BSD_SOURCE -D_XOPEN_SOURCE=700 -D_FILE_OFFSET_BITS=64
CFLAGS   += -std=c99 -Wall -pedantic `sdl2-config --cflags`
LDFLAGS  += -Os
#LDFLAGS  += -O0 -g
LDLIBS   += `sdl2-config --libs` -lSDL2 -lSDL2_mixer -lSDL2_ttf