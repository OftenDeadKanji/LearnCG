#include "controller.h"
#include "../../EventSystem/Keyboard/keyboard.h"

namespace RedWood::MVC
{
	Controller::Controller()
		: view(*this)
	{
	}

	void Controller::processInput()
	{
		view.checkInput(this->deltaTime);
	}

	void Controller::update()
	{
		model.Update();
	}

	void Controller::render()
	{
		view.render(this->deltaTime);
	}

	void Controller::updateDeltaTime()
	{
		const auto now = std::chrono::high_resolution_clock::now();
		this->deltaTime =  std::chrono::duration_cast<std::chrono::nanoseconds>(now - this->frameStart).count() * 0.000000001;

		this->frameStart = now;
	}

	bool Controller::shouldApplicationRun() const
	{
		return this->mainLoopCondition;
	}

	void Controller::windowCloseCallback()
	{
		this->mainLoopCondition = false;
	}

	void Controller::keyboardKeyPressCallback()
	{
		if(EventSystem::Keyboard::keys[static_cast<size_t>(EventSystem::KeyboardKey::KeyEscape)])
		{
			this->mainLoopCondition = false;
		}
	}
}
