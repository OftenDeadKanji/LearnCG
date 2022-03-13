#pragma once
#include "../../General/EventManager/eventManager.h"

namespace RedWood::EventSystem
{
	class EventManagerGLFW
		: public EventManager
	{
	public:
		void checkForEvents() override;
	};
}

