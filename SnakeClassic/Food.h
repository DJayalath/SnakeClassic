#pragma once

#include <random>

class Food
{
public:
	Food();
	~Food();

	void GenerateFood();

	int GetX() { return m_x; }
	int GetY() { return m_y; }

private:
	int GenRandom(int max, int min);

	const int RANDOM_MIN = 2;
	const int RANDOM_MAX = 62;
	int m_x, m_y;
};

