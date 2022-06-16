#include "mouse.h"

std::array<bool, static_cast<size_t>(RedWood::EventSystem::MouseButton::Count)> RedWood::EventSystem::Mouse::buttons;
RedWood::vec2 RedWood::EventSystem::Mouse::position;
