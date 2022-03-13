#include "pch.h"
#include "eventManagerGLFW.h"

void RedWood::EventSystem::EventManagerGLFW::checkForEvents()
{
	glfwPollEvents();
}
