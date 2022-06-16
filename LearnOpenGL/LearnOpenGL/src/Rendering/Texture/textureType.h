#ifndef TEXTURETYPE_H
#define TEXTURETYPE_H
#include <string>

namespace RedWood
{
	enum class TextureType
	{
		Diffuse,
		Specular,
		Normal,

		DepthMap,
		DepthCubeMap
	};

	constexpr std::string TextureTypeToString(TextureType type)
	{
		switch (type)
		{
		case TextureType::Diffuse:
			return "Diffuse";
		case TextureType::Specular:
			return "Specular";
		case TextureType::Normal:
			return "Normal";
		case TextureType::DepthMap:
			return "DepthMap";
		case TextureType::DepthCubeMap:
			return "DepthCubeMap";
		default:
			return "None";
		}
	}
}

#endif // TEXTURETYPE_H
