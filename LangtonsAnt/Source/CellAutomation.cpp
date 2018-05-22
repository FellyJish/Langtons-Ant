#include "CellAutomation.h"
#include <random>

CellAutomation::CellAutomation(const Config& c) :
	m_Config(c),
	m_Board(m_Config),
	m_Window(sf::VideoMode(m_Config.uScreenWidth, m_Config.uScreenHeight),"Langtons Ant"),
	m_CellsVec(m_Config.uSimHeight * m_Config.uSimWidth)
{
	m_pAntsVec.reserve(m_Config.uNumAnts);
	std::mt19937 rng(std::time(nullptr));
	std::uniform_int_distribution<int> xPositionDistribution(0, m_Config.uSimWidth - 1);
	std::uniform_int_distribution<int> yPositionDistribution(0, m_Config.uSimHeight - 1);

	CellForEach([&](unsigned x, unsigned y)
	{	
		Cell& cell = m_CellsVec[GetCellIndex(x, y)];
		cell = Cell::Dead;
		m_Board.AddQuad(x, y, GetCellColor(cell));
	});

	for (int i = 0; i < m_Config.uNumAnts; ++i)
	{
		m_pAntsVec.emplace_back(new Ant(xPositionDistribution(rng), yPositionDistribution(rng)));
	}
}

const sf::Color CellAutomation::GetCellColor(const Cell& c) const
{
	switch (c)
	{
	case Cell::Alive:
		return sf::Color::White;
		break;

	case Cell::Dead:
		return sf::Color::Black;
		break;
	}
}

const sf::Color CellAutomation::FlipCellColour(const Cell& c, const sf::Color& colour)
{
	switch (c)
	{
	case Cell::Alive:
		return sf::Color::Black;
		break;

	case Cell::Dead:
		return colour;
		break;
	}
}

Cell CellAutomation::GetCell(const unsigned& x, const unsigned& y) const
{
	unsigned index = (x * m_Config.uSimWidth) + y;
	return m_CellsVec[index];
}

void CellAutomation::Run()
{
	m_Window.setFramerateLimit(m_Config.uFrameRate);
	while (m_Window.isOpen())
	{
		m_Window.clear();
		sf::Event event;
		while (m_Window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				m_Window.close();
		}

		for(unsigned i = 0; i<m_Config.uSimSpeed; ++i)
			UpdateAnt();

		m_Window.draw(m_Board.v_PixelsVec.data(), m_Board.v_PixelsVec.size(), sf::Quads);
		m_Window.display();
	}
}

unsigned CellAutomation::GetCellIndex(const unsigned& x, const unsigned& y) const
{
	return (y * m_Config.uSimWidth + x);
}

void CellAutomation::UpdateAnt()
{
	for (Ant* Ant : m_pAntsVec)
	{
		Cell& cell = m_CellsVec[GetCellIndex(Ant->m_XPos, Ant->m_YPos)];
		switch (cell)
		{
		case Cell::Alive:
			Ant->Turn(Direction::Right);
			break;

		case Cell::Dead:
			Ant->Turn(Direction::Left);
			break;
		}

		int newX = Ant->m_XPos + Ant->m_AntFacing.m_X;
		int newY = Ant->m_YPos + Ant->m_AntFacing.m_Y;

		//World wrapping on the X axis
		if (newX == m_Config.uSimWidth)
		{
			newX = 0;
		}
		else if (newX == -1)
		{
			newX = m_Config.uSimWidth - 1;
		}

		//World wrapping on the Y axis
		if (newY == m_Config.uSimHeight)
		{
			newY = 0;
		}
		else if (newY == -1)
		{
			newY = m_Config.uSimHeight - 1;
		}
		
		cell == Cell::Alive ? cell = Cell::Dead : cell = Cell::Alive;

		m_Board.ChangeQuadColour(Ant->m_XPos, Ant->m_YPos, FlipCellColour(cell, Ant->m_AntColor));

		Ant->m_XPos = newX;
		Ant->m_YPos = newY;
	}
}

CellAutomation::~CellAutomation()
{
	for (unsigned i = m_pAntsVec.size() - 1; i > -1; --i)
	{
		delete m_pAntsVec[i];
		m_pAntsVec[i] = nullptr;
	}
}