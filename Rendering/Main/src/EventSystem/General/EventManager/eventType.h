#pragma once

namespace RedWood::EventSystem
{
	enum class EventType
	{
		None,

		WindowResized,
		WindowClosed,

		KeyboardKeyPressed,
		KeyboardKeyReleased,

		MouseButtonPressed,
		MouseButtonReleased,

		MouseCursorMoved
	};
}
