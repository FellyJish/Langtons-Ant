#include "Ant.h"
#include <chrono>
#include <random>

namespace antcolourseed
{
	std::mt19937 mersenneRand(std::time(NULL));
}

sf::Color Ant::GetRandomColor()
{
	std::uniform_int_distribution<unsigned> distribution(0, 255);

	unsigned randomR = distribution(antcolourseed::mersenneRand);
	unsigned randomG = distribution(antcolourseed::mersenneRand);
	unsigned randomB = distribution(antcolourseed::mersenneRand);

	return sf::Color(randomR, randomG, randomB);
}

Ant::Ant(int x, int y) : m_XPos(x), m_YPos(y), m_AntColor(GetRandomColor()) {}

void Ant::Turn(Direction AntDir)
{
	switch (AntDir)
	{
	case Direction::Right:
	{
		if (m_FacingIndex == m_FacingsVec.size() - 1)
		{
			m_FacingIndex = 0;
			m_AntFacing = m_FacingsVec[m_FacingIndex];
		}
		else
		{
			++m_FacingIndex;
			m_AntFacing = m_FacingsVec[m_FacingIndex];
		}
	}
	break;
	case Direction::Left:
	{
		if (m_FacingIndex == 0)
		{
			m_FacingIndex = m_FacingsVec.size() - 1;
			m_AntFacing = m_FacingsVec[m_FacingIndex];
		}
		else
		{
			--m_FacingIndex;
			m_AntFacing = m_FacingsVec[m_FacingIndex];
		}
	}
	break;
	}
}

void Ant::SetPosition(int x, int y)
{
	m_XPos = x;
	m_YPos = y;
}

Ant::~Ant()
{

}
