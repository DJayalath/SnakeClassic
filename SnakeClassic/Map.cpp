#include "Map.h"
#include "Display.h"
#include "Snake.h"
#include "Food.h"

#include <iostream> // REMOVE

Map::Map()
{
}

Map::~Map()
{
}

void Map::Draw(Display* display)
{
	for (int x = 0; x < 63; x++)
	{
		for (int y = 0; y < 63; y++)
		{
			switch (m_grid[ToIndex(x, y)])
			{
			case 1:
				display->DrawRect(x * 10, y * 10, x * 10 + 10, y * 10 + 10, GREEN);
				break;
			case 2:
				display->DrawRect(x * 10, y * 10, x * 10 + 10, y * 10 + 10, RED);
				break;
			}
		}
	}
}

int Map::MoveSnake()
{
	// Clear snake's current position
	for (int i = 0; i < m_snake.GetSize(); i++)
		m_grid[ToIndex(m_snake.GetSnake(i, 0), m_snake.GetSnake(i, 1))] = 0;

	// For new x and y offsets according to direction of movement
	int dx, dy;

	bool extend = false;
	int tail_x = m_snake.GetSnake(m_snake.GetSize() - 1, 0);
	int tail_y = m_snake.GetSnake(m_snake.GetSize() - 1, 1);

	for (int i = m_snake.GetSize() - 1; i >= 0; i--)
	{
		// Let snake body follow the piece in front (so body follows the head in sequence)
		if (i == HEAD)
		{
			// Let the head follow the current direction
			dx = m_snake.GetDX();
			dy = m_snake.GetDY();

			// Set new snake coordinates using modulo so snake can warp from end of sides
			m_snake.GetSnake(i, 0) = ((m_snake.GetSnake(i, 0) + dx) + 64) % 64;
			m_snake.GetSnake(i, 1) = ((m_snake.GetSnake(i, 1) + dy) + 64) % 64;

			// Check if head touches part of snake
			for (int i = 1; i < m_snake.GetSize(); i++)
			{
				if (m_snake.GetSnake(i, 0) == m_snake.GetSnake(0, 0) &&
					m_snake.GetSnake(i, 1) == m_snake.GetSnake(0, 1))
				{
					return 1;
				}
			}

			// If head touches food, we should extend the snake
			if (m_grid[ToIndex(m_snake.GetSnake(i, 0), m_snake.GetSnake(i, 1))] == 2)
				extend = true;
		}
		else
		{
			// Calculate distance to body piece in front
			dx = m_snake.GetSnake(i - 1, 0) - m_snake.GetSnake(i, 0);
			dy = m_snake.GetSnake(i - 1, 1) - m_snake.GetSnake(i, 1);

			// Set new snake coordinates using modulo so snake can warp from end of sides
			m_snake.GetSnake(i, 0) = ((m_snake.GetSnake(i, 0) + dx) + 64) % 64;
			m_snake.GetSnake(i, 1) = ((m_snake.GetSnake(i, 1) + dy) + 64) % 64;
		}

	}

	// Extend the snake by placing a body piece where the tail was before it moved and generate a new piece of food
	if (extend)
	{
		m_snake.GetSnake(m_snake.GetSize(), 0) = tail_x;
		m_snake.GetSnake(m_snake.GetSize(), 1) = tail_y;
		m_snake.GetSize() += 1;
		m_food.GenerateFood();
	}

	return 0;
}

void Map::SetDirection(direction dir)
{
	switch (dir)
	{
	case UP:
		if (m_snake.GetDirection() != DOWN)
			m_snake.SetDirection(UP);
		break;
	case DOWN:
		if (m_snake.GetDirection() != UP)
			m_snake.SetDirection(DOWN);
		break;
	case LEFT:
		if (m_snake.GetDirection() != RIGHT)
			m_snake.SetDirection(LEFT);
		break;
	case RIGHT:
		if (m_snake.GetDirection() != LEFT)
			m_snake.SetDirection(RIGHT);
		break;
	}
}

void Map::LoadSnake()
{
	// Loads snake coordinates onto rendering grid
	for (int i = 0; i < m_snake.GetSize(); i++)
		m_grid[ToIndex(m_snake.GetSnake(i, 0), m_snake.GetSnake(i, 1))] = 1;
}

void Map::LoadFood()
{
	m_grid[ToIndex(m_food.GetX(), m_food.GetY())] = 2;
}

int Map::ToIndex(int x, int y)
{
	return x + (64 - 1 - y) * 64;
}
