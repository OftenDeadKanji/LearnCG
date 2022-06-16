#pragma once
#include <vector>
#include "glad/glad.h"
#include "../Rendering/Vertex/vertex.h"
#include "../Rendering/Texture/texture.h"
#include "../Rendering/Shader/shader.h"

namespace RedWood
{
	class SubMesh
	{
	public:
		SubMesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture*> textures);
		SubMesh(const SubMesh&) = delete;
		SubMesh(SubMesh&&) noexcept;
		~SubMesh();

		SubMesh& operator=(const SubMesh&) = delete;
		SubMesh& operator=(SubMesh&&) noexcept;

		void render(const Shader& shader);
	private:
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
		std::vector<Texture*> textures;

		GLuint vao {}, vbo {}, ebo{};
	};
}