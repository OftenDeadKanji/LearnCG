#pragma once

namespace RedWood::EventSystem
{
	struct Keyboard
	{
		static std::array<bool, static_cast<size_t>(KeyboardKey::Count)> keys;
	};

}