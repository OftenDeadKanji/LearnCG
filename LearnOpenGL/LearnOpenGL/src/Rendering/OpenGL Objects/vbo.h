#ifndef VBO_H
#define VBO_H

namespace RedWood
{
	struct VBO
	{
		VBO();
		VBO(const VBO&) = delete;
		VBO(VBO&& other) noexcept;
		~VBO();

		VBO& operator=(const VBO&) = delete;
		VBO& operator=(VBO&& other) noexcept;

		GLuint id = 0;
	};
}

#endif // VBO_H