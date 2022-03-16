#include "pch.h"
#include "renderer.h"

namespace RedWood
{
	void Renderer::bindVertexBuffer(const VBO& vbo)
	{
		glBindBuffer(GL_ARRAY_BUFFER, vbo.id);
	}

	void Renderer::unbindVertexBuffer()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Renderer::bufferVertexBufferData(const void* vertices, GLsizeiptr size, GLenum usage)
	{
		glBufferData(GL_ARRAY_BUFFER, size, vertices, usage);
	}

	void Renderer::bufferVertexBufferSubData(const void* vertices, GLsizeiptr size)
	{
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, vertices);
	}

	void Renderer::setAttributesPointer(GLuint index, GLint size, GLenum type, GLsizei stride, const void* offset)
	{
		glVertexAttribPointer(index, size, type, GL_FALSE, stride, offset);
		glEnableVertexAttribArray(index);
	}

	void Renderer::bindElementBuffer(const EBO& ebo)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo.id);
	}

	void Renderer::unbindElementBuffer()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void Renderer::bufferElementData(GLuint indices[], GLsizei size, GLenum usage)
	{
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, usage);
	}

	void Renderer::drawElements(GLenum mode, int size, GLenum type, const void* offset)
	{
		glDrawElements(mode, size, type, offset);
	}

	void Renderer::bindVertexArray(const VAO& vao)
	{
		glBindVertexArray(vao.id);
	}

	void Renderer::unbindVertexArray()
	{
		glBindVertexArray(0);
	}

	void Renderer::drawArrays(int count, int first, GLenum mode)
	{
		glDrawArrays(mode, first, count);
	}

	void Renderer::useShader(const Shader& shader)
	{
		glUseProgram(shader.getShaderID());
	}
}
