#include "pch.h"
#include "directionalLight.h"

namespace RedWood
{
	DirectionalLight::DirectionalLight(vec3 direction, vec3 color)
		: direction(glm::normalize(direction)), color(color)
	{}

	vec3 DirectionalLight::getDirection() const
	{
		return this->direction;
	}

	vec3 DirectionalLight::getColor() const
	{
		return this->color;
	}
}
