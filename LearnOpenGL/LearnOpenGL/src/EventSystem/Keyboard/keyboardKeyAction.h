#pragma once

namespace RedWood::EventSystem
{
	enum class KeyboardKeyAction
	{
		None,

		Pressed,
		Released
	};

	inline KeyboardKeyAction convertToKeyboardKeyAction(int glfw_action)
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