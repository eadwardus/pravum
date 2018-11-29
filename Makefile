include config.mk

.SUFFIXES:
.SUFFIXES: .o .c

MOJS=\
	src/map00.o\
	src/map01.o\
	src/map02.o\
	src/map03.o\
	src/map04.o

BIN=src/main
SRC=$(BIN:=.c)
OBJ=$(BIN:=.o) src/draw.o $(MOJS)

all: $(BIN)
$(OBJ): config.mk

src/main: $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

.c.o:
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

clean:
	rm -f $(BIN) $(OBJ)

.PHONY:
	all clean
