#include "pch.h"
#include "mouseButtonActionGLFW.h"

namespace RedWood::EventSystem
{
	MouseButtonAction convertToMouseButtonActionGLFW(int glfw_action)
	{
		switch(glfw_action)
		{
			default:
				return MouseButtonAction::None;
			case GLFW_PRESS:
				return MouseButtonAction::Pressed;
			case GLFW_RELEASE:
				return MouseButtonAction::Released;
		}
	}

}