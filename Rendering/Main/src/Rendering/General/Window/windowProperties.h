#ifndef WINDOW_PROPERTIES_H
#define WINDOW_PROPERTIES_H
#include "windowMode.h"

namespace RedWood
{
	struct WindowProperties
	{
		WindowProperties(const Size& size, WindowMode mode, std::string title, std::string iconFilePath);
		WindowProperties(const WindowProperties&) = default;
		WindowProperties(WindowProperties&&) noexcept;
		~WindowProperties() = default;

		WindowProperties& operator=(const WindowProperties&);
		WindowProperties& operator=(WindowProperties&&) noexcept;

		[[nodiscard]] Size getSize() const;
		void setSize(const Size& size);

		__declspec(property(get = getSize, put = setSize)) Size Size;

		[[nodiscard]] WindowMode getWindowMode() const;
		void setWindowMode(WindowMode mode);

		__declspec(property(get = getWindowMode, put = setWindowMode)) WindowMode Mode;

		[[nodiscard]] const std::string& getTitle() const;
		void setTitle(std::string title);

		__declspec(property(get = getTitle, put = setTitle)) std::string Title;

		[[nodiscard]] const std::string& getIconFilePath() const;
		void setIconFilePath(std::string iconFilePath);

		__declspec(property(get = getIconFilePath, put = setIconFilePath)) std::string IconFilePath;

	private:
		RW::Size size {};
		WindowMode mode = WindowMode::eWindowed;
		std::string title;
		std::string iconFilePath;
	};
}
#endif