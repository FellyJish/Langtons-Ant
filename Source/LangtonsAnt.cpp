#include "Config.h"
#include "CellAutomation.h"
#include <iostream>
#include <cctype>

unsigned const uSCREEN_WIDTH = 800, uSCREEN_HEIGHT = 600, uQUAD_SIZE = 4, uFRAME_RATE = 60, uNUM_AntS = 1, uSIMULATION_SPEED = 20, uSPEED_BLOAT_VALUE = 20;

int main()
{
	Config config;
	char chOption;

	std::cout << "Would you like to use default config? Y/N: ";
	std::cin >> chOption;

	chOption = std::toupper(chOption);

	if (chOption == 'Y')
	{
		config.uScreenWidth = uSCREEN_WIDTH;
		config.uScreenHeight = uSCREEN_HEIGHT;
		config.uQuadSize = uQUAD_SIZE;
		config.uFrameRate = uFRAME_RATE;

		config.uSimWidth = config.uScreenWidth / config.uQuadSize;
		config.uSimHeight = config.uScreenHeight / config.uQuadSize;

		config.uNumAnts = uNUM_AntS;

		config.uSimSpeed = uSIMULATION_SPEED;

		printf("Window width: %d\nWindow height: %d\nFramerate: %d\nCell: size %d\nSimulation Speed: %d\nNumber of ants: %d\n", config.uScreenWidth, config.uScreenHeight, config.uFrameRate, uQUAD_SIZE, config.uSimSpeed/uSPEED_BLOAT_VALUE, config.uNumAnts);
	}
	else if (chOption == 'N')
	{
		std::cout << "\nPlease enter your desired values" << std::endl;
		std::cout << "(negative values will be made positive)" << std::endl;
		std::cout << "---------------------------------------\n\n" << std::endl;

		std::cout << "Enter window width: ";
		std::cin >> config.uScreenWidth;

		std::cout << "Enter window height: ";
		std::cin >> config.uScreenHeight;

		std::cout << "Enter how many Ants you want: ";
		std::cin >> config.uNumAnts;

		std::cout << "Enter cell size (smaller numbers like 4-16 work better): ";
		std::cin >> config.uQuadSize;

		std::cout << "Enter max frame rate: ";
		std::cin >> config.uFrameRate;

		std::cout << "Enter the simulation speed (about 1-5 works well) ";
		std::cin >> config.uSimSpeed;

		config.uScreenWidth = std::abs(config.uScreenWidth);
		config.uScreenHeight = std::abs(config.uScreenHeight);
		config.uNumAnts = std::abs(config.uNumAnts);
		config.uQuadSize = std::abs(config.uQuadSize);
		config.uFrameRate = std::abs(config.uFrameRate);
		config.uSimSpeed = std::abs(config.uSimSpeed);

		config.uSimSpeed *= uSPEED_BLOAT_VALUE;

		//Make it so that the cells fit in the window
		config.uScreenWidth -= config.uScreenWidth % config.uQuadSize;
		config.uScreenHeight -= config.uScreenHeight % config.uQuadSize;

		config.uSimWidth = config.uScreenWidth / config.uQuadSize;
		config.uSimHeight = config.uScreenHeight / config.uQuadSize;

		printf("Window width: %d\nWindow height: %d\nFramerate: %d\nCell: size %d\nSimulation Speed: %d\nNumber of ants: %d\n", config.uScreenWidth, config.uScreenHeight, config.uFrameRate, uQUAD_SIZE, config.uSimSpeed / uSPEED_BLOAT_VALUE, config.uNumAnts);
	}
	else
	{
		printf("Invalid input, using default config.\n");

		config.uScreenWidth = uSCREEN_WIDTH;
		config.uScreenHeight = uSCREEN_HEIGHT;
		config.uQuadSize = uQUAD_SIZE;
		config.uFrameRate = uFRAME_RATE;

		config.uSimWidth = config.uScreenWidth / config.uQuadSize;
		config.uSimHeight = config.uScreenHeight / config.uQuadSize;

		config.uNumAnts = uNUM_AntS;
		config.uSimSpeed = uSIMULATION_SPEED;

		printf("Window width: %d\nWindow height: %d\nFramerate: %d\nCell: size %d\nSimulation Speed: %d\nNumber of ants: %d\n", config.uScreenWidth, config.uScreenHeight, config.uFrameRate, uQUAD_SIZE, config.uSimSpeed / uSPEED_BLOAT_VALUE, config.uNumAnts);
	}

	CellAutomation app(config);
	app.Run();
	return 0;
}
