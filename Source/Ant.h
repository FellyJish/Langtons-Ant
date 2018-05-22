#pragma once
#include "SFML\Graphics.hpp"

enum class Direction
{
	Right,
	Left
};

struct FacingDirection
{
	int m_X, m_Y;
};

class Ant
{
	unsigned m_FacingIndex = 0;
	std::vector<FacingDirection> m_FacingsVec{ 
		FacingDirection{ 0, -1 },
		FacingDirection{ 1, 0 },
		FacingDirection{ 0, 1 },
		FacingDirection{ -1, 0 }
	};

private:
	sf::Color GetRandomColor();

public:
	void SetPosition(int x, int y);
	int m_XPos, m_YPos;
	void Ant::Turn(Direction AntDir);
	FacingDirection m_AntFacing{ 0, -1 };
	sf::Color m_AntColor;
	Ant(int x, int y);
	~Ant();
};

