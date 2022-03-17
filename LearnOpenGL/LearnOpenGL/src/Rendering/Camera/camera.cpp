#include "pch.h"
#include "camera.h"

namespace RedWood
{
	Camera::Camera(const vec3& position, const vec3& target)
		: position(position)
	{
		this->rotation = glm::quatLookAt(target, Camera::worldUp);
	}

	glm::mat4 Camera::getViewMatrix() const
	{
		//auto view = glm::toMat4(this->rotation);
		//view = glm::translate(view, this->position);

		glm::mat4 translate(1.0f);
		translate = glm::translate(translate, this->position);

		glm::mat4 rotate(1.0f);
		rotate = glm::mat4_cast(this->rotation);

		//auto forward = glm::vec3(0.0f, 0.0f, 1.0f);
		//forward = glm::rotate(this->rotation, forward);

		//auto normalLookAt = glm::lookAt(this->position, forward, this->worldUp);

		return rotate * translate;
	}

	glm::mat4 Camera::getProjectionMatrix() const
	{
		return glm::perspective(glm::radians(45.0f), 1600.0f / 900.0f, 0.1f, 100.0f);
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
		const auto right = glm::rotate(this->rotation, glm::vec3(-1.0f, 0.0f, 0.0f));
		this->position += distance * right;
	}

	void Camera::moveToLocalUp(float distance)
	{
		const auto up =  glm::rotate(this->rotation, glm::vec3(0.0f, 1.0f, 0.0f));
		this->position += distance * up;
	}

	void Camera::moveToLocalFront(float distance)
	{
		const auto forward = glm::rotate(this->rotation, glm::vec3(0.0f, 0.0f, 1.0f));
		this->position += distance * forward;
	}

	void Camera::pitchCamera(float angleInDeg)
	{
		
	}

	void Camera::yawCamera(float angleInDeg)
	{
		
	}

	void Camera::rotateCamera(vec3 anglesInDeg)
	{
		//std::cout << "\n\n" << anglesInDeg.x << '\t' << anglesInDeg.y << '\t' << anglesInDeg.z << '\n';
		const glm::quat rotation(glm::radians(anglesInDeg));

		//auto euler = glm::degrees(glm::eulerAngles(this->rotation));
		//std::cout << euler.x << '\t' << euler.y << '\t' << euler.z << '\n';

		this->rotation = glm::normalize(this->rotation * rotation);
		

		//auto rot = glm::quat(glm::radians(vec3(0.1f, 0.0f, 0.0f)));
		//this->rotation *= rot;
		//euler = glm::degrees(glm::eulerAngles(this->rotation));
		//std::cout << euler.x << '\t' << euler.y << '\t' << euler.z << "\n\n";
	}
}
