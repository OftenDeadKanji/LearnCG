#ifndef WINDOW_H
#define WINDOW_H
#include "windowProperties.h"
#include "../../../EventSystem/General/EventManager/eventManager.h"

namespace RedWood
{
	class Window
	{
	public:
		explicit Window(WindowProperties properties);
		Window(const Window&) = delete;
		Window(Window&&) noexcept;
		virtual ~Window() = default;

		Window& operator=(const Window&) = delete;
		Window& operator=(Window&&) noexcept;

		void setSize(const Size& size);
		Size getSize();

		void setTitle(const std::string& title);
		const std::string& getTitle();

		void setIcon(const std::string& iconFilePath);

		virtual void fillWithColorRGB(const vec3& color = { 0, 0, 0 }) = 0;
		virtual void fillWithColorRGBf(const vec3& color = {0.0, 0.0, 0.0}) = 0;

		virtual void swapBuffers() = 0;

		virtual void attachEventManager(EventSystem::EventManager& manager);

		void windowCloseCallback(bool shouldWindowClose) const;
		void windowResizeCallback(vec2 size) const;
		void keyboardKeyCallback(EventSystem::KeyboardKey key, EventSystem::KeyboardKeyAction action) const;
		void mouseButtonCallback(EventSystem::MouseButton button, EventSystem::MouseButtonAction action) const;
		void cursorPositionCallback(vec2 position) const;
	protected:
		virtual void resize() = 0;
		virtual void resize(const Size& size) = 0;

		virtual void rename() = 0;
		virtual void rename(std::string) = 0;

		virtual void changeIcon() = 0;
		virtual void changeIcon(std::string iconFilePath) = 0;

		WindowProperties properties;
		EventSystem::EventManager* eventManager;
	};
}
#endif