#include "pch.h"
#include "view.h"
#include "controller.h"
#include <format>

namespace RedWood::MVC
{
	View::View(MVC::Controller& controller)
		: controller(controller),
		window(WindowProperties({ 1600, 900 }, WindowMode::Windowed, "LearnOpenGL", "")),
		camera({ 0.0f, 0.0f, -5.0f }, { 0.0f, 0.0f, 0.0f }),
		dirLight({ 1.0f, 1.0f, 1.0f }, { 0.5f, -1.0f, -1.0f }),
		dirLightDirection({ 0.5f, -1.0f, -1.0f }),
		dirLightColor({ 1.0f, 1.0f, 1.0f }),
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
					{
						this->mousePrevPos = EventSystem::Mouse::position;
					}
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

		if (EventSystem::Mouse::buttons[static_cast<int>(EventSystem::MouseButton::Right)])
		{
			const float yaw = EventSystem::Mouse::position.x - this->mousePrevPos.x;
			const float pitch = EventSystem::Mouse::position.y - this->mousePrevPos.y;

			const vec3 cameraRotation(pitch, yaw, 0.0f);
			this->camera.rotateCamera(cameraRotation * this->mouseSpeed * deltaTime);

			this->mousePrevPos = EventSystem::Mouse::position;
		}
	}

	void View::render(float deltaTime)
	{
		renderDepthMaps();
		renderScene();
	}

	void View::checkImGUI()
	{
		ImGui::Begin("Scene manager", (bool*)false);

		ImGui::Text("Directional light");

		ImGui::Text("direction");
		ImGui::SameLine();
		ImGui::SliderFloat3("", &this->dirLightDirection[0], -1.0f, 1.0f, "%.3f");
		this->dirLight.setDirection(this->dirLightDirection);

		ImGui::Text("color");
		ImGui::SameLine();
		ImGui::ColorEdit3("", &this->dirLightColor[0], ImGuiColorEditFlags_Uint8);
		this->dirLight.setColor(this->dirLightColor);

		ImGui::Text("");
		ImGui::Text("PointLights");
		if(ImGui::Button("Add"))
		{
			this->pointLights.push_back(PointLight( { 1.0f, 1.0f, 1.0f }, {0.0f, 1.0f, 0.0f}, 10.0f));
		}
		for (auto i = 0; i < this->pointLights.size(); ++i)
		{
			std::string text1 = std::format("Point light #{}", i + 1);
			ImGui::Text(text1.c_str());
			ImGui::SameLine();
			if(ImGui::Button(std::string("Remove##" + text1).c_str()))
			{
				this->pointLights.erase(std::next(this->pointLights.begin(), i));
				i--;
				continue;
			}

			ImGui::Text("Position");
			ImGui::SameLine();
			vec3 pos = this->pointLights[i].getPosition();
			ImGui::SliderFloat3(std::string("Position##" + text1).c_str(), &pos[0], -10.0f, 10.0f, "%.3f");
			this->pointLights[i].setPosition(pos);

			float strength = this->pointLights[i].getStrength();
			ImGui::Text("Strength");
			ImGui::SameLine();
			ImGui::SliderFloat(std::string("Strength##" + text1).c_str(), &strength, 0.0f, 100.0f);
			this->pointLights[i].setStrength(strength);

			vec3 color = this->pointLights[i].getColor();
			ImGui::ColorEdit3(std::string("Color##" + text1).c_str(), &color[0], ImGuiColorEditFlags_Uint8);
			this->pointLights[i].setColor(color);
		}

		ImGui::End();
	}

	void View::renderDepthMaps()
	{
		glViewport(0, 0, LightSource::shadowResolution.x, LightSource::shadowResolution.y);
		glClear(GL_DEPTH_BUFFER_BIT);
		glBindFramebuffer(GL_FRAMEBUFFER, dirLight.getDepthMapFramebuffer());
	}

	void View::renderScene()
	{
		window.fillWithColorRGB({ 0, 0, 0 });

		checkImGUI();

		meshShader.use();

		meshShader.setMat4("view", camera.getViewMatrix());
		meshShader.setMat4("proj", camera.getProjectionMatrix());
		meshShader.setMat4("model", glm::mat4(1.0f));

		meshShader.setInt("directionalLightCount", 1);
		dirLight.setLightInShader(meshShader, "directionalLights[0].");

		meshShader.setInt("pointLightCount", this->pointLights.size());
		for (int i = 0; i < this->pointLights.size(); ++i)
		{
			std::string prefix = std::format("pointLights[{}].", i);

			pointLights[i].setLightInShader(meshShader, prefix);
		}

		backpack.render(meshShader);

		window.swapBuffers();
	}
}
