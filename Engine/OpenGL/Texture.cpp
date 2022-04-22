#include"CompiledHeader.h"
#include "Texture.h"
#include"stb/stb_image.h"
#include"ErrorCheckMacro.h"

namespace Engine {
	Texture2D::Texture2D(const std::string& textureName) : name(textureName), height(0), width(0), nrChannels(0), ID(0) {
		stbi_set_flip_vertically_on_load(true);
		filePath = Texture2D::getTexturesDirectory() + name + ".png";
		stbi_uc* data = stbi_load(filePath.c_str(), &width, &height, &nrChannels, 4);
		if (data) {
			glGenTextures(1, &ID);
			glBindTexture(GL_TEXTURE_2D, ID);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

			glGenerateMipmap(GL_TEXTURE_2D);
			GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data));
			stbi_image_free(data);
		}
		else {
			std::cout << "nie wczytano pliku\n";
			ASSERT(false);
		}
	}

	Texture2D::~Texture2D() {
		GLCall(glDeleteTextures(1, &ID));
	}

	void Texture2D::bind(GLuint slot) const {
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, ID);
	}
}
