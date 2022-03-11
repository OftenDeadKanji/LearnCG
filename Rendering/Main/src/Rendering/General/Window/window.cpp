#include "pch.h"
#include "window.h"

namespace RedWood
{
	Window::Window(WindowProperties properties) 
		: properties(std::move(properties))
	{}

	Window::Window(Window&& other) noexcept
		: properties(std::move(other.properties))
	{
	}

	Window& Window::operator=(Window&& other) noexcept
	{
		if(this != &other)
		{
			this->properties = other.properties;
		}

		return *this;
	}

	void Window::setSize(const Size& size)
	{
		this->properties.Size = size;

		this->resize();
	}
	Size Window::getSize()
	{
		return this->properties.Size;
	}

	void Window::setTitle(const std::string& title)
	{
		this->properties.Title = title;
		
		this->rename();
	}
	const std::string& Window::getTitle()
	{
		return this->properties.Title;
	}

	void Window::setIcon(const std::string& iconFilePath)
	{
		this->properties.IconFilePath = iconFilePath;

		this->changeIcon();
	}

	void Window::attachEventManager(EventSystem::EventManager& manager)
	{
		this->eventManager = &manager;
	}

	void Window::windowCloseCallback(bool shouldWindowClose) const
	{
		this->eventManager->windowCloseCallback(shouldWindowClose);
	}

	void Window::windowResizeCallback(vec2 size) const
	{
		this->eventManager->windowResizeCallback(size);
	}

	void Window::keyboardKeyCallback(EventSystem::KeyboardKey key, EventSystem::KeyboardKeyAction action) const
	{
		this->eventManager->keyboardKeyCallback(key, action);
	}

	void Window::mouseButtonCallback(EventSystem::MouseButton button, EventSystem::MouseButtonAction action) const
	{
		this->eventManager->mouseButtonCallback(button, action);
	}

	void Window::cursorPositionCallback(vec2 position) const
	{
		this->eventManager->cursorPositionCallback(position);
	}
}
