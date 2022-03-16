#include "pch.h"
#include "Application/General/application.h"

#ifndef _DEBUG
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

int main()
{
#ifdef _DEBUG
	std::cout << "Starting" << std::endl;
#endif

	glfwInit();

	RW::Application app;
	app.run();

	glfwTerminate();
}