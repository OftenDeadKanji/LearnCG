#pragma once

namespace RedWood
{
	struct Transform
	{
		vec3 position;
		glm::quat rotation;
		vec3 scale;

		explicit Transform(const vec3& position = { 0.0f, 0.0f, 0.0f }, const glm::quat& rotation = { 1.0f, 0.0f, 0.0f, 0.0f}, const vec3& scale = {1.0f, 1.0f, 1.0f});
		Transform(const Transform& other);
		Transform(Transform&& other) noexcept;
		~Transform() = default;

		Transform& operator=(const Transform& other);
		Transform& operator=(Transform&& other) noexcept;
	};
}