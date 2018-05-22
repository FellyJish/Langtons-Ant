#include "Config.h"
#include "CellAutomation.h"
#include <iostream>
#include <cctype>

unsigned const uSCREEN_WIDTH = 800, uSCREEN_HEIGHT = 600, uQUAD_SIZE = 4, uFRAME_RATE = 60, uNUM_ANTS = 1, uSIMULATION_SPEED = 15, uSPEED_BLOAT_VALUE = 5;

int main()
{
	Config config;
	char chOption;

	printf("The default config is:\n\nScreen Width: %d\nScreen Height: %d\nCell Size: %d\nFrame Rate: %d\nNumber of Ants: %d\nSimulation Speed: %d\n", uSCREEN_WIDTH, uSCREEN_HEIGHT, uQUAD_SIZE, uFRAME_RATE, uNUM_ANTS, uSIMULATION_SPEED/uSPEED_BLOAT_VALUE);
	std::cout << "-------------------\n\n";

	std::cout << "Would you like to use default setup? Y/N: ";
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

		config.uNumAnts = uNUM_ANTS;

		config.uSimSpeed = uSIMULATION_SPEED;
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

		std::cout << "Enter cell size: ";
		std::cin >> config.uQuadSize;

		std::cout << "Enter max frame rate: ";
		std::cin >> config.uFrameRate;

		std::cout << "Enter the simulation speed: ";
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

		config.uNumAnts = uNUM_ANTS;
		config.uSimSpeed = uSIMULATION_SPEED;
	}

	CellAutomation app(config);
	app.Run();
	return 0;
}
