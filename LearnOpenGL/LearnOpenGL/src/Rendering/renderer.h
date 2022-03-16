#ifndef RENDERER_H
#define RENDERER_H
#include "OpenGL Objects/ebo.h"
#include "OpenGL Objects/vao.h"
#include "OpenGL Objects/vbo.h"
#include "Shader/shader.h"

namespace RedWood
{
	class Renderer
	{
	public:
		static void bindVertexBuffer(const VBO& vbo);
		static void unbindVertexBuffer();
		static void bufferVertexBufferData(const void* vertices, GLsizeiptr size, GLenum usage = GL_STATIC_DRAW);
		static void bufferVertexBufferSubData(const void* vertices, GLsizeiptr size);
		static void setAttributesPointer(GLuint index, GLint size, GLenum type, GLsizei stride, const void* offset);

		static void bindElementBuffer(const EBO& ebo);
		static void unbindElementBuffer();
		static void bufferElementData(GLuint indices[], GLsizei size, GLenum usage = GL_STATIC_DRAW);
		static void drawElements(GLenum mode, int size, GLenum type, const void* offset = nullptr);

		static void bindVertexArray(const VAO& vao);
		static void unbindVertexArray();
		static void drawArrays(int count, int first = 0, GLenum mode = GL_TRIANGLES);

		static void useShader(const Shader& shader);
	};
}

#endif // RENDERER_H