#pragma once
#include<glad/glad.h>
#include<glm/glm.hpp>
#include<memory>
#include<vector>
#include"VertexBuffer.h"
#include"IndexBuffer.h"

/*Adding more than one buffer is no tested yet*/

namespace Engine {
	class VertexArray {
	public:
		VertexArray();
		~VertexArray();

		void bind() const;
		void unbind() const;

		void addVertexBuffer(const std::shared_ptr<VertexBuffer>& VBO);
		void addIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer);

		const std::shared_ptr<VertexBuffer>& getVBO() const { return vertexBuffer; }
		const std::shared_ptr<IndexBuffer>& getIndexBuffer() const { return indexBuffer; }
	private:
		std::shared_ptr<VertexBuffer> vertexBuffer;
		std::shared_ptr<IndexBuffer> indexBuffer;
		GLuint ID;
	};
}
