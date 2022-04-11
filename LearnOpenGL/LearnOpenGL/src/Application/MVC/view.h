#ifndef VIEW_H
#define VIEW_H
#include "../../Rendering/Window/window.h"
#include "../../Rendering/Shader/shader.h"
#include "../../Rendering/Camera/camera.h"
#include "../../Rendering/Light/directionalLight.h"
#include "../../Rendering/Light/pointLight.h"

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

		void checkImGUI();
	private:
		void renderDepthMaps();
		void renderScene();

		Controller& controller;

		Window window;
		EventSystem::EventManager eventManager;

		Camera camera;

		DirectionalLight dirLight;
		vec3 dirLightDirection{};
		vec3 dirLightColor{};

		std::vector<PointLight> pointLights;

		vec2 mousePrevPos {};
		float mouseSpeed = 50.0f;

		Shader meshShader;
		Mesh backpack;
	};
}
#endif