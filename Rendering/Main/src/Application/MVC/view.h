#ifndef VIEW_H
#define VIEW_H
#include "../../Rendering/General/Window/window.h"

namespace RedWood::MVC
{
	class Controller;

	class View
	{
	public:
		View(MVC::Controller& controller);

		void checkInput();
		void render();

	private:
		Controller& controller;

		std::unique_ptr<Window> window;
		std::unique_ptr<EventSystem::EventManager> eventManager;

	};
}
#endif