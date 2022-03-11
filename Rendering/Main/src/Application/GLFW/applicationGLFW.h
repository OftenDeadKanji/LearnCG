#pragma once
#include "../General/application.h"

namespace RedWood
{
	class ApplicationGLFW
		: public Application
	{
	public:
		ApplicationGLFW();
		~ApplicationGLFW();

		void run() override;
	};
}