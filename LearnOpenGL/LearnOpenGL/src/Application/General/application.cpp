#include "pch.h"
#include "application.h"

namespace RedWood
{

	void Application::run()
	{
		while(controller.shouldApplicationRun())
		{
			controller.processInput();
			controller.update();
			controller.render();

			controller.updateDeltaTime();
		}
	}
}
