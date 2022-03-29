#ifndef DIRECTIONALLIGHT_H
#define DIRECTIONALLIGHT_H

namespace RedWood
{
	class DirectionalLight
	{
	public:
		explicit DirectionalLight(vec3 direction, vec3 color = {0.95f, 0.95f, 0.95f});

		vec3 getDirection() const;
		vec3 getColor() const;
	private:
		vec3 direction;
		vec3 color;
	};
}
#endif // DIRECTIONALLIGHT_H