#include "directionalLight.h"

namespace RedWood
{
	DirectionalLight::DirectionalLight(vec3 color, vec3 direction)
		: LightSource(color), direction(glm::normalize(direction))
	{}

	void DirectionalLight::setLightInShader(const Shader & shader, const std::string & prefix) const
	{
		LightSource::setLightInShader(shader, prefix);
		shader.setVec3f(prefix + "direction", this->direction);
	}

	vec3 DirectionalLight::getDirection() const
	{
		return this->direction;
	}

	void DirectionalLight::setDirection(const vec3& dir)
	{
		this->direction = dir;
	}
}
