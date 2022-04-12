#include "pch.h"
#include "lightSource.h"

namespace RedWood
{
	LightSource::LightSource(const vec3& color)
		: color(color), ambient(color * ambientFactor), diffuse(color * diffuseFactor), specular(color * specularFactor), depthMap(Texture::createDepthMap(shadowResolution))
	{
		createDepthMap();
	}
	LightSource::LightSource(const vec3& color, float ambient, float diffuse, float specular)
		: color(color), ambientFactor(ambient), ambient(color * ambient), diffuseFactor(diffuse), diffuse(color* diffuse), specularFactor(specular), specular(color* specular), depthMap(Texture::createDepthMap(shadowResolution))
	{
		createDepthMap();
	}
	LightSource::LightSource(const vec3& color, const vec3& ambient, const vec3& diffuse, const vec3& specular)
		: color(color), ambient(ambient), diffuse(diffuse), specular(specular), depthMap(Texture::createDepthMap(shadowResolution))
	{
		createDepthMap();

		ambientFactor = this->ambient.r / this->color.r;
		diffuseFactor = this->diffuse.r / this->color.r;
		specularFactor = this->specular.r / this->color.r;
	}
	void LightSource::setLightInShader(const Shader& shader, const std::string& prefix) const
	{
		//shader.setVec3f(prefix + "color", this->color);
		shader.setVec3f(prefix + "light.ambient", this->ambient);
		shader.setVec3f(prefix + "light.diffuse", this->diffuse);
		shader.setVec3f(prefix + "light.specular", this->specular);
	}

	void LightSource::setColor(const vec3& color)
	{
		this->color = color;

		this->ambient = color * this->ambientFactor;
		this->diffuse = color * this->diffuseFactor;
		this->specular = color * this->specularFactor;
	}

	vec3 LightSource::getColor() const
	{
		return this->color;
	}

	GLuint LightSource::getDepthMapFramebuffer() const
	{
		return this->depthMapFBO;
	}

	const Texture& LightSource::getDepthMap() const
	{
		return this->depthMap;
	}

	void LightSource::createDepthMap()
	{
		glGenFramebuffers(1, &this->depthMapFBO);
		glBindFramebuffer(GL_FRAMEBUFFER, this->depthMapFBO);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, this->depthMap.id, 0);
		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
}
