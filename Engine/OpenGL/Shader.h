#pragma once
#include<string>
#include<glad/glad.h>
#include<unordered_map>

#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"
#include<glm/gtc/type_ptr.hpp>

namespace Engine {
	struct ShaderSource;
	class Shader {
	public:
		Shader(const std::string& filePath = getShadersDirectory());
		~Shader();
		static const char* getShadersDirectory();
		void bind() const;
		void unbind() const;
		GLint getUniformLocation(const std::string& name) const;

		void setUniformInt(const std::string& name, int v0);
		void setUniformIntArray(const std::string& name, GLuint count, GLint* values);
		void setUniformMat4(const std::string& name, const glm::mat4& matrix);
	private:
		GLuint compileShader(GLuint type, const std::string& source) const;
		ShaderSource loadShaders() const;
		void createShaderProgram(const std::string& fragmentShaderSource, const std::string& vertexShaderSource);

		std::string fileName;
		mutable std::unordered_map<std::string, int> locationCache;
		GLuint program;
	};
}
