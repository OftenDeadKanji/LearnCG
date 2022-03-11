#include "pch.h"
#include "view.h"

namespace RedWood::MVC
{
	View::View(MVC::Controller& controller)
		: controller(controller)
	{
		APIFactory::createWindow(this->window);
		APIFactory::createEventManager(this->eventManager);

		this->window->attachEventManager(*this->eventManager.get());
	}

	void View::checkInput()
	{
		eventManager->checkForEvents();
		while(!eventManager->isEventQueueEmpty())
		{
			auto eventType = this->eventManager->getEventTypeFromQueue();
			switch (eventType)
			{
			case EventSystem::EventType::WindowResized:
				break;
			case EventSystem::EventType::WindowClosed:
				this->controller.windowCloseCallback();
				break;
			case EventSystem::EventType::KeyboardKeyPressed:
				break;
			case EventSystem::EventType::KeyboardKeyReleased:
				break;
			case EventSystem::EventType::MouseButtonPressed:
				break;
			case EventSystem::EventType::MouseButtonReleased:
				break;
			case EventSystem::EventType::MouseCursorMoved:
				break;
			}
		}
	}

	void View::render()
	{
		window->fillWithColorRGBf({ 0.1f, 0.6f, 0.2f });

		window->swapBuffers();
	}
}
