#include "pch.h"
#include "camera.h"

namespace RedWood
{
	Camera::Camera(const vec3& position, const vec3& target)
		: position(position)
	{
		this->orientation = glm::quatLookAt(target, Camera::worldUp);
	}

	glm::mat4 Camera::getViewMatrix() const
	{
		glm::mat4 translate(1.0f);
		translate = glm::translate(translate, this->position);

		const glm::mat4 rotate = glm::mat4_cast(this->orientation);

		return rotate * translate;
	}

	glm::mat4 Camera::getProjectionMatrix() const
	{
		return glm::perspective(glm::radians(45.0f), 1600.0f / 900.0f, 0.1f, 100.0f);
	}

	glm::vec3 Camera::getPosition() const
	{
		return this->position;
	}

	void Camera::move(float distance, const glm::vec3& direction)
	{
		this->position += distance * glm::normalize(direction);
	}

	void Camera::move(const glm::vec3& newPosition)
	{
		this->position = newPosition;
	}

	void Camera::moveToLocalRight(float distance)
	{
		const auto right = glm::vec3(-1.0f, 0.0f, 0.0f) * this->orientation;
		this->position += distance * right;
	}

	void Camera::moveToLocalUp(float distance)
	{
		const auto up =  glm::vec3(0.0f, -1.0f, 0.0f) * this->orientation;
		this->position += distance * up;
	}

	void Camera::moveToLocalFront(float distance)
	{
		const auto forward = glm::vec3(0.0f, 0.0f, 1.0f) * this->orientation;
		this->position += distance * forward;
	}

	void Camera::rotateCamera(vec3 anglesInDeg)
	{
		const auto x = glm::angleAxis(glm::radians(anglesInDeg.x), vec3(1.0f, 0.0f, 0.0f));
		const auto y = glm::angleAxis(glm::radians(anglesInDeg.y), vec3(0.0f, 1.0f, 0.0f));
		
		this->orientation = glm::normalize(x * this->orientation * y);
	}
}
