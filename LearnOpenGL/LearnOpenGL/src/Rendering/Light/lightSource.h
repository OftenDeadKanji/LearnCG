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

		void setColor(const vec3& color);
		vec3 getColor() const;

		//void renderDepthMap();

		GLuint getDepthMapFramebuffer() const;

		static constexpr vec2 shadowResolution{ 1024, 1024 };
		const Texture& getDepthMap() const;
	protected:
		void createDepthMap();

		vec3 color;

		float ambientFactor = 0.05f;
		vec3 ambient;
		float diffuseFactor = 0.8f;
		vec3 diffuse;
		float specularFactor = 1.0f;
		vec3 specular;

		GLuint depthMapFBO{};
		Texture depthMap;
	};
}