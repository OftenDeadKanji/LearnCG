#include "pch.h"
#include "APIFactory.h"

namespace RedWood
{
	void APIFactory::createApplication(std::unique_ptr<Application>& application)
	{
		const Settings* settings = Settings::getInstance();
		const RendererType type = settings->CurrentRendererType;

		switch(type)
		{
			case RendererType::eOpenGL:
				application = std::make_unique<ApplicationGLFW>();
				return;
		}
	}

	void APIFactory::createWindow(std::unique_ptr<Window>& window)
	{
		const Settings* settings = Settings::getInstance();
		const RendererType type = settings->CurrentRendererType;

		const vec2 screenSize = settings->ScreenSize;
		const WindowMode mode = settings->CurrentWindowMode;

		WindowProperties windowProperties(screenSize, mode, "LearnCG!", "");

		switch (type)
		{
		case RendererType::eOpenGL:
			window = std::make_unique<WindowOpenGL>(windowProperties);
			return;
		}
	}

	void APIFactory::createEventManager(std::unique_ptr<EventSystem::EventManager>& manager)
	{
		const Settings* settings = Settings::getInstance();
		const RendererType type = settings->CurrentRendererType;

		switch (type)
		{
		case RendererType::eOpenGL:
			manager = std::make_unique<EventSystem::EventManagerGLFW>();
			return;
		}
	}
}
