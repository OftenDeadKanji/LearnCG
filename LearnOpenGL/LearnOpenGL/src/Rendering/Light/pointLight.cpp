#include "pch.h"
#include "pointLight.h"

namespace RedWood
{
	PointLight::PointLight(const glm::vec3 color, const vec3& position, float strength)
		: LightSource(color), position(position), strength(strength)
	{
		this->attenuation.constant = 1.0f;
		this->attenuation.linear = 4.5452f * powf(strength, -1.004f);
		this->attenuation.quadratic = 82.445f * powf(strength, -2.019f);
	}
	void PointLight::setLightInShader(const Shader& shader, const std::string& prefix) const
	{
		LightSource::setLightInShader(shader, prefix);
		shader.setVec3f(prefix + "position", this->position);
		shader.setFloat(prefix + "attenuation.constant", this->attenuation.constant);
		shader.setFloat(prefix + "attenuation.linear", this->attenuation.linear);
		shader.setFloat(prefix + "attenuation.quadratic", this->attenuation.quadratic);
	}

	vec3 PointLight::getPosition() const
	{
		return this->position;
	}

	void PointLight::setPosition(const vec3& pos)
	{
		this->position = pos;
	}

	float PointLight::getStrength() const
	{
		return this->strength;
	}

	void PointLight::setStrength(float strength)
	{
		this->strength = strength;

		this->attenuation.linear = 4.5452f * powf(strength, -1.004f);
		this->attenuation.quadratic = 82.445f * powf(strength, -2.019f);
	}
}
