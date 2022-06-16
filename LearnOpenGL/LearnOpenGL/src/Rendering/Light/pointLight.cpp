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

	void PointLight::createDepthMap()
	{
		glBindTexture(GL_TEXTURE_CUBE_MAP, this->depthMap.id);
		for(auto i = 0; i < 6; ++i)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT, LightSource::shadowResolution.x, LightSource::shadowResolution.y, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
		}

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

		glBindFramebuffer(GL_FRAMEBUFFER, this->depthMapFBO);
		glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, this->depthMap.id, 0);
		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
}
