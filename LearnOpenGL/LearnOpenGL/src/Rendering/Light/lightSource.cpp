#include "pch.h"
#include "lightSource.h"

namespace RedWood
{
	LightSource::LightSource(const vec3& color)
		: color(color), ambient(color * LightSource::defaultAmbientFactor), diffuse(color * LightSource::defaultDiffuseFactor), specular(color * LightSource::defaultSpecularFactor)
	{
	}
	LightSource::LightSource(const vec3& color, float ambient, float diffuse, float specular)
		: color(color), ambient(color * ambient), diffuse(color* diffuse), specular(color* specular)
	{
	}
	LightSource::LightSource(const vec3& color, const vec3& ambient, const vec3& diffuse, const vec3& specular)
		: color(color), ambient(ambient), diffuse(diffuse), specular(specular)
	{
	}
	void LightSource::setLightInShader(const Shader& shader, const std::string& prefix) const
	{
		shader.setVec3f(prefix + "color", this->color);
		shader.setVec3f(prefix + "ambient", this->ambient);
		shader.setVec3f(prefix + "diffuse", this->diffuse);
		shader.setVec3f(prefix + "specular", this->specular);
	}
}