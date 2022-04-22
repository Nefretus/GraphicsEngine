#pragma once
#include<string>
#include<glad/glad.h>

namespace Engine {
	class Texture2D {
	public:
		Texture2D(const std::string& _name);
		~Texture2D();
		void bind(GLuint slot = 0) const;
		int getHeight() const { return height; }
		int getWidth() const { return width; }
		std::string getName() const { return name; }

		static std::string getTexturesDirectory() { return std::string(_SOLUTIONDIR + std::string(R"(Resources\textures\)")); }
	private:
		int height, width, nrChannels;
		std::string filePath, name;
		GLuint ID;
	};
}
