#ifndef VIEW_H
#define VIEW_H
#include "../../Rendering/Window/window.h"
#include "../../Rendering/Vertex/vertex.h"
#include "../../Rendering/OpenGL Objects/vao.h"
#include "../../Rendering/OpenGL Objects/vbo.h"
#include "../../Rendering/Shader/shader.h"
#include "../../Rendering/Camera/camera.h"

namespace RedWood::MVC
{
	class Controller;

	class View
	{
	public:
		View(MVC::Controller& controller);

		void checkInput();
		void render();

	private:
		Controller& controller;

		Window window;
		EventSystem::EventManager eventManager;

		Camera camera;

		Shader mainShader;

		std::array<Vertex, 3> triangle = std::array<Vertex, 3>();
		VAO triangleVAO;
		VBO triangleVBO;

		vec2 mousePrevPos {};
	};
}
#endif