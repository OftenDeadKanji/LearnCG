#pragma once
#include "submesh.h"
#include "../Rendering/Texture/texture.h"

namespace RedWood
{
	class Mesh
	{
	public:
		explicit Mesh(const std::string& filePath);
	private:
		void processNode(const aiScene* scene, const aiNode* node);
		SubMesh processSubMesh(const aiMesh* mesh, const aiScene* scene);
		std::vector<Texture*> loadMaterialTextures(const aiMaterial* material, aiTextureType type, const std::string& typeName);

		std::vector<SubMesh> subMeshes;
	};
}