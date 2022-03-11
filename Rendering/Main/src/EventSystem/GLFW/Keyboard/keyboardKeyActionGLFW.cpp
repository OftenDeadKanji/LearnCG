#include "pch.h"
#include "keyboardKeyActionGLFW.h"

namespace RedWood::EventSystem
{
	KeyboardKeyAction convertToKeyboardKeyActionGLFW(int glfw_action)
	{
		switch(glfw_action)
		{
			default:
				return KeyboardKeyAction::None;
			case GLFW_PRESS:
				return KeyboardKeyAction::Pressed;
			case GLFW_RELEASE:
				return KeyboardKeyAction::Released;
		}
	}

}