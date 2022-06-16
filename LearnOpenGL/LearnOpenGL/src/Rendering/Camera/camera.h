#pragma once
#include "../../Utilities/types.h"
#include "glm/glm.hpp"

#include "glm/gtc/quaternion.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/quaternion.hpp"
#include "glm/gtx/rotate_vector.hpp"

namespace RedWood
{
	class Camera
	{
	public:
		Camera(const vec3& position, const vec3& target);

		glm::mat4 getViewMatrix() const;
		glm::mat4 getProjectionMatrix() const;

		glm::vec3 getPosition() const;

		glm::vec3 getForward() const;
		glm::vec3 getRight() const;
		glm::vec3 getUp() const;

		void moveForward(float movement);
		void moveLeft(float movement);
		void moveUp(float movement);

		void pitch(float pitchInDeg);
		void yaw(float yawInDeg);
		void turn(float turnRadians);

		void renderScene() const;
	private:
		vec3 position{};

		static constexpr vec3 worldUp = { 0.0f, 1.0f, 0.0f };

		glm::quat orientation;
	};
}
