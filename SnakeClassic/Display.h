#pragma once

// --- Includes ---

#include "SDL/include/SDL.h"
#include "SDL/SDL_GfxPrimitives/SDL_gfxPrimitives.h"

// --- Enums ---

enum colour { BLACK, RED, GREEN, BLUE, CYAN, MAGENTA, YELLOW, WHITE, COLOUR_MAX };

class Display
{
public:
	Display();

	void DrawRect(int ul_x, int ul_y, int lr_x, int lr_y, enum colour c);
	void Clear();
	int GetHeight();
	int GetWidth();
	int InitSDL();
	bool GetKey(int sc);
	void Update();
	bool& Quit();

private:
	bool key_status[1024];
	bool m_quit;
};

