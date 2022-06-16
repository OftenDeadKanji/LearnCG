#include <iostream>
#include "Application/General/application.h"

#ifndef _DEBUG
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#include <fstream>

int main()
{
#ifdef _DEBUG
	std::cout << "Starting" << std::endl;
#endif
	std::ofstream file("WhereAmI.txt");
	glfwInit();

	RW::Application app;
	app.run();

	glfwTerminate();
}