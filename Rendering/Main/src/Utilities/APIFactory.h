#ifndef APIFACTORY_H
#define APIFACTORY_H

#include "../Application/GLFW/applicationGLFW.h"
#include "../Rendering/OpenGL/Window/windowOpenGL.h"
#include "../EventSystem/GLFW/EventManager/eventManagerGLFW.h"

namespace RedWood
{
	class APIFactory
	{
	public:
		static void createApplication(std::unique_ptr<Application>& application);
		static void createWindow(std::unique_ptr<Window>& window);
		static void createEventManager(std::unique_ptr<EventSystem::EventManager>& manager);
	};

}
#endif // APIFACTORY_H
