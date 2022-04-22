#include"CompiledHeader.h"
#include "IndexBuffer.h"
#include"ErrorCheckMacro.h"

namespace Engine {
	IndexBuffer::IndexBuffer(const void* data, GLuint count)
		: numberOfIndicies(count) {
		GLCall(glGenBuffers(1, &bufferID));
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferID));
		GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data, GL_STATIC_DRAW));
	}

	void IndexBuffer::bind() const {
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferID));
	}

	void IndexBuffer::unbind() const {
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	}

	IndexBuffer::~IndexBuffer() {
		glDeleteBuffers(1, &bufferID);
	}
}
