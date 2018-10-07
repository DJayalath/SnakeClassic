#include "Display.h"

static SDL_Surface *m_screen;
static Uint32 m_colours[COLOUR_MAX] =
{ 0x000000ff, 0xff0000ff, 0x00ff00ff, 0x0000ffff,
  0x00ffffff, 0xff00ffff, 0xffff00ff, 0xffffffff };

Display::Display() : m_quit(false)
{
	for (int i = 0; i < 1024; i++)
		key_status[i] = false;

	InitSDL();
}

void Display::Clear()
{
	boxColor(m_screen, 0, 0, m_screen->w - 1, m_screen->h - 1, m_colours[BLACK]);
}

/*
--------------------------------------------------
	Parameters:
	>> ul_x, ul_y = Upper left corner of rectangle
	>> lr_x, lr_y = Lower right corner of rectangle
	>> c = Colour of rectangle
--------------------------------------------------
*/
void Display::DrawRect(int ul_x, int ul_y, int lr_x, int lr_y, enum colour c)
{
	boxColor(m_screen, ul_x, ul_y, lr_x, lr_y - 1, m_colours[c]);
}

int Display::GetHeight()
{
	return m_screen->h;
}

int Display::GetWidth()
{
	return m_screen->w;
}

// Swap Buffers
void Display::Update()
{
	SDL_Flip(m_screen);
}

bool Display::GetKey(int sc)
{
	return key_status[sc];
}

bool& Display::Quit()
{
	return m_quit;
}

int Display::InitSDL()
{
	const SDL_VideoInfo *info;
	Uint8  video_bpp;
	Uint32 video_flags;

	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		fprintf(stderr, "Couldn't initialize SDL: %s\n", SDL_GetError());
		return 1;
	}
	atexit(SDL_Quit);

	// Alpha blending doesn't work well at 8-bit color
	info = SDL_GetVideoInfo();
	if (info->vfmt->BitsPerPixel > 8) {
		video_bpp = info->vfmt->BitsPerPixel;
	}
	else {
		video_bpp = 16;
	}
	video_flags = SDL_SWSURFACE | SDL_DOUBLEBUF;

	// Set 640x640 video mode
	if ((m_screen = SDL_SetVideoMode(640, 640, video_bpp, video_flags)) == NULL) {
		fprintf(stderr, "Couldn't set %ix%i video mode: %s\n", 640, 640, SDL_GetError());
		return 2;
	}

	SDL_WM_SetCaption("Snake Classic", NULL);

	return 0;
}
