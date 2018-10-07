#include "Display.h"
#include "Map.h"
#include "Snake.h"
#include "Food.h"

#include <windows.h>
#include <iostream>

#undef main

void HandleEvents(SDL_Event* e, Display* display, Map* map);

int main(int argc, char **argv)
{
	Display display;
	SDL_Event event;

	Map map;

	DWORD time = GetTickCount();
	DWORD new_time;

	while (!display.Quit())
	{
		display.Clear();

		HandleEvents(&event, &display, &map);

		// Move snake every ~200ms
		new_time = GetTickCount();
		if (new_time - time > 200)
		{
			time = new_time;
			if (map.MoveSnake() == STATUS_GAMEOVER)
			{
				display.Quit() = true;
				std::cout << "You Lose!" << std::endl;
			}
		}

		map.LoadSnake();
		map.LoadFood();
		map.Draw(&display);

		display.Update();
	}
	
	return 0;
}

void HandleEvents(SDL_Event* e, Display* display, Map* map)
{
	while (SDL_PollEvent(e))
	{
		switch (e->type)
		{
		case SDL_KEYDOWN:
			switch (e->key.keysym.sym)
			{
			case SDLK_ESCAPE:
				display->Quit() = true;
				break;
			case SDLK_w:
				map->SetDirection(UP);
				break;
			case SDLK_a:
				map->SetDirection(LEFT);
				break;
			case SDLK_s:
				map->SetDirection(DOWN);
				break;
			case SDLK_d:
				map->SetDirection(RIGHT);
				break;

			}
			break;
		case SDL_QUIT:
			display->Quit() = true;
			break;
		}
	}
}