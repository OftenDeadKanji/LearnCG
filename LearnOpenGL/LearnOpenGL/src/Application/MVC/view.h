#ifndef VIEW_H
#define VIEW_H
#include "../../Rendering/Window/window.h"
#include "../../Rendering/Vertex/vertex.h"
#include "../../Rendering/Shader/shader.h"
#include "../../Rendering/Camera/camera.h"

#include "../../Mesh/mesh.h"

namespace RedWood::MVC
{
	class Controller;

	class View
	{
	public:
		explicit View(MVC::Controller& controller);

		void checkInput(float deltaTime);
		void render(float deltaTime);

	private:
		Controller& controller;

		Window window;
		EventSystem::EventManager eventManager;

		Camera camera;

		Shader mainShader;

		std::array<Vertex, 3> triangle = std::array<Vertex, 3>();
		GLuint triangleVAO, triangleVBO;

		vec2 mousePrevPos {};

		Shader meshShader;
		Mesh backpack;
	};
}
#endif