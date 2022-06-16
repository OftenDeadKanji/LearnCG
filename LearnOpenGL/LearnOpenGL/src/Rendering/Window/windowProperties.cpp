#include "windowProperties.h"

namespace RedWood
{
	WindowProperties::WindowProperties(const RedWood::size& size, WindowMode mode, std::string title,
		std::string iconFilePath)
			: size(size), mode(mode), title(std::move(title)), iconFilePath(std::move(iconFilePath))
	{
	}

	WindowProperties::WindowProperties(WindowProperties&& other) noexcept
		: size(other.size), mode(other.mode), title(std::move(other.title)), iconFilePath(std::move(other.iconFilePath))
	{
	}


	WindowProperties& WindowProperties::operator=(const WindowProperties& other)
	{
		if(this != &other)
		{
			this->size = other.size;
			this->mode = other.mode;
			this->title = other.title;
			this->iconFilePath = other.iconFilePath;
		}

		return *this;
	}

	WindowProperties& WindowProperties::operator=(WindowProperties&& other) noexcept
	{
		if(this != &other)
		{
			this->size = other.size;
			this->mode = other.mode;
			this->title = std::move(other.title);
			this->iconFilePath = std::move(other.iconFilePath);
		}

		return *this;
	}

	size WindowProperties::getSize() const
	{
		return this->size;
	}

	void WindowProperties::setSize(const RedWood::size& size)
	{
		this->size = size;
	}

	WindowMode WindowProperties::getWindowMode() const
	{
		return this->mode;
	}

	void WindowProperties::setWindowMode(WindowMode mode)
	{
		this->mode = mode;
	}

	const std::string& WindowProperties::getTitle() const
	{
		return this->title;
	}

	void WindowProperties::setTitle(std::string title)
	{
		this->title = std::move(title);
	}

	const std::string& WindowProperties::getIconFilePath() const
	{
		return this->iconFilePath;
	}

	void WindowProperties::setIconFilePath(std::string iconFilePath)
	{
		this->iconFilePath = std::move(iconFilePath);
	}
}
