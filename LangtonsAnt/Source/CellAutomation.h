#pragma once
#include "Config.h"
#include "board.h"
#include <chrono>
#include "Ant.h"

enum class Cell : uint8_t
{
	Dead,
	Alive
};

struct Timer
{
	const char* m_szOperation;
	std::chrono::time_point<std::chrono::steady_clock> m_tstart, m_tend;
	std::chrono::duration<float> duration;

	Timer(const char* job) : m_szOperation(job)
	{
		m_tstart = std::chrono::high_resolution_clock::now();
	}

	~Timer()
	{
		m_tend = std::chrono::high_resolution_clock::now();
		duration = m_tend - m_tstart;

		float ms = duration.count() * 1000.0f;
		printf("Timer took %dms to perform %c\n", ms, m_szOperation);
	}
	
};

class CellAutomation
{
public:
	CellAutomation(const Config& c);
	~CellAutomation();
	void Run();

private:
	const Config m_Config;
	unsigned m_uGenerations;
	std::vector<Cell> m_CellsVec;
	std::vector<Ant*> m_pAntsVec;
	sf::RenderWindow m_Window;
	Board m_Board;

	const sf::Color GetCellColor(const Cell& c) const;
	Cell CellAutomation::GetCell(const unsigned& x, const unsigned& y) const;
	unsigned GetCellIndex(const unsigned& x,const unsigned& y) const;
	void UpdateAnt();
	const sf::Color CellAutomation::FlipCellColour(const Cell& c, const sf::Color& colour);

	template<typename F>
	void CellForEach(F f);
	
	std::vector<Ant> m_AntsVec;
};

//Template to pass lambdas to for shorthand looping through the grid
template<typename F>
void CellAutomation::CellForEach(F f)
{
	for (unsigned y = 0; y < m_Config.uSimHeight; y++)
	{
		for (unsigned x = 0; x < m_Config.uSimWidth; x++)
		{
			f(x, y);
		}
	}
}
