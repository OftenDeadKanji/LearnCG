#include "pch.h"
#include "texture.h"

namespace RedWood
{
	Texture::Texture(TextureType type)
		: type(type)
	{
		glGenTextures(1, &this->id);
	}

	Texture::Texture(Texture&& other) noexcept
		: type(other.type)
	{
		const auto tmp = this->id;
		this->id = other.id;
		other.id = tmp;
	}

	Texture::~Texture()
	{
		if(this->id)
		{
			glDeleteTextures(1, &this->id);
		}
	}

	Texture& Texture::operator=(Texture&& other) noexcept
	{
		if(this != &other)
		{
			type = other.type;

			const auto tmp = this->id;
			this->id = other.id;
			other.id = tmp;
		}

		return *this;
	}

	Texture Texture::createTextureFromFile(std::string filePath, TextureType type)
	{
		Texture toReturn(type);
		toReturn.path = std::move(filePath);

		int width, height, nrChannels;
		unsigned char* data = stbi_load(toReturn.path.c_str(), &width, &height, &nrChannels, 0);
		if(!data)
		{
			std::cout << "Loading texture failed\n";
		}

		toReturn.bind();

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(data);

		return toReturn;
	}

	void Texture::bind() const
	{
		glBindTexture(GL_TEXTURE_2D, id);
	}

	void Texture::unbind() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}
