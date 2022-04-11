#ifndef TEXTURE_H
#define TEXTURE_H

#include "textureType.h"

namespace RedWood
{
	struct Texture
	{
	private:
		explicit Texture(TextureType type);
	public:
		Texture(const Texture&) = delete;
		Texture(Texture&&) noexcept;
		~Texture();

		Texture& operator=(const Texture&) = delete;
		Texture& operator=(Texture&&) noexcept;

		static Texture createTextureFromFile(std::string filePath, TextureType type);
		static Texture createDepthMap(const vec2& resolution);

		void bind() const;
		void unbind() const;

		GLuint id = 0;
		TextureType type;
		std::string path;
	};
}

#endif // TEXTURE_H