#ifndef WINDOW_OPENGL_H
#define WINDOW_OPENGL_H
#include "..\\..\\General\Window\window.h"

namespace RedWood
{
	class WindowOpenGL :
		public Window
	{
	public:
		explicit WindowOpenGL(const WindowProperties& properties);
		WindowOpenGL(const WindowOpenGL&) = delete;
		WindowOpenGL(WindowOpenGL&&) noexcept;
		~WindowOpenGL() override;

		WindowOpenGL& operator=(const WindowOpenGL&) = delete;
		WindowOpenGL& operator=(WindowOpenGL&&) noexcept;

		void fillWithColorRGB(const vec3& color) override;
		void fillWithColorRGBf(const vec3& color) override;

		void swapBuffers() override;

		void attachEventManager(EventSystem::EventManager& manager) override;
	private:
		void createGLFWWindow();

		void createWindowed();
		void createFullscreen();
		void createWindowedFullscreen();

		void centerWindow() const;

		void initializeOpenGL();
	protected:
		void resize() override;
		void resize(const Size& size) override;
		void rename() override;
		void rename(std::string) override;
		void changeIcon() override;
		void changeIcon(std::string iconFilePath) override;
	private:
		GLFWwindow* glfwWindow{};
	};
}
#endif