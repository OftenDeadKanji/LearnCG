#include "pch.h"
#include "mouseButtonGLFW.h"

namespace RedWood::EventSystem
{
	MouseButton convertToMouseButtonGLFW(int button)
	{
		switch(button)
		{
			default:
				return MouseButton::None;
			case GLFW_MOUSE_BUTTON_LEFT:
				return MouseButton::Left;
			case GLFW_MOUSE_BUTTON_MIDDLE:
				return MouseButton::Middle;
			case GLFW_MOUSE_BUTTON_RIGHT:
				return MouseButton::Right;
		}
	}
}
