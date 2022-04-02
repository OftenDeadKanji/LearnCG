#pragma once
#include "../Shader/shader.h"

namespace RedWood
{
	class LightSource
	{
	public:
		explicit LightSource(const vec3& color);
		LightSource(const vec3& color, float ambient, float diffuse, float specular);
		LightSource(const vec3& color, const vec3& ambient, const vec3& diffuse, const vec3& specular);

		virtual void setLightInShader(const Shader& shader, const std::string& prefix) const;
	protected:
		vec3 color;

		static constexpr float defaultAmbientFactor = 0.05;;
		vec3 ambient;
		static constexpr float defaultDiffuseFactor = 0.8f;
		vec3 diffuse;
		static constexpr float defaultSpecularFactor = 1.0f;
		vec3 specular;
	};
}