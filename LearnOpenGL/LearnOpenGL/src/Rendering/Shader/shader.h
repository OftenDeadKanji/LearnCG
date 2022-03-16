#pragma once
#include "subShader.h"

namespace RedWood
{
	class Shader
	{
	public:
		Shader();
		Shader(const Shader&) = delete;
		Shader(Shader&&) noexcept;
		~Shader();

		Shader& operator=(const Shader&) = delete;
		Shader& operator=(Shader&&) noexcept;

		void attachSubShader(const SubShader& shader);
		bool tryToLinkShader();

		void setInt(const std::string& name, int value) const;
		void setFloat(const std::string& name, float value) const;
		void setVec2f(const std::string& name, const glm::vec2& vector) const;
		void setVec3f(const std::string& name, const glm::vec3& vector) const;
		void setVec4f(const std::string& name, const glm::vec4& vector) const;
		void setMat4(const std::string& name, const glm::mat4& matrix) const;

		GLuint getShaderID() const;
	private:
		GLint getUniformLocation(const std::string& name) const;

		GLuint shaderID {};
		mutable std::unordered_map<std::string, GLint> uniformLocation;
	};
}
