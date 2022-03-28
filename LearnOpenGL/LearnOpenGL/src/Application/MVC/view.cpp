#include "pch.h"
#include "view.h"
#include "controller.h"

namespace RedWood::MVC
{
	View::View(MVC::Controller& controller)
		: controller(controller),
		window(WindowProperties({ 1600, 900 }, WindowMode::Windowed, "LearnOpenGL", "")),
		camera({ 0.0f, 0.0f, -5.0f }, { 0.0f, 0.0f, 0.0f }),
		backpack("Resources/Models/backpack/backpack.obj")
	{
		this->window.attachEventManager(this->eventManager);

		auto mainVert = SubShader::createShaderFromFile("Shaders/main.vert", SubShader::Type::Vertex);
		auto mainFrag = SubShader::createShaderFromFile("Shaders/main.frag", SubShader::Type::Fragment);

		this->mainShader.attachSubShader(mainVert);
		this->mainShader.attachSubShader(mainFrag);

		if(!this->mainShader.tryToLinkShader())
		{
			std::cout << "Linking main shader failed.\n";
		}

		triangle = {
			Vertex
			{
				{-0.5f, -0.5f, 0.0f},
				{0.0f, 0.0f},
				{0.0f, 0.0f, 0.0f}
			},
			Vertex
			{
				{0.5f, -0.5f, 0.0f},
				{0.0f, 0.0f},
				{0.0f, 0.0f, 0.0f}
			},
			Vertex
			{
				{0.0f, 0.5f, 0.0f},
				{0.0f, 0.0f},
				{0.0f, 0.0f, 0.0f}
			}
		};

		/*glGenVertexArrays(1, &triangleVAO);
		glGenBuffers(1, &triangleVBO);

		glBindVertexArray(triangleVAO);
		glBindBuffer(GL_ARRAY_BUFFER, triangleVBO);

		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * triangle.size(), triangle.data(), GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, position)));
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, textureCoords)));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, normal)));
		glEnableVertexAttribArray(2);*/

		this->mousePrevPos = window.getSize() * 0.5f;

		auto meshVert = SubShader::createShaderFromFile("Shaders/model_main.vert", SubShader::Type::Vertex);
		auto meshFrag = SubShader::createShaderFromFile("Shaders/model_main.frag", SubShader::Type::Fragment);

		this->meshShader.attachSubShader(meshVert);
		this->meshShader.attachSubShader(meshFrag);

		if (!this->meshShader.tryToLinkShader())
		{
			std::cout << "Linking main shader failed.\n";
		}
	}

	void View::checkInput()
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
					break;
				case EventSystem::EventType::MouseButtonReleased:
					break;
				case EventSystem::EventType::MouseCursorMoved:
					break;
			}
		}

		if(EventSystem::Keyboard::keys[static_cast<size_t>(EventSystem::KeyboardKey::KeyA)])
		{
			camera.moveToLocalRight(-0.001f);
		}
		if(EventSystem::Keyboard::keys[static_cast<size_t>(EventSystem::KeyboardKey::KeyD)])
		{
			camera.moveToLocalRight(0.001f);
		}
		if(EventSystem::Keyboard::keys[static_cast<size_t>(EventSystem::KeyboardKey::KeyS)])
		{
			camera.moveToLocalFront(-0.001f);
		}
		if(EventSystem::Keyboard::keys[static_cast<size_t>(EventSystem::KeyboardKey::KeyW)])
		{
			camera.moveToLocalFront(0.001f);
		}

		//if(EventSystem::Mouse::buttons[static_cast<size_t>(EventSystem::MouseButton::Left)])
		//{
			float yaw = EventSystem::Mouse::position.x - this->mousePrevPos.x;
			float pitch = EventSystem::Mouse::position.y - this->mousePrevPos.y;

			vec3 cameraRotation(pitch, yaw, 0.0f);
			this->camera.rotateCamera(cameraRotation * 0.03f);

			this->mousePrevPos = EventSystem::Mouse::position;
		//}
	}

	void View::render()
	{
		window.fillWithColorRGB({ 120, 230, 85 });

		//mainShader.use();
		//mainShader.setMat4("viewMatrix", camera.getViewMatrix());
		//mainShader.setMat4("projMatrix", camera.getProjectionMatrix());
		//
		//glBindVertexArray(this->triangleVAO);
		//glDrawArrays(GL_TRIANGLES, 0, 3);

		meshShader.use();
		meshShader.setMat4("view", camera.getViewMatrix());
		meshShader.setMat4("proj", camera.getProjectionMatrix());
		backpack.render(meshShader);

		window.swapBuffers();
	}
}
