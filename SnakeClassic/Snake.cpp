#include "Snake.h"

Snake::Snake()
{
	SetDirection(LEFT);
	for (int i = 0; i < 4; i++)
	{
		m_pos_queue[i][0] = 30 + i;
		m_pos_queue[i][1] = 30;
		m_size += 1;
	}
}


Snake::~Snake()
{
}

void Snake::SetDirection(direction dir)
{
	m_dir = dir;
	switch (dir)
	{
	case UP:
		m_dx = 0;
		m_dy = -1;
		break;
	case DOWN:
		m_dx = 0;
		m_dy = 1;
		break;
	case LEFT:
		m_dx = -1;
		m_dy = 0;
		break;
	case RIGHT:
		m_dx = 1;
		m_dy = 0;
		break;
	}
}
