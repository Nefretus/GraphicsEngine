#include"CompiledHeader.h"
#include "VertexBuffer.h"
#include"ErrorCheckMacro.h"

namespace Engine {
	/*Constructor for static buffer*/
	VertexBuffer::VertexBuffer(const void* data, GLuint size) {
		GLCall(glGenBuffers(1, &bufferID));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, bufferID));
		GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
	}

	/*Constructor for dynamic buffer*/
	VertexBuffer::VertexBuffer(GLuint size) {
		GLCall(glGenBuffers(1, &bufferID));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, bufferID));
		GLCall(glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW));
	}

	void VertexBuffer::loadData(const void* data, GLuint size) const {
		bind();
		GLCall(glBufferSubData(GL_ARRAY_BUFFER, 0, size, data));
	}

	void VertexBuffer::bind() const {
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, bufferID));
	}

	void VertexBuffer::unbind() const {
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	}

	void VertexBuffer::setLayout(const BufferLayout& _layout) {
		if (layout == nullptr)
			layout = std::make_unique<BufferLayout>(_layout);
		else
			*layout = _layout;
	}

	VertexBuffer::~VertexBuffer() {
		glDeleteBuffers(1, &bufferID);
	}
}
