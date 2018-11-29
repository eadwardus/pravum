#define NELEM(a)  (sizeof((a))/sizeof((a)[0]))
#define GETTIME() (clock() / (CLOCKS_PER_SEC / 1000))

enum {
	DYNAMIC  = 1 << 0,
	NOAFRAME = 1 << 1,
	NODRAW   = 1 << 2,
	NOINIT   = 1 << 3,
	NORECT   = 1 << 4
};

typedef struct Node Node;

struct Node {
	Node *np;
	void *data;
};

typedef struct {
	SDL_Texture *texture;  /* texture           */
	SDL_Surface **surface; /* array of surfaces */
	int         aframe;    /* current frame     */
	int         frame;     /* number of frames  */
	int         time;      /* time before delay */
	int         delay;     /* delay time        */
	unsigned    opts;      /* flags             */
	int         posx;      /* position x        */
	int         posy;      /* position y        */
	int         shapex;    /* shape x size      */
	int         shapey;    /* shape y size      */
	char        *path;     /* image name        */
} Image;

typedef struct {
	Image *img;
	int   (*die)(void);
	int   (*init)(void);
	int   (*keydown)(int);
	int   (*keyup)(int);
	int   (*update)(void);
	int    nimg;
} Map;

extern TTF_Font  *font;
extern Mix_Music *music;

/* draw.c
 * */
int  image_init(Image *);
int  image_draw(SDL_Renderer *, Image *);
void image_free(Image *);
int  image_text(Image *, TTF_Font *, const char *);

extern Map Map00;
extern Map Map01;
extern Map Map02;
extern Map Map03;
extern Map Map04;

