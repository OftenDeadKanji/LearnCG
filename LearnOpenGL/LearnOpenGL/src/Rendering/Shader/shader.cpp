#include "shader.h"
#include <iostream>

#include "../Texture/texture.h"
#include "glm/gtc/type_ptr.hpp"

namespace RedWood
{
	Shader::Shader()
		: shaderID(glCreateProgram())
	{}

	Shader::Shader(Shader&& other) noexcept
		: uniformLocation(std::move(other.uniformLocation))
	{
		auto tmp = this->shaderID;
		this->shaderID = other.shaderID;
		other.shaderID = tmp;
	}

	Shader::~Shader()
	{
		if(shaderID)
		{
			glDeleteProgram(this->shaderID);
		}
	}

	Shader& Shader::operator=(Shader&& other) noexcept
	{
		if(this != &other)
		{
			auto tmp = this->shaderID;
			this->shaderID = other.shaderID;
			other.shaderID = tmp;

			this->uniformLocation = std::move(other.uniformLocation);
		}

		return *this;
	}

	void Shader::attachSubShader(const SubShader& shader)
	{
		glAttachShader(this->shaderID, shader.getSubShaderID());
	}

	bool Shader::tryToLinkShader()
	{
		glLinkProgram(this->shaderID);

		int success;
		glGetProgramiv(this->shaderID, GL_LINK_STATUS, &success);

		if(!success)
		{
			char infoLog[1024];
			glGetProgramInfoLog(this->shaderID, 512, nullptr, infoLog);
			std::cout << infoLog << std::endl;

			return false;
		}

		return true;
	}

	void Shader::setInt(const std::string& name, int value) const
	{
		const GLint location = this->getUniformLocation(name);
		glUniform1i(location, value);
	}

	void Shader::setFloat(const std::string& name, float value) const
	{
		const GLint location = this->getUniformLocation(name);
		glUniform1f(location, value);
	}

	void Shader::setBool(const std::string& name, bool value) const
	{
		const GLint location = this->getUniformLocation(name);
		glUniform1i(location, value);
	}

	void Shader::setVec2f(const std::string& name, const glm::vec2& vector) const
	{
		const GLint location = this->getUniformLocation(name);
		glUniform2f(location, vector.x, vector.y);
	}

	void Shader::setVec3f(const std::string& name, const glm::vec3& vector) const
	{
		const GLint location = this->getUniformLocation(name);
		glUniform3f(location, vector.x, vector.y, vector.z);
	}

	void Shader::setVec4f(const std::string& name, const glm::vec4& vector) const
	{
		const GLint location = this->getUniformLocation(name);
		glUniform4f(location, vector.x, vector.y, vector.z, vector.w);
	}

	void Shader::setMat4(const std::string& name, const glm::mat4& matrix) const
	{
		const GLint location = this->getUniformLocation(name);
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void Shader::setTexture(const std::string& name, const Texture& texture) const
	{
		const GLint location = this->getUniformLocation(name);
		glUniform1i(location, this->textureUnit);
		glActiveTexture(GL_TEXTURE0 + this->textureUnit);
		if(texture.type == TextureType::DepthCubeMap)
		{
			glBindTexture(GL_TEXTURE_CUBE_MAP, texture.id);
		}
		else
		{
			glBindTexture(GL_TEXTURE_2D, texture.id);
		}

		this->textureUnit++;
	}

	GLuint Shader::getShaderID() const
	{
		return this->shaderID;
	}

	void Shader::use() const
	{
		glUseProgram(this->shaderID);
	}

	void Shader::resetTextureUnits()
	{
		this->textureUnit = 0;
	}

	GLint Shader::getUniformLocation(const std::string& name) const
	{
		if(this->uniformLocation.contains(name))
		{
			return uniformLocation[name];
		}

		const GLint location = glGetUniformLocation(this->shaderID, name.c_str());
		uniformLocation.insert(std::make_pair(name, location));

		return location;
	}
}
