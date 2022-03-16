#include "pch.h"
#include "ebo.h"

namespace RedWood
{
	EBO::EBO()
	{
		glGenBuffers(1, &id);
	}

	EBO::EBO(EBO&& other) noexcept
	{
		const auto tmp = id;
		id = other.id;
		other.id = tmp;
	}

	EBO::~EBO()
	{
		if(id != 0)
		{
			glDeleteBuffers(1, &id);
		}
	}

	EBO& EBO::operator=(EBO&& other) noexcept
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
