#pragma once

enum direction { UP, LEFT, DOWN, RIGHT };
enum piece {HEAD};

class Snake
{
public:
	Snake();
	~Snake();

	int& GetSnake(int index, int coordinate) { return m_pos_queue[index][coordinate]; }
	int& GetSize() { return m_size; }
	int GetDX() { return m_dx; }
	int GetDY() { return m_dy; }
	direction GetDirection() { return m_dir; }
	void SetDirection(direction dir);

private:
	int m_pos_queue[256][2] = { 0 };
	int m_size = 0;
	direction m_dir;
	int m_dx, m_dy;
};

