#include "pch.h"
#include "windowOpenGL.h"

RW::EventSystem::MouseButton convert2ToMouseButtonGLFW(int button)
{
	switch(button)
	{
		default:
			return RW::EventSystem::MouseButton::None;
		case GLFW_MOUSE_BUTTON_LEFT:
			return RW::EventSystem::MouseButton::Left;
		case GLFW_MOUSE_BUTTON_MIDDLE:
			return RW::EventSystem::MouseButton::Middle;
		case GLFW_MOUSE_BUTTON_RIGHT:
			return RW::EventSystem::MouseButton::Right;
	}
}

#pragma region GLFW callback functions
void framebuffer_size_callback(GLFWwindow* window, const int width, const int height)
{
	glViewport(0, 0, width, height);
	if(const auto userWindow = static_cast<RedWood::Window*>(glfwGetWindowUserPointer(window)))
	{
		userWindow->windowResizeCallback({ width, height });
	}
}

void window_close_callback(GLFWwindow* window)
{
	if(const auto* userWindow = static_cast<RedWood::Window*>(glfwGetWindowUserPointer(window)))
	{
		userWindow->windowCloseCallback(glfwWindowShouldClose(window));
	}
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if(const auto* userWindow = static_cast<RedWood::Window*>(glfwGetWindowUserPointer(window)))
	{
		userWindow->keyboardKeyCallback(RW::EventSystem::convertToKeyboardKeyGLFW(key), RW::EventSystem::convertToKeyboardKeyActionGLFW(action));
	}
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if(const auto* userWindow = static_cast<RedWood::Window*>(glfwGetWindowUserPointer(window)))
	{
		userWindow->mouseButtonCallback(convert2ToMouseButtonGLFW(button), RW::EventSystem::convertToMouseButtonActionGLFW(action));
	}
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	if(const auto* userWindow = static_cast<RedWood::Window*>(glfwGetWindowUserPointer(window)))
	{
		userWindow->cursorPositionCallback({ xpos, ypos });
	}
}
#pragma endregion

namespace RedWood
{
	WindowOpenGL::WindowOpenGL(const WindowProperties& properties)
		: Window(properties)
	{
		glfwInit();

		this->createGLFWWindow();
		this->initializeOpenGL();
	}

	WindowOpenGL::WindowOpenGL(WindowOpenGL&& other) noexcept
		: Window(std::move(other)), glfwWindow(other.glfwWindow)
	{
		other.glfwWindow = nullptr;
	}

	WindowOpenGL::~WindowOpenGL()
	{
		if(this->glfwWindow)
		{
			glfwDestroyWindow(this->glfwWindow);
		}

		glfwTerminate();
	}

	WindowOpenGL& WindowOpenGL::operator=(WindowOpenGL&& other) noexcept
	{
		if(this != &other)
		{
			Window::operator=(std::move(other));

			this->glfwWindow = other.glfwWindow;
			other.glfwWindow = nullptr;
		}

		return *this;
	}

	constexpr float colorNormalizeFactor()
	{
		return 1.0f / 255.0f;
	}

	void WindowOpenGL::fillWithColorRGB(const vec3& color)
	{
		constexpr float normalizeFactor = colorNormalizeFactor();
		glClearColor(color.r * normalizeFactor, color.g * normalizeFactor, color.b * normalizeFactor, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void WindowOpenGL::fillWithColorRGBf(const vec3& color)
	{
		glClearColor(color.r, color.g, color.b, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void WindowOpenGL::swapBuffers()
	{
		glfwSwapBuffers(this->glfwWindow);
	}

	void WindowOpenGL::attachEventManager(EventSystem::EventManager& manager)
	{
		Window::attachEventManager(manager);

		glfwSetWindowCloseCallback(glfwWindow, window_close_callback);
		glfwSetFramebufferSizeCallback(glfwWindow, framebuffer_size_callback);
		glfwSetKeyCallback(glfwWindow, key_callback);
		glfwSetMouseButtonCallback(glfwWindow, mouse_button_callback);
		glfwSetCursorPosCallback(glfwWindow, cursor_position_callback);

		glfwSetWindowUserPointer(this->glfwWindow, this);
	}

	void WindowOpenGL::createGLFWWindow()
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		switch(this->properties.Mode)
		{
			case WindowMode::eWindowed:
				this->createWindowed();
				this->centerWindow();
				break;
			case WindowMode::eFullscreen:
				this->createFullscreen();
				break;
			case WindowMode::eWindowedFullscreen:
				this->createWindowedFullscreen();
				break;
		}

		glfwSetWindowAttrib(this->glfwWindow, GLFW_RESIZABLE, GLFW_FALSE);
		glfwMakeContextCurrent(this->glfwWindow);
	}

	void WindowOpenGL::createWindowed()
	{
		this->glfwWindow = glfwCreateWindow(
			this->properties.Size.x,
			this->properties.Size.y,
			this->properties.Title.c_str(),
			nullptr,
			nullptr
		);
	}

	void WindowOpenGL::createFullscreen()
	{
		const auto monitor = glfwGetPrimaryMonitor();

		this->glfwWindow = glfwCreateWindow(
			this->properties.Size.x,
			this->properties.Size.y,
			this->properties.Title.c_str(),
			monitor,
			nullptr
		);
	}

	void WindowOpenGL::createWindowedFullscreen()
	{
		const auto monitor = glfwGetPrimaryMonitor();
		const auto mode = glfwGetVideoMode(monitor);

		this->properties.Size = { mode->width, mode->height };

		this->glfwWindow = glfwCreateWindow(
			mode->width,
			mode->height,
			properties.Title.c_str(),
			monitor,
			nullptr
		);
	}

	void WindowOpenGL::centerWindow() const
	{
		if(const auto monitor = glfwGetPrimaryMonitor())
		{
			if(const auto mode = glfwGetVideoMode(monitor))
			{
				int windowWidth, windowHeight;
				glfwGetWindowSize(this->glfwWindow, &windowWidth, &windowHeight);

				glfwSetWindowPos(this->glfwWindow, (mode->width - windowWidth) / 2, (mode->height - windowHeight) / 2);
			}
		}
	}

	void WindowOpenGL::initializeOpenGL()
	{
		if(gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
		{
			glViewport(0, 0, this->getSize().x, this->getSize().y);
		}
		else
		{
			//TODO: exception
		}

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void WindowOpenGL::resize()
	{
		glfwSetWindowSize(this->glfwWindow, this->properties.Size.x, this->properties.Size.y);
	}

	void WindowOpenGL::resize(const Size& size)
	{
		this->properties.Size = size;
		glfwSetWindowSize(this->glfwWindow, this->properties.Size.x, this->properties.Size.y);
	}

	void WindowOpenGL::rename()
	{
		glfwSetWindowTitle(this->glfwWindow, this->properties.Title.c_str());
	}

	void WindowOpenGL::rename(std::string title)
	{
		this->properties.Title = std::move(title);
		glfwSetWindowTitle(this->glfwWindow, this->properties.Title.c_str());
	}

	void WindowOpenGL::changeIcon()
	{
		//GLFWimage icon;
		//glfwSetWindowIcon(this->glfwWindow, 1, )
	}

	void WindowOpenGL::changeIcon(std::string iconFilePath)
	{
		//glfwSetWindowIcon(this->glfwWindow, 1, )
	}
}