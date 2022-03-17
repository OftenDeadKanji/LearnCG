#include "pch.h"
#include "view.h"
#include "../../Rendering/renderer.h"
#include "controller.h"

namespace RedWood::MVC
{
	View::View(MVC::Controller& controller)
		: controller(controller),
		window(WindowProperties({ 1600, 900 }, WindowMode::Windowed, "LearnOpenGL", "")),
		camera({ 0.0f, 0.0f, -5.0f }, { 0.0f, 0.0f, 0.0f })
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
				{0.9f, 0.5f, 0.1f, 1.0f},
				{0.0f, 0.0f},
				{0.0f, 0.0f, 0.0f}
			},
			Vertex
			{
				{0.5f, -0.5f, 0.0f},
				{0.3f, 0.1f, 0.1f, 1.0f},
				{0.0f, 0.0f},
				{0.0f, 0.0f, 0.0f}
			},
			Vertex
			{
				{0.0f, 0.5f, 0.0f},
				{0.3f, 0.5f, 0.5f, 1.0f},
				{0.0f, 0.0f},
				{0.0f, 0.0f, 0.0f}
			}
		};

		Renderer::bindVertexArray(triangleVAO);
		Renderer::bindVertexBuffer(triangleVBO);

		Renderer::bufferVertexBufferData(triangle.data(), sizeof(Vertex) * triangle.size());
		Renderer::setAttributesPointer(0, 3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, position));
		Renderer::setAttributesPointer(1, 4, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, color));
		Renderer::setAttributesPointer(2, 2, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, textureCoords));
		Renderer::setAttributesPointer(3, 3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, normal));

		//Renderer::unbindVertexBuffer();
		//Renderer::unbindVertexArray();

		this->mousePrevPos = window.getSize() * 0.5f;
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

		Renderer::useShader(mainShader);
		mainShader.setMat4("viewMatrix", camera.getViewMatrix());
		mainShader.setMat4("projMatrix", camera.getProjectionMatrix());

		Renderer::bindVertexArray(triangleVAO);
		Renderer::drawArrays(3);

		window.swapBuffers();
	}
}
