#include "pch.h"
#include "view.h"
#include "../../Rendering/renderer.h"
#include "controller.h"

namespace RedWood::MVC
{
	View::View(MVC::Controller& controller)
		: controller(controller), window(WindowProperties({ 1600, 900 }, WindowMode::Windowed, "LearnOpenGL", ""))
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

		float vertices[] = {
			-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f
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
	}

	void View::render()
	{
		window.fillWithColorRGB({ 120, 230, 85 });

		Renderer::useShader(mainShader);
		Renderer::bindVertexArray(triangleVAO);
		Renderer::drawArrays(3);

		window.swapBuffers();
	}
}
