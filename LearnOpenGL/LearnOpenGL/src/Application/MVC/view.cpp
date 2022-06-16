#include "view.h"
#include <string>
#include <format>
#include <iostream>
#include "glad/glad.h"
#include "controller.h"
#include "../../EventSystem/Keyboard/keyboard.h"
#include "../../EventSystem/Mouse/mouse.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"



namespace RedWood::MVC
{
	View::View(MVC::Controller& controller)
		: controller(controller)
		, window(WindowProperties({ 1600, 900 }, WindowMode::Windowed, "LearnOpenGL", ""))
		, camera({ 0.0f, 0.0f, 5.0f }, { 0.5f, 0.0f, 0.0f })
		, dirLight({ 1.0f, 1.0f, 1.0f }, { 0.5f, -1.0f, -1.0f })
		, dirLightDirection({ 0.5f, -1.0f, -1.0f })
		, dirLightColor({ 1.0f, 1.0f, 1.0f })
		, backpack("Resources/Models/primitives/sphere.obj", { 0.0f, 0.0f, 0.0f })
		//, backpack("Resources/Models/backpack/backpack.obj", { 0.0f, 0.0f, 0.0f })
		, floor("Resources/Models/primitives/plane.obj", { 0.0f, -1.8f, 0.0f })
	{
		this->window.attachEventManager(this->eventManager);

		this->mousePrevPos = window.getSize() * 0.5f;

		this->initShaders();
	}

	void View::checkInput(const float deltaTime)
	{
		eventManager.checkForEvents();
		while (!eventManager.isEventQueueEmpty())
		{
			const auto eventType = this->eventManager.getEventTypeFromQueue();
			switch (eventType)
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
				if (EventSystem::Mouse::buttons[static_cast<int>(EventSystem::MouseButton::Right)])
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

		if (EventSystem::Keyboard::keys[static_cast<size_t>(EventSystem::KeyboardKey::KeyA)])
		{
			camera.moveLeft(-7 * deltaTime);
		}
		if (EventSystem::Keyboard::keys[static_cast<size_t>(EventSystem::KeyboardKey::KeyD)])
		{
			camera.moveLeft(7 * deltaTime);
		}
		if (EventSystem::Keyboard::keys[static_cast<size_t>(EventSystem::KeyboardKey::KeyS)])
		{
			camera.moveForward(-7 * deltaTime);
		}
		if (EventSystem::Keyboard::keys[static_cast<size_t>(EventSystem::KeyboardKey::KeyW)])
		{
			camera.moveForward(7 * deltaTime);
		}
		if (EventSystem::Keyboard::keys[static_cast<size_t>(EventSystem::KeyboardKey::KeyQ)])
		{
			camera.moveUp(-7 * deltaTime);
		}
		if (EventSystem::Keyboard::keys[static_cast<size_t>(EventSystem::KeyboardKey::KeyE)])
		{
			camera.moveUp(7 * deltaTime);
		}

		if (EventSystem::Mouse::buttons[static_cast<int>(EventSystem::MouseButton::Right)])
		{
			const float yaw = EventSystem::Mouse::position.x - this->mousePrevPos.x;
			const float pitch = EventSystem::Mouse::position.y - this->mousePrevPos.y;

			const vec3 cameraRotation(pitch, yaw, 0.0f);
			//this->camera.rotateCamera(cameraRotation * this->mouseSpeed * deltaTime);
			this->camera.turn(-yaw * this->mouseSpeed * deltaTime);
			this->camera.pitch(-pitch * this->mouseSpeed * deltaTime);

			this->mousePrevPos = EventSystem::Mouse::position;
		}
	}

	void View::render(float deltaTime)
	{
		glViewport(0, 0, LightSource::shadowResolution.x, LightSource::shadowResolution.y);
		glCullFace(GL_FRONT);
		renderDepthMaps();

		glViewport(0, 0, this->window.getSize().x, this->window.getSize().y);
		glCullFace(GL_BACK);
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
		if (ImGui::Button("Add"))
		{
			this->pointLights.push_back(PointLight({ 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f, 0.0f }, 10.0f));
		}
		for (auto i = 0; i < this->pointLights.size(); ++i)
		{
			std::string text1 = std::format("Point light #{}", i + 1);
			ImGui::Text(text1.c_str());
			ImGui::SameLine();
			if (ImGui::Button(std::string("Remove##" + text1).c_str()))
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

	void View::initShaders()
	{
		auto meshVert = SubShader::createShaderFromFile("Resources/Shaders/model_main.vert", SubShader::Type::Vertex);
		auto meshFrag = SubShader::createShaderFromFile("Resources/Shaders/model_main.frag", SubShader::Type::Fragment);

		this->meshShader.attachSubShader(meshVert);
		this->meshShader.attachSubShader(meshFrag);

		if (!this->meshShader.tryToLinkShader())
		{
			std::cout << "Linking mesh shader failed.\n";
		}

		auto depthMapVert = SubShader::createShaderFromFile("Resources/Shaders/depthMap.vert", SubShader::Type::Vertex);
		auto depthMapFrag = SubShader::createShaderFromFile("Resources/Shaders/depthMap.frag", SubShader::Type::Fragment);

		this->depthMapShader.attachSubShader(depthMapVert);
		this->depthMapShader.attachSubShader(depthMapFrag);

		if (!this->depthMapShader.tryToLinkShader())
		{
			std::cout << "Linking depth map shader failed.\n";
		}
	}

	void View::renderDepthMaps()
	{

		glBindFramebuffer(GL_FRAMEBUFFER, dirLight.getDepthMapFramebuffer());
		glClear(GL_DEPTH_BUFFER_BIT);

		vec3 dirLightPos = -2.0f * this->dirLightDirection;
		glm::mat4 lightView = glm::lookAt
		(
			dirLightPos,
			vec3(0.0f, 0.0f, 0.0f),
			vec3(0.0f, 1.0f, 0.0f)
		);
		float nearPlane = 1.0f, farPlane = 9.5f;
		mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, nearPlane, farPlane);
		mat4 lightSpaceMatrix = lightProjection * lightView;

		depthMapShader.use();
		depthMapShader.setMat4("lightSpaceMatrix", lightSpaceMatrix);


		backpack.render(depthMapShader);

		auto tr = mat4(1.0f);
		tr = glm::translate(tr, { 0.0f, -2.0f, 0.0f });
		depthMapShader.setMat4("model", tr);
		floor.render(depthMapShader);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void View::renderScene()
	{
		window.fillWithColorRGB({ 100, 250, 0 });

		checkImGUI();

		vec3 dirLightPos = -2.0f * this->dirLightDirection;
		glm::mat4 lightView = glm::lookAt
		(
			dirLightPos,
			vec3(0.0f, 0.0f, 0.0f),
			vec3(0.0f, 1.0f, 0.0f)
		);
		constexpr float nearPlane = 1.0f, farPlane = 9.5f;
		const mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, nearPlane, farPlane);
		mat4 lightSpaceMatrix = lightProjection * lightView;

		meshShader.use();
		setCameraUniforms(meshShader);
		setLightUniforms(meshShader);

		meshShader.setMat4("lightSpaceMatrix", lightSpaceMatrix);
		meshShader.setVec3f("lightPos", dirLightPos);
		glActiveTexture(GL_TEXTURE0);
		meshShader.setInt("shadowMap", 0);
		dirLight.getDepthMap().bind();

		meshShader.setMat4("model", glm::mat4(1.0f));
		backpack.render(meshShader);

		glActiveTexture(GL_TEXTURE0);
		dirLight.getDepthMap().bind();
		auto tr = mat4(1.0f);
		tr = glm::translate(tr, { 0.0f, -2.0f, 0.0f });
		meshShader.setMat4("model", tr);
		floor.render(meshShader);
		
		window.swapBuffers();
	}

	void View::setCameraUniforms(const Shader& shader) const
	{
		shader.setMat4("view", camera.getViewMatrix());
		shader.setMat4("proj", camera.getProjectionMatrix());

		shader.setVec3f("cameraPos", camera.getPosition());
	}

	void View::setLightUniforms(const Shader& shader) const
	{
		shader.setInt("directionalLightCount", 1);
		dirLight.setLightInShader(shader, "directionalLights[0].");

		shader.setInt("pointLightCount", this->pointLights.size());
		for (int i = 0; i < this->pointLights.size(); ++i)
		{
			std::string prefix = std::format("pointLights[{}].", i);
		
			pointLights[i].setLightInShader(shader, prefix);
		}
	}
}
