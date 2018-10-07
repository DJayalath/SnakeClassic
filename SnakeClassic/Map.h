#pragma once

#include "Snake.h"
#include "Food.h"

class Display;
class Snake;
class Food;

enum status {STATUS_RUNNING, STATUS_GAMEOVER};

class Map
{
public:
	Map();
	~Map();

	int MoveSnake();
	void SetDirection(direction dir);
	void LoadSnake();
	void LoadFood();
	void Draw(Display* display);
private:
	Snake m_snake;
	Food m_food;
	int m_grid[64*64] = { 0 };

	int ToIndex(int x, int y);
};

