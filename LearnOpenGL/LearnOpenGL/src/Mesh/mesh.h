#pragma once
#include <string>
#include <vector>

#include "submesh.h"
#include "../Rendering/Texture/texture.h"
#include "../Utilities/types.h"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

namespace RedWood
{
	class Mesh
	{
	public:
		Mesh(const std::string& filePath, const vec3& position);

		void render(const Shader& shader);

		void setPosition(const vec3& position);
		void setRotation(const vec3& rotation);
		void setScale(const vec3& scale);
	private:
		void processNode(const aiScene* scene, const aiNode* node);
		SubMesh processSubMesh(const aiMesh* mesh, const aiScene* scene);
		std::vector<Texture*> loadMaterialTextures(const aiMaterial* material, aiTextureType assimpTextureType, TextureType type);

		std::vector<SubMesh> subMeshes;
		std::string directory;

		vec3 position{ 0.0f, 0.0f, 0.0f };
		vec3 rotation{ 0.0f, 0.0f, 0.0f }; //in deg
		vec3 scale{ 1.0f, 1.0f, 1.0f };

		bool withDiffuseTexture{};
		bool withSpecularTexture{};
		bool withNormalTexture{};
	};
}