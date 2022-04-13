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
		//glm::mat4 translate(1.0f);
		//translate = glm::translate(translate, -this->position);

		glm::mat4 viewMat = glm::mat4_cast(this->orientation);
		viewMat = glm::translate(viewMat, -position);

		return viewMat;
	}

	glm::mat4 Camera::getProjectionMatrix() const
	{
		return glm::perspective(glm::radians(45.0f), 1600.0f / 900.0f, 0.1f, 100.0f);
	}

	glm::vec3 Camera::getPosition() const
	{
		//std::cout << this->position.x << '\t' << this->position.y << '\t' << this->position.z << '\n';
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
		const auto right = glm::vec3(1.0f, 0.0f, 0.0f) * this->orientation;
		this->position += distance * right;
	}

	void Camera::moveToLocalUp(float distance)
	{
		const auto up =  glm::vec3(0.0f, 1.0f, 0.0f) * this->orientation;
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

	void Camera::rotate(float angle, const glm::vec3& axis)
	{
		glm::quat q = glm::angleAxis(angle, axis);
		this->rotate(q);
	}

	void Camera::rotate(const glm::quat& rotation)
	{
		this->orientation = glm::normalize(rotation * this->orientation);
	}

	void Camera::pitch(float pitchInDeg)
	{
		this->rotate(glm::radians(pitchInDeg), { 1.0f, 0.0f, 0.0f });
	}

	void Camera::yaw(float yawInDeg)
	{
		this->rotate(glm::radians(yawInDeg), { 0.0f, 1.0f, 0.0f });
	}

	void Camera::turn(float turnRadians)
	{
		glm::quat q = glm::angleAxis(glm::radians(turnRadians), this->orientation * glm::vec3(0.0f, 1.0f, 0.0f));
		rotate(q);
	}
}
