#include "pch.h"
#include "vbo.h"

namespace RedWood
{
	VBO::VBO()
	{
		glGenBuffers(1, &id);
	}

	VBO::VBO(VBO&& other) noexcept
	{
		const auto tmp = id;
		id = other.id;
		other.id = tmp;
	}

	VBO::~VBO()
	{
		if(id != 0)
		{
			glDeleteBuffers(1, &id);
		}
	}

	VBO& VBO::operator=(VBO&& other) noexcept
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
