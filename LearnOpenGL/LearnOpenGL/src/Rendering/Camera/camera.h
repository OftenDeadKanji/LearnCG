#pragma once

namespace RedWood
{
	class Camera
	{
	public:
		Camera(const vec3& position, const vec3& target);

		glm::mat4 getViewMatrix() const;
		glm::mat4 getProjectionMatrix() const;

		glm::vec3 getPosition() const;

		void move(float distance, const glm::vec3& direction);
		void move(const glm::vec3& newPosition);

		void moveToLocalRight(float distance);
		void moveToLocalUp(float distance);
		void moveToLocalFront(float distance);

		void rotateCamera(vec3 angles);

		glm::vec3 getForward() const {
			return glm::conjugate(this->orientation) * glm::vec3(0.0f, 0.0f, -1.0f);
		}

		glm::vec3 getLeft() const {
			return glm::conjugate(this->orientation) * glm::vec3(-1.0, 0.0f, 0.0f);
		}

		glm::vec3 getUp() const {
			return glm::conjugate(this->orientation) * glm::vec3(0.0f, 1.0f, 0.0f);
		}

		void moveForward(float movement) {
			this->position += getForward() * movement;
		}

		void moveLeft(float movement) {
			this->position += getLeft() * movement;
		}

		void moveUp(float movement) {
			this->position += getUp() * movement;
		}

		void rotate(float angle, const glm::vec3& axis);
		void rotate(const glm::quat& rotation);

		void pitch(float pitchInDeg);
		void yaw(float yawInDeg);
		void turn(float turnRadians);
	private:
		vec3 position {};

		static constexpr vec3 worldUp = { 0.0f, 1.0f, 0.0f };

		glm::quat orientation;
	};
}
