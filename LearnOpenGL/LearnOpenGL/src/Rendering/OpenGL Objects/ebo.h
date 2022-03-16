#ifndef EBO_H
#define EBO_H

namespace RedWood
{
	struct EBO
	{
		EBO();
		EBO(const EBO&) = delete;
		EBO(EBO&& other) noexcept;
		~EBO();

		EBO& operator=(const EBO&) = delete;
		EBO& operator=(EBO&& other) noexcept;

		GLuint id = 0;
	};
}

#endif // EBO_H