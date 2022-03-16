#ifndef WINDOW_H
#define WINDOW_H
#include "windowProperties.h"
#include "../../EventSystem/EventManager/eventManager.h"

namespace RedWood
{
	class Window
	{
	public:
		explicit Window(WindowProperties properties);
		Window(const Window&) = delete;
		Window(Window&&) noexcept;
		~Window();

		Window& operator=(const Window&) = delete;
		Window& operator=(Window&&) noexcept;

		void setSize(const size& size);
		size getSize();

		void setTitle(const std::string& title);
		const std::string& getTitle();

		void setIcon(const std::string& iconFilePath);

		void fillWithColorRGB(const vec3& color = { 0, 0, 0 });
		void fillWithColorRGBf(const vec3& color = { 0.0f, 0.0f, 0.0f });

		void swapBuffers();

		void attachEventManager(EventSystem::EventManager& manager);

		void windowCloseCallback(bool shouldWindowClose) const;
		void windowResizeCallback(vec2 size) const;
		void keyboardKeyCallback(EventSystem::KeyboardKey key, EventSystem::KeyboardKeyAction action) const;
		void mouseButtonCallback(EventSystem::MouseButton button, EventSystem::MouseButtonAction action) const;
		void cursorPositionCallback(vec2 position) const;

	private:
		void createGLFWWindow();

		void createWindowed();
		void createFullscreen();
		void createWindowedFullscreen();

		void centerWindow() const;

		void initializeOpenGL();

		WindowProperties properties;
		GLFWwindow* glfwWindow {};
		EventSystem::EventManager* eventManager {};
	}; 
}
#endif