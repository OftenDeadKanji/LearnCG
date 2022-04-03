#include "pch.h"
#include "view.h"
#include "controller.h"

namespace RedWood::MVC
{
	View::View(MVC::Controller& controller)
		: controller(controller),
		window(WindowProperties({ 1600, 900 }, WindowMode::Windowed, "LearnOpenGL", "")),
		camera({ 0.0f, 0.0f, -5.0f }, { 0.0f, 0.0f, 0.0f }),
		dirLight({ 1.0f, 1.0f, 1.0f }, { -1.0f, -1.0f, -1.0f }),
		pointLight({1.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {10.0f}),
		backpack("Resources/Models/backpack/backpack.obj")
	{
		this->window.attachEventManager(this->eventManager);

		this->mousePrevPos = window.getSize() * 0.5f;

		auto meshVert = SubShader::createShaderFromFile("Shaders/model_main.vert", SubShader::Type::Vertex);
		auto meshFrag = SubShader::createShaderFromFile("Shaders/model_main.frag", SubShader::Type::Fragment);

		this->meshShader.attachSubShader(meshVert);
		this->meshShader.attachSubShader(meshFrag);

		if (!this->meshShader.tryToLinkShader())
		{
			std::cout << "Linking mesh shader failed.\n";
		}
	}

	void View::checkInput(const float deltaTime)
	{
#if 1
		eventManager.checkForEvents();
		while(!eventManager.isEventQueueEmpty())
		{
			const auto eventType = this->eventManager.getEventTypeFromQueue();
			switch(eventType)
			{
				case EventSystem::EventType::WindowResized:
					break;
				case EventSystem::EventType::WindowClosed:
					this->controller.windowCloseCallback();
					break;
				case EventSystem::EventType::KeyboardKeyPressed:
					this->controller.keyboardKeyPressCallback();
					break;
				case EventSystem::EventType::KeyboardKeyReleased:
					break;
				case EventSystem::EventType::MouseButtonPressed:
					if(EventSystem::Mouse::buttons[static_cast<int>(EventSystem::MouseButton::Right)])
					this->mousePrevPos = EventSystem::Mouse::position;
					break;
				case EventSystem::EventType::MouseButtonReleased:
					break;
				case EventSystem::EventType::MouseCursorMoved:
					break;
			}
		}

		if(EventSystem::Keyboard::keys[static_cast<size_t>(EventSystem::KeyboardKey::KeyA)])
		{
			camera.moveToLocalRight(-7 * deltaTime);
		}
		if(EventSystem::Keyboard::keys[static_cast<size_t>(EventSystem::KeyboardKey::KeyD)])
		{
			camera.moveToLocalRight(7 * deltaTime);
		}
		if(EventSystem::Keyboard::keys[static_cast<size_t>(EventSystem::KeyboardKey::KeyS)])
		{
			camera.moveToLocalFront(-7 * deltaTime);
		}
		if(EventSystem::Keyboard::keys[static_cast<size_t>(EventSystem::KeyboardKey::KeyW)])
		{
			camera.moveToLocalFront(7 * deltaTime);
		}
		if (EventSystem::Keyboard::keys[static_cast<size_t>(EventSystem::KeyboardKey::KeyQ)])
		{
			camera.moveToLocalUp(-7 * deltaTime);
		}
		if (EventSystem::Keyboard::keys[static_cast<size_t>(EventSystem::KeyboardKey::KeyE)])
		{
			camera.moveToLocalUp(7 * deltaTime);
		}

		//const float yaw = EventSystem::Mouse::position.x - this->window.getSize().x / 2.0f;
		//const float pitch = EventSystem::Mouse::position.y - this->window.getSize().y / 2.0f;
		if (EventSystem::Mouse::buttons[static_cast<int>(EventSystem::MouseButton::Right)])
		{
			const float yaw = EventSystem::Mouse::position.x - this->mousePrevPos.x;
			const float pitch = EventSystem::Mouse::position.y - this->mousePrevPos.y;

			const vec3 cameraRotation(pitch, yaw, 0.0f);
			this->camera.rotateCamera(cameraRotation * this->mouseSpeed * deltaTime);

			this->mousePrevPos = EventSystem::Mouse::position;
		}
		//this->mousePrevPos = EventSystem::Mouse::position;
		//this->window.resetCursorPos();
#endif
	}

	void View::render(float deltaTime)
	{
		window.fillWithColorRGB({ 0, 0, 0 });

		checkImGUI();

		ImGui::ShowDemoWindow((bool*)true);

		meshShader.use();

		meshShader.setMat4("view", camera.getViewMatrix());
		meshShader.setMat4("proj", camera.getProjectionMatrix());
		meshShader.setMat4("model", glm::mat4(1.0f));

		meshShader.setInt("directionalLightCount", 1);
		dirLight.setLightInShader(meshShader, "directionalLights[0].");

		meshShader.setInt("pointLightCount", 1);
		pointLight.setLightInShader(meshShader, "pointLights[0].");

		backpack.render(meshShader);

		window.swapBuffers();
	}

	void View::checkImGUI()
	{
		
	}
}
