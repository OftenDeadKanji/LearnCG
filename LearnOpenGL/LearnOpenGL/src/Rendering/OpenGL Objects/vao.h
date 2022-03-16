#ifndef VAO_H
#define VAO_H
#include "glad/glad.h"

namespace RedWood
{
	struct VAO
	{
		VAO();
		VAO(const VAO&) = delete;
		VAO(VAO&& other) noexcept;
		~VAO();

		VAO& operator=(const VAO&) = delete;
		VAO& operator=(VAO&& other) noexcept;

		GLuint id = 0;
	};
}

#endif // VAO_H