#pragma once
#include "../Rendering/Texture/texture.h"

namespace RedWood
{
	class ResourceManager
	{
	private:
		ResourceManager() = default;
	public:
		ResourceManager(const ResourceManager&) = delete;
		ResourceManager(ResourceManager&&) = delete;
		~ResourceManager();

		ResourceManager& operator=(const ResourceManager&) = delete;
		ResourceManager& operator=(ResourceManager&&) = delete;

		static ResourceManager& getInstance();

		Texture* getTexture(const std::string& textureFilePath, TextureType type);
		void unloadTexture(const std::string& textureFilePath);
		void unloadTexture(const Texture& texture);
		static ResourceManager* instance;

		std::unordered_map<std::string, Texture> textures;
	};
}