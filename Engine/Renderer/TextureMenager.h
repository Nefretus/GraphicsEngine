#pragma once
#include<glad/glad.h>
#include <string>
#include <vector>
#include <memory>
#include"Core/DllMacro.h"

namespace Engine {
	class Shader;
	class Texture2D;
	class TextureMenager {
	public:
		static void loadTextures(Shader& shader, const std::initializer_list<std::string>& _textureNames);
		static GLfloat findTextureSlot(const std::string& textureName);
		static const auto& getTextures() { return textures; }
		static std::vector<std::pair<int, Texture2D*>> textures;
	};
}
