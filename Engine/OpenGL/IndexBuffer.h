#pragma once
#include<glad/glad.h>

namespace Engine {
	class IndexBuffer {
	public:
		IndexBuffer(const void* data, GLuint count);
		~IndexBuffer();
		void bind() const;
		void unbind() const;
		GLuint getHowManyIndicies() const { return numberOfIndicies; }
	private:
		GLuint bufferID;
		GLuint numberOfIndicies;
	};

}