#pragma once
#include <string>
#include "glad/glad.h"

namespace RedWood
{
	class SubShader
	{
	public:
		enum class Type
		{
			Vertex,
			Geometry,
			Fragment
		};

	private:
		explicit SubShader(Type type);

	public:
		SubShader(const SubShader&) = delete;
		SubShader(SubShader&&) noexcept;
		~SubShader();

		SubShader& operator=(const SubShader&) = delete;
		SubShader& operator=(SubShader&&) noexcept;

		static SubShader createShaderFromSourceCode(const std::string& sourceCode, Type type);
		static SubShader createShaderFromFile(const std::string& filePath, Type type);

		GLuint getSubShaderID() const;
		Type getType() const;

	private:
		[[nodiscard("This function doesn't set the source code. Use returned string as parameter for setSourceCode method.")]] static std::string loadShaderSourceCodeFromFile(const std::string& filePath);

		void setSourceCode(const std::string& sourceCode);
		void compile();

		GLuint subShaderID {};
		Type type;
	};
}