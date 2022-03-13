#ifndef APPLICATION_H
#define APPLICATION_H
#include "../MVC/controller.h"

namespace RedWood
{
	class Application
	{
	public:
		virtual void run();
	protected:
		MVC::Controller controller;
	};
}
#endif