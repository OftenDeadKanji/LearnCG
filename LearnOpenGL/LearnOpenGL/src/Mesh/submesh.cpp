#include "pch.h"
#include "submesh.h"

namespace RedWood
{
	SubMesh::SubMesh(std::vector<Vertex> vertices, std::vector<unsigned> indices, std::vector<Texture*> textures)
		: vertices(std::move(vertices)), indices(std::move(indices)), textures(std::move(textures))
	{
		glGenVertexArrays(1, &this->vao);
		glGenBuffers(1, &this->vbo);
		glGenBuffers(1, &this->ebo);

		glBindVertexArray(this->vao);

		glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
		glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex), &this->vertices[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(unsigned int), &this->indices[0], GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, position)));
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, textureCoords)));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, normal)));
		glEnableVertexAttribArray(2);

		glBindVertexArray(0);
	}

	SubMesh::SubMesh(SubMesh&& other) noexcept
		: vertices(std::move(other.vertices)), indices(std::move(other.indices)), textures(std::move(other.textures))
	{
		this->vao = other.vao;
		other.vao = 0;

		this->vbo = other.vbo;
		other.vbo = 0;

		this->ebo = other.ebo;
		other.ebo = 0;
	}

	SubMesh::~SubMesh()
	{
		if (this->ebo)
		{
			glDeleteBuffers(1, &ebo);
		}
		if (this->vbo)
		{
			glDeleteBuffers(1, &vbo);
		}
		if (this->vao)
		{
			glDeleteVertexArrays(1, &vao);
		}
	}

	SubMesh& SubMesh::operator=(SubMesh&& other) noexcept
	{
		if (this != &other)
		{
			this->vertices = std::move(other.vertices);
			this->indices = std::move(other.indices);
			this->textures = std::move(other.textures);

			this->vao = other.vao;
			other.vao = 0;

			this->vbo = other.vbo;
			other.vbo = 0;

			this->ebo = other.ebo;
			other.ebo = 0;
		}

		return *this;
	}

	void SubMesh::render(const Shader& shader)
	{
		unsigned int diffuseNr = 1;
		unsigned int specularNr = 1;

		for(unsigned int i = 0; i < this->textures.size(); ++i)
		{
			glActiveTexture(GL_TEXTURE0 + i);

			TextureType type = this->textures[i]->type;

			std::string number;
			switch (type)
			{
			case TextureType::Diffuse:
				number = std::to_string(diffuseNr++);
				break;
			case TextureType::Specular:
				number = std::to_string(specularNr++);
				break;
			}

			shader.setInt("texture_" + TextureTypeToString(type) + number, i);
			this->textures[i]->bind();
		}

		glBindVertexArray(this->vao);
		glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
		//glBindVertexArray(0);
	}
}
