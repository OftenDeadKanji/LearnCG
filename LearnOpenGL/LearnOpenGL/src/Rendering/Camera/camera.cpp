#include "pch.h"
#include "camera.h"

namespace RedWood
{
	Camera::Camera(const vec3& position, const vec3& target)
		: position(position)
	{
		vec3 direction = target - position;
		if(glm::length2(direction))
		{
			direction = glm::normalize(direction);
		}
		
		this->orientation = glm::quatLookAt(direction, Camera::worldUp);
	}

	glm::mat4 Camera::getViewMatrix() const
	{
		glm::mat4 viewMat = glm::mat4_cast(glm::inverse(this->orientation));
		viewMat = glm::translate(viewMat, -position);

		return viewMat;
	}

	glm::mat4 Camera::getProjectionMatrix() const
	{
		return glm::perspective(glm::radians(45.0f), 1600.0f / 900.0f, 0.1f, 100.0f);
	}

	glm::vec3 Camera::getPosition() const
	{
		return this->position;
	}

	glm::vec3 Camera::getForward() const
	{
		return this->orientation * glm::vec3(0.0f, 0.0f, -1.0f) ;
	}

	glm::vec3 Camera::getRight() const
	{
		return this->orientation * glm::vec3(1.0, 0.0f, 0.0f);
	}

	glm::vec3 Camera::getUp() const
	{
		return this->orientation * glm::vec3(0.0f, 1.0f, 0.0f);
	}

	void Camera::moveForward(float movement)
	{
		this->position += getForward() * movement;
	}

	void Camera::moveLeft(float movement)
	{
		this->position += getRight() * movement;
	}

	void Camera::moveUp(float movement)
	{
		this->position += getUp() * movement;
	}

	void Camera::pitch(float pitchInDeg)
	{
		glm::quat q = glm::angleAxis(glm::radians(pitchInDeg), this->getRight());
		this->orientation = glm::normalize(q * this->orientation);
	}

	void Camera::yaw(float yawInDeg)
	{
		glm::quat q = glm::angleAxis(glm::radians(yawInDeg), this->getUp());
		this->orientation = glm::normalize(q * this->orientation);
	}

	void Camera::turn(float turnRadians)
	{
		glm::quat q = glm::angleAxis(glm::radians(turnRadians), glm::vec3(0.0f, 1.0f, 0.0f));
		this->orientation = glm::normalize(q * this->orientation);
	}
}
