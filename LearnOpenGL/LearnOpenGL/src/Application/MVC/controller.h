#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "model.h"
#include "view.h"

namespace RedWood::MVC
{
	class Controller
	{
	public:
		Controller();

		void processInput();
		void update();
		void render();

		void updateDeltaTime();

		[[nodiscard]] bool shouldApplicationRun() const;

		void windowCloseCallback();
		void keyboardKeyPressCallback();
	private:
		MVC::Model model;
		MVC::View view;

		bool mainLoopCondition = true;

		std::chrono::high_resolution_clock::time_point frameStart;
		float deltaTime{};
	};
}

#endif