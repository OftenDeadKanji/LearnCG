#pragma once

namespace RedWood
{
	class Camera
	{
	public:
		Camera(const vec3& position, const vec3& target);

		glm::mat4 getViewMatrix() const;
		glm::mat4 getProjectionMatrix() const;

		void move(float distance, const glm::vec3& direction);
		void move(const glm::vec3& newPosition);

		void moveToLocalRight(float distance);
		void moveToLocalUp(float distance);
		void moveToLocalFront(float distance);

		void pitchCamera(float angleInDeg);
		void yawCamera(float angleInDeg);
		void rotateCamera(vec3 angles);
	private:
		vec3 position {};

		static constexpr vec3 worldUp = { 0.0f, 1.0f, 0.0f };

		glm::quat rotation;
	};
}
