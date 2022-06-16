#pragma once
#include <array>
#include "mouseButton.h"
#include "../../Utilities/types.h"

namespace RedWood::EventSystem
{
	struct Mouse
	{
		static std::array<bool, static_cast<size_t>(MouseButton::Count)> buttons;
		static vec2 position;
	};
}
