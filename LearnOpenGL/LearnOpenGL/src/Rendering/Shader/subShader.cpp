#include "subShader.h"
#include <fstream>
#include <iostream>

namespace RedWood
{
	SubShader::SubShader(Type type)
		: type(type)
	{
		switch (this->type)
		{
		case Type::Vertex:
			this->subShaderID = glCreateShader(GL_VERTEX_SHADER);
			break;
		case Type::Fragment:
			this->subShaderID = glCreateShader(GL_FRAGMENT_SHADER);
			break;
		}
	}

	SubShader::SubShader(SubShader&& other) noexcept
		: type(other.type)
	{
		const auto tmp = this->subShaderID;
		this->subShaderID = other.subShaderID;
		other.subShaderID = tmp;
	}

	SubShader::~SubShader()
	{
		if(this->subShaderID)
		{
			glDeleteShader(this->subShaderID);
		}
	}

	SubShader& SubShader::operator=(SubShader&& other) noexcept
	{
		if(this != &other)
		{
			this->type = other.type;

			const auto tmp = this->subShaderID;
			this->subShaderID = other.subShaderID;
			other.subShaderID = tmp;
		}

		return *this;
	}

	SubShader SubShader::createShaderFromSourceCode(const std::string& sourceCode, Type type)
	{
		SubShader subShader { type };
		subShader.setSourceCode(sourceCode);
		subShader.compile();

		return subShader;
	}

	SubShader SubShader::createShaderFromFile(const std::string& filePath, Type type)
	{
		SubShader subShader { type };
		const auto sourceCode = SubShader::loadShaderSourceCodeFromFile(filePath);
		subShader.setSourceCode(sourceCode);
		subShader.compile();

		return subShader;
	}

	GLuint SubShader::getSubShaderID() const
	{
		return this->subShaderID;
	}

	SubShader::Type SubShader::getType() const
	{
		return this->type;
	}

	std::string SubShader::loadShaderSourceCodeFromFile(const std::string& filePath)
	{
		std::ifstream file(filePath);
		if(file.is_open())
		{
			file.seekg(0, std::ios::end);

			const size_t size = file.tellg();
			std::string buffer(size, ' ');

			file.seekg(0);
			file.read(&buffer[0], size);

			file.close();
			return buffer;
		}

		return "";
	}

	void SubShader::setSourceCode(const std::string& sourceCode)
	{
		const char* code = sourceCode.c_str();
		glShaderSource(this->subShaderID, 1, &code, nullptr);
	}

	void SubShader::compile()
	{
		glCompileShader(this->subShaderID);

		int success;
		glGetShaderiv(this->subShaderID, GL_COMPILE_STATUS, &success);

		if(!success)
		{
			char infoLog[1024];
			glGetShaderInfoLog(this->subShaderID, 1024, nullptr, infoLog);
			std::cout << infoLog << std::endl;
		}
	}
}
