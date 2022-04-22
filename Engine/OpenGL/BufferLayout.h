#pragma once
#include<typeinfo>
#include<string>
#include<vector>
#include<iostream>
#include<glad/glad.h>
#include<glm/glm.hpp>
#include"ErrorCheckMacro.h"

namespace Engine {
	struct BufferLayoutElement {
		BufferLayoutElement(const std::string& _name, int _count, GLenum type = GL_FLOAT, GLboolean _normalized = GL_FALSE);

		int getSizeOfOpenGLType(GLenum type);

		std::string name;
		int size;
		int count;
		GLboolean normalized;
		GLuint offset;
		GLenum openGLType;
	};

	class BufferLayout {
	public:
		BufferLayout(const std::initializer_list<BufferLayoutElement>& newElements);

		const std::vector<BufferLayoutElement>& getElements() const { return elements; }
		GLuint getStride() const { return stride; }
	private:
		GLuint stride;
		std::vector<BufferLayoutElement> elements;
	};
}