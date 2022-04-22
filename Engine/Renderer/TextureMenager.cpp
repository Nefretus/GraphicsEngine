#include"CompiledHeader.h"
#include "TextureMenager.h"
#include "Shader.h"
#include "Texture.h"
#include "ErrorCheckMacro.h"


namespace Engine {
	std::vector<std::pair<int, Texture2D*>> TextureMenager::textures;

	void TextureMenager::loadTextures(Shader& shader, const std::initializer_list<std::string>& textureNames) {
		GLint textureSlot = 0;
		for (const auto& textureName : textureNames) {
			textures.push_back(std::make_pair(textureSlot, new Texture2D(textureName)));
			textureSlot++;
		}
		GLint* samplers = new GLint[textures.size()];
		for (size_t i = 0; i < textures.size(); i++)
			samplers[i] = i;
		shader.bind();
		shader.setUniformIntArray("newTexture", textures.size(), samplers);
		delete[] samplers;
	}

	GLfloat TextureMenager::findTextureSlot(const std::string& textureName) {
		for (const auto& element : textures) {
			if (element.second->getName() == textureName) {
				return static_cast<float>(element.first);
			}
		}
		ASSERT(false);
		std::cout << "Texture could not be found!\n";
		return 0;
	}
}