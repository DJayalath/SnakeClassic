#include "Food.h"

Food::Food()
{
	GenerateFood();
}

Food::~Food()
{
}

void Food::GenerateFood()
{
	m_x = GenRandom(RANDOM_MIN, RANDOM_MAX);
	m_y = GenRandom(RANDOM_MIN, RANDOM_MAX);
}

int Food::GenRandom(int min, int max)
{
	return min + (rand() % static_cast<int>(max - min + 1));
}
