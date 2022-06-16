#pragma once
#include "lightSource.h"
#include "attenuation.h"

namespace RedWood
{
	class PointLight : public LightSource
	{
	public:
		PointLight(const glm::vec3 color, const vec3& position, float strength);

		void setLightInShader(const Shader& shader, const std::string& prefix) const override;

		vec3 getPosition() const;
		void setPosition(const vec3& pos);

		float getStrength() const;
		void setStrength(float strength);
	private:
		void createDepthMap() override;

		vec3 position;
		float strength;

		Attenuation attenuation;
	};

}