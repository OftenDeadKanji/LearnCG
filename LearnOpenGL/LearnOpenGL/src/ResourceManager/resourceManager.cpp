#include "pch.h"
#include "resourceManager.h"

namespace RedWood
{
	ResourceManager* ResourceManager::instance{};

	ResourceManager::~ResourceManager()
	{
		delete instance;
	}

	ResourceManager& ResourceManager::getInstance()
	{
		return instance == nullptr ? *(instance = new ResourceManager()) : *instance;
	}

	Texture* ResourceManager::getTexture(const std::string& textureFilePath, TextureType type)
	{
		if(this->textures.contains(textureFilePath))
		{
			return &this->textures.at(textureFilePath);
		}

		this->textures.insert(std::make_pair(textureFilePath, Texture::createTextureFromFile(textureFilePath, type)));
		return &this->textures.at(textureFilePath);
	}

	void ResourceManager::unloadTexture(const std::string& textureFilePath)
	{
		if(const auto pos = this->textures.find(textureFilePath); pos != this->textures.end())
		{
			this->textures.erase(pos);
		}
	}

	void ResourceManager::unloadTexture(const Texture& texture)
	{
		this->unloadTexture(texture.path);
	}
}
