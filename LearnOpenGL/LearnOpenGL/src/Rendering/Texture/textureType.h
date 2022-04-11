#ifndef TEXTURETYPE_H
#define TEXTURETYPE_H

namespace RedWood
{
	enum class TextureType
	{
		Diffuse,
		Specular,
		Normal,

		DepthMap
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
		default:
			return "None";
		}
	}
}

#endif // TEXTURETYPE_H
