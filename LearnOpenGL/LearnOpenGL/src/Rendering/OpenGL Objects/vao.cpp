#include "pch.h"
#include "vao.h"

namespace RedWood
{
	VAO::VAO()
	{
		glGenVertexArrays(1, &id);
	}

	VAO::VAO(VAO&& other) noexcept
	{
		const auto tmp = id;
		id = other.id;
		other.id = tmp;
	}

	VAO::~VAO()
	{
		if(id != 0)
		{
			glDeleteVertexArrays(1, &id);
		}
	}

	VAO& VAO::operator=(VAO&& other) noexcept
	{
		if(this != &other)
		{
			const auto tmp = id;
			id = other.id;
			other.id = tmp;
		}

		return *this;
	}
}
