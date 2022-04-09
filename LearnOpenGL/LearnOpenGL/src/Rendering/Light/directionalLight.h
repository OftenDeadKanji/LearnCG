#ifndef DIRECTIONALLIGHT_H
#define DIRECTIONALLIGHT_H
#include "lightSource.h"

namespace RedWood
{
	class DirectionalLight : public LightSource
	{
	public:
		DirectionalLight(vec3 color, vec3 direction);

		void setLightInShader(const Shader& shader, const std::string& prefix) const override;

		vec3 getDirection() const;
		void setDirection(const vec3& dir);
	private:
		vec3 direction;
	};
}
#endif // DIRECTIONALLIGHT_H