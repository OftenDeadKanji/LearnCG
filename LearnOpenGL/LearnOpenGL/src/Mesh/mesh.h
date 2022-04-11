#pragma once
#include "submesh.h"
#include "../Rendering/Texture/texture.h"

namespace RedWood
{
	class Mesh
	{
	public:
		explicit Mesh(const std::string& filePath);

		void render(const Shader& shader);
	private:
		void processNode(const aiScene* scene, const aiNode* node);
		SubMesh processSubMesh(const aiMesh* mesh, const aiScene* scene);
		std::vector<Texture*> loadMaterialTextures(const aiMaterial* material, aiTextureType assimpTextureType, TextureType type);

		std::vector<SubMesh> subMeshes;
		std::string directory;

		bool withDiffuseTexture{};
		bool withSpecularTexture{};
		bool withNormalTexture{};
	};
}