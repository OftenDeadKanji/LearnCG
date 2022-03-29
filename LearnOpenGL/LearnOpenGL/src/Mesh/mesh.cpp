#include "pch.h"
#include "mesh.h"
#include "../Rendering/Vertex/vertex.h"

namespace RedWood
{
	Mesh::Mesh(const std::string& filePath)
		: directory(filePath.substr(0, filePath.find_last_of('/')))
	{
		Assimp::Importer importer;

		const aiScene* scene = importer.ReadFile(filePath,
												 aiProcess_CalcTangentSpace |
												 aiProcess_Triangulate |
												 aiProcess_JoinIdenticalVertices |
												 aiProcess_SortByPType |
												 aiProcess_FlipUVs |
												 aiProcess_CalcTangentSpace);
		if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			std::cout << importer.GetErrorString() << '\n';
			return;
		}

		processNode(scene, scene->mRootNode);
	}

	void Mesh::render(const Shader& shader)
	{
		for(auto& subMesh : this->subMeshes)
		{
			subMesh.render(shader);
		}
	}

	void Mesh::processNode(const aiScene* scene, const aiNode* node)
	{
		for(unsigned i = 0; i < node->mNumMeshes; ++i)
		{
			const auto mesh = scene->mMeshes[node->mMeshes[i]];
			this->subMeshes.push_back(this->processSubMesh(mesh, scene));
		}

		for(unsigned i = 0; i < node->mNumChildren; ++i)
		{
			processNode(scene, node->mChildren[i]);
		}
	}

	SubMesh Mesh::processSubMesh(const aiMesh* mesh, const aiScene* scene)
	{
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
		std::vector<Texture*> textures;

		for(unsigned i = 0; i < mesh->mNumVertices; ++i)
		{
			vec3 position = { mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z };
			vec3 normal = { mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z };
			vec2 textureCoordinates = mesh->mTextureCoords[0]
				? vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y)
				: vec2(0.0f, 0.0f);

			vec3 tangent{}, bitangent{};
			if(mesh->HasTangentsAndBitangents())
			{
				tangent = { mesh->mTangents[i].x, mesh->mTangents[i].y , mesh->mTangents[i].z };
				bitangent = {mesh->mBitangents[i].x, mesh->mBitangents[i].y , mesh->mBitangents[i].z};
			}

			vertices.emplace_back(position, textureCoordinates, normal, tangent, bitangent);
		}
		
		for(unsigned i = 0; i < mesh->mNumFaces; ++i)
		{
			aiFace face = mesh->mFaces[i];
			for(unsigned j = 0; j < face.mNumIndices; ++j)
			{
				indices.push_back(face.mIndices[j]);
			}
		}

		//process material
		if(mesh->mMaterialIndex >= 0)
		{
			aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

			std::vector<Texture*> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, TextureType::Diffuse);
			textures.insert(textures.end(), std::make_move_iterator(diffuseMaps.begin()), std::make_move_iterator(diffuseMaps.end()));

			std::vector<Texture*> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, TextureType::Specular);
			textures.insert(textures.end(), std::make_move_iterator(specularMaps.begin()), std::make_move_iterator(specularMaps.end()));

			std::vector<Texture*> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, TextureType::Normal);
			textures.insert(textures.end(), std::make_move_iterator(normalMaps.begin()), std::make_move_iterator(normalMaps.end()));
		}

		return { vertices, indices, textures };
	}

	std::vector<Texture*> Mesh::loadMaterialTextures(const aiMaterial* material, aiTextureType assimpTextureType, TextureType type)
	{
		std::vector<Texture*> textures;

		for(unsigned i = 0; i < material->GetTextureCount(assimpTextureType);++i)
		{
			aiString str;
			material->GetTexture(assimpTextureType, i, &str);
			textures.push_back(ResourceManager::getInstance().getTexture(this->directory + "/" + str.C_Str(), type));
		}

		return textures;
	}
}
