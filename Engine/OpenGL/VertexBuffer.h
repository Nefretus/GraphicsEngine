#pragma once
#include<glad/glad.h>
#include<memory>
#include"BufferLayout.h"

namespace Engine {
	class VertexBuffer {
	public:
		VertexBuffer(const void* data, GLuint size);
		VertexBuffer(GLuint size);
		void loadData(const void* data, GLuint size) const;
		~VertexBuffer();
		void bind() const;
		void unbind() const;
		void setLayout(const BufferLayout& _layout);
		const BufferLayout& getLayout() const { return *layout; }
	private:
		GLuint bufferID;
		std::unique_ptr<BufferLayout> layout{ nullptr };
	};
}
