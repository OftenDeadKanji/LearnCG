#include "pch.h"
#include "controller.h"

namespace RedWood::MVC
{
	Controller::Controller()
		: view(*this)
	{
	}

	void Controller::processInput()
	{
		view.checkInput();
	}

	void Controller::update()
	{
		model.Update();
	}

	void Controller::render()
	{
		view.render();
	}

	bool Controller::shouldApplicationRun() const
	{
		return this->mainLoopCondition;
	}

	void Controller::windowCloseCallback()
	{
		this->mainLoopCondition = false;
	}
}
