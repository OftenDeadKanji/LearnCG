#ifndef TEXTURE_H
#define TEXTURE_H

namespace RedWood
{
	struct Texture
	{
	private:
		Texture();
	public:
		Texture(const Texture&) = delete;
		Texture(Texture&&) noexcept;
		~Texture();

		Texture& operator=(const Texture&) = delete;
		Texture& operator=(Texture&&) noexcept;

		static Texture createTextureFromFile(std::string filePath);

		void bind() const;
		void unbind() const;

		GLuint id = 0;
		std::string path;
	};
}

#endif // TEXTURE_H