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

		[[nodiscard]] bool shouldApplicationRun() const;

		void windowCloseCallback();
		void keyboardKeyPressCallback();
	private:
		MVC::Model model;
		MVC::View view;

		bool mainLoopCondition = true;
	};
}

#endif