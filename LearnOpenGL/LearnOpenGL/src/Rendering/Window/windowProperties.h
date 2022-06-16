#ifndef WINDOW_PROPERTIES_H
#define WINDOW_PROPERTIES_H
#include "windowMode.h"
#include "../../Utilities/types.h"
#include <string>

namespace RedWood
{
	struct WindowProperties
	{
		WindowProperties(const size& size, WindowMode mode, std::string title, std::string iconFilePath);
		WindowProperties(const WindowProperties&) = default;
		WindowProperties(WindowProperties&&) noexcept;
		~WindowProperties() = default;

		WindowProperties& operator=(const WindowProperties&);
		WindowProperties& operator=(WindowProperties&&) noexcept;

		size getSize() const;
		void setSize(const size& size);

		__declspec(property(get = getSize, put = setSize)) size Size;

		WindowMode getWindowMode() const;
		void setWindowMode(WindowMode mode);

		__declspec(property(get = getWindowMode, put = setWindowMode)) WindowMode Mode;

		const std::string& getTitle() const;
		void setTitle(std::string title);

		__declspec(property(get = getTitle, put = setTitle)) std::string Title;

		const std::string& getIconFilePath() const;
		void setIconFilePath(std::string iconFilePath);

		__declspec(property(get = getIconFilePath, put = setIconFilePath)) std::string IconFilePath;

	private:
		size size {};
		WindowMode mode = WindowMode::Windowed;
		std::string title;
		std::string iconFilePath;
	};
}
#endif