#include "pch.h"
#include "window.h"

#pragma region GLFW callback functions
void framebuffer_size_callback(GLFWwindow* window, const int width, const int height)
{
	glViewport(0, 0, width, height);
	auto* userWindow = reinterpret_cast<RW::Window*>(glfwGetWindowUserPointer(window));
	if(userWindow)
	{
		userWindow->windowResizeCallback({ width, height });
	}
}

void window_close_callback(GLFWwindow* window)
{
	auto* userWindow = reinterpret_cast<RW::Window*>(glfwGetWindowUserPointer(window));
	if(userWindow)
	{
		userWindow->windowCloseCallback(glfwWindowShouldClose(window));
	}
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	auto* userWindow = reinterpret_cast<RW::Window*>(glfwGetWindowUserPointer(window));
	if(userWindow)
	{
		userWindow->keyboardKeyCallback(RW::EventSystem::convertToKeyboardKey(key), RW::EventSystem::convertToKeyboardKeyAction(action));
	}
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	auto* userWindow = reinterpret_cast<RW::Window*>(glfwGetWindowUserPointer(window));
	if(userWindow)
	{
		userWindow->mouseButtonCallback(RW::EventSystem::convertToMouseButton(button), RW::EventSystem::convertToMouseButtonAction(action));
	}
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	auto* userWindow = reinterpret_cast<RW::Window*>(glfwGetWindowUserPointer(window));
	if(userWindow)
	{
		userWindow->cursorPositionCallback({ xpos, ypos });
	}
}
#pragma endregion


namespace RedWood
{
	Window::Window(WindowProperties properties) 
		: properties(std::move(properties))
	{
		this->createGLFWWindow();
		this->initializeOpenGL();

		glfwSetInputMode(this->glfwWindow, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		glfwSetCursorPos(this->glfwWindow, this->properties.Size.x / 2.0, this->properties.Size.y / 2.0);
	}

	Window::Window(Window&& other) noexcept
		: properties(std::move(other.properties)), glfwWindow(other.glfwWindow)
	{
		other.glfwWindow = nullptr;
	}

	Window::~Window()
	{
		if(this->glfwWindow)
		{
			glfwDestroyWindow(this->glfwWindow);
		}
	}

	Window& Window::operator=(Window&& other) noexcept
	{
		if(this != &other)
		{
			this->properties = other.properties;
			this->glfwWindow = other.glfwWindow;
			other.glfwWindow = nullptr;
		}

		return *this;
	}

	void Window::setSize(const size& size)
	{
		this->properties.Size = size;
		glfwSetWindowSize(this->glfwWindow, this->properties.Size.x, this->properties.Size.y);
	}
	size Window::getSize()
	{
		return this->properties.Size;
	}

	void Window::setTitle(const std::string& title)
	{
		this->properties.Title = title;
		glfwSetWindowTitle(this->glfwWindow, this->properties.Title.c_str());
	}
	const std::string& Window::getTitle()
	{
		return this->properties.Title;
	}

	void Window::setIcon(const std::string& iconFilePath)
	{
		this->properties.IconFilePath = iconFilePath;
		//??
	}

	constexpr float colorNormalizeFactor()
	{
		return 1.0f / 255.0f;
	}

	void Window::fillWithColorRGB(const vec3& color)
	{
		constexpr float normalizeFactor = colorNormalizeFactor();
		glClearColor(color.r * normalizeFactor, color.g * normalizeFactor, color.b * normalizeFactor, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Window::fillWithColorRGBf(const vec3& color)
	{
		glClearColor(color.r, color.g, color.b, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Window::swapBuffers()
	{
		glfwSwapBuffers(this->glfwWindow);
	}

	void Window::attachEventManager(EventSystem::EventManager& manager)
	{
		this->eventManager = &manager;

		glfwSetWindowCloseCallback(glfwWindow, window_close_callback);
		glfwSetFramebufferSizeCallback(glfwWindow, framebuffer_size_callback);
		glfwSetKeyCallback(glfwWindow, key_callback);
		glfwSetMouseButtonCallback(glfwWindow, mouse_button_callback);
		glfwSetCursorPosCallback(glfwWindow, cursor_position_callback);

		glfwSetWindowUserPointer(this->glfwWindow, this);
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

	void Window::resetCursorPos()
	{
		glfwSetCursorPos(this->glfwWindow, this->properties.Size.x / 2.0, this->properties.Size.y / 2.0);
	}

	void Window::createGLFWWindow()
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		switch(this->properties.Mode)
		{
			case WindowMode::Windowed:
				this->createWindowed();
				this->centerWindow();
				break;
			case WindowMode::Fullscreen:
				this->createFullscreen();
				break;
			case WindowMode::WindowedFullscreen:
				this->createWindowedFullscreen();
				break;
		}

		glfwSetWindowAttrib(this->glfwWindow, GLFW_RESIZABLE, GLFW_FALSE);
		glfwMakeContextCurrent(this->glfwWindow);
	}

	void Window::createWindowed()
	{
		this->glfwWindow = glfwCreateWindow(
			this->properties.Size.x,
			this->properties.Size.y,
			this->properties.Title.c_str(),
			nullptr,
			nullptr
		);
	}

	void Window::createFullscreen()
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

	void Window::createWindowedFullscreen()
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

	void Window::centerWindow() const
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

	void Window::initializeOpenGL()
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
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glFrontFace(GL_CCW);
	}
}
