#include "pch.h"
#include "transform.h"

namespace RedWood
{
	Transform::Transform(const vec3& position, const glm::quat& rotation, const vec3& scale)
		: position(position), rotation(rotation), scale(scale)
	{
	}
	Transform::Transform(const Transform& other)
	{
	}
	Transform::Transform(Transform&& other) noexcept
	{
	}

	Transform& Transform::operator=(const Transform&)
	{

	}
	Transform& Transform::operator=(Transform&&) noexcept
	{

	}
}