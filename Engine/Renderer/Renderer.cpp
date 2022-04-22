#include"CompiledHeader.h"
#include "Renderer.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Texture.h"
#include "Shader.h"
#include "TextureMenager.h"
#include "Camera.h"


namespace Engine {
	struct Vertex {
		glm::vec2 position;
		glm::vec2 texCoords;
		float texIndex;
	};

	struct RendererData {
		static const GLint maxNumberOfQuads = 5000;
		static const GLint indiciesPerRectangle = 6;
		static const GLint vertexPerRectangle = 4;
		static const GLint maxIndexCount = maxNumberOfQuads * indiciesPerRectangle;
		static const GLint maxTextureSlots = 8;

		Vertex* mainBuffer = nullptr;
		Vertex* ptrToBuffer = nullptr;

		std::unique_ptr<VertexArray> VAO;
		std::shared_ptr<VertexBuffer> VBO;
		std::shared_ptr<IndexBuffer> indexBuffer;
		std::unique_ptr<Shader> shader;
		std::shared_ptr<Camera> camera;

		GLint countIndex = 0;
		GLint countDrawCalls = 0;
	};

	static RendererData data;

	void Renderer::init(const std::shared_ptr<Camera>& _camera) {
		data.VAO = std::make_unique<VertexArray>();
		data.mainBuffer = new Vertex[data.vertexPerRectangle * data.maxNumberOfQuads];

		BufferLayout layout{
			  { "position", 2 },
			  { "texCoords", 2 },
			  { "texIndex", 1 }
		};

		data.VBO = std::make_shared<VertexBuffer>(sizeof(Vertex) * data.maxNumberOfQuads * 4);
		data.VBO->setLayout(layout);

		GLuint* indicies = generateIndicies(data.maxNumberOfQuads, data.maxIndexCount);
		data.indexBuffer = std::make_shared<IndexBuffer>(indicies, data.maxIndexCount);
		delete[] indicies;

		data.VAO->addVertexBuffer(data.VBO);
		data.VAO->addIndexBuffer(data.indexBuffer);

		data.shader = std::make_unique<Shader>();
		data.shader->bind();

		data.camera = _camera;

		TextureMenager::loadTextures(*data.shader, { "pipe", "background", "bird", "menu", "gameover"});
	}

	void Renderer::onDestroy() {
		delete[] data.mainBuffer;
	}

	void Renderer::beginBatch() {
		data.ptrToBuffer = data.mainBuffer;
		data.countIndex = 0;
	}

	void Renderer::endBatch() {
		GLint size = (GLint*)data.ptrToBuffer - (GLint*)data.mainBuffer;
		data.VAO->getVBO()->loadData(data.mainBuffer, data.vertexPerRectangle * size);
		data.shader->bind();
		const auto& textures = TextureMenager::getTextures();
		for (size_t i = 0; i < textures.size(); i++) {
			textures[i].second->bind(textures[i].first);
		}
		draw();
	}

	void Renderer::draw() {
		GLint count = (data.countIndex == 0) ? data.VAO->getIndexBuffer()->getHowManyIndicies() : data.countIndex;
		data.shader->bind();
		data.shader->setUniformMat4("viewProjection", data.camera->getViewProjectionMatrix());
		data.VAO->bind();
		GLCall(glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, NULL));
	}

	void Renderer::clear() {
		GLCall(glClearColor(0.9f, 0.6f, 0.2f, 1.0f));
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void Renderer::generateQuad(const glm::vec2& position, const glm::vec2& size, GLfloat texIndex, bool reverseTexture) {
		if (data.countIndex >= data.maxIndexCount) {
			endBatch();
			beginBatch();
		}

		std::vector<glm::vec2> texCoords = { {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f} };
		if(reverseTexture)
			texCoords = { {0.0f, 1.0f}, {1.0f, 1.0f}, {1.0f, 0.0f}, {0.0f, 0.0f} };
		
		data.ptrToBuffer->position = { position.x, position.y };
		data.ptrToBuffer->texCoords = texCoords[0];
		data.ptrToBuffer->texIndex = texIndex;
		data.ptrToBuffer++;

		data.ptrToBuffer->position = { position.x + size.x, position.y };
		data.ptrToBuffer->texCoords = texCoords[1];
		data.ptrToBuffer->texIndex = texIndex;
		data.ptrToBuffer++;

		data.ptrToBuffer->position = { position.x + size.x, position.y + size.y };
		data.ptrToBuffer->texCoords = texCoords[2];
		data.ptrToBuffer->texIndex = texIndex;
		data.ptrToBuffer++;

		data.ptrToBuffer->position = { position.x, position.y + size.y };
		data.ptrToBuffer->texCoords = texCoords[3];
		data.ptrToBuffer->texIndex = texIndex;
		data.ptrToBuffer++;

		data.countIndex += data.indiciesPerRectangle;
	}

	void Renderer::generateQuad(const glm::mat4& transform, GLfloat textureIndex) {
		if (data.countIndex >= data.maxIndexCount) {
			endBatch();
			beginBatch();
		}
		const glm::vec2 textureCoords[data.vertexPerRectangle] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };
		glm::vec4 quadVertexPostions[4];
		quadVertexPostions[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
		quadVertexPostions[1] = { 0.5f,  -0.5f, 0.0f, 1.0f };
		quadVertexPostions[2] = { 0.5f,   0.5f, 0.0f, 1.0f };
		quadVertexPostions[3] = { -0.5f,  0.5f, 0.0f, 1.0f };
		for (size_t i = 0; i < data.vertexPerRectangle; i++) {
			data.ptrToBuffer->position = transform * quadVertexPostions[i];
			data.ptrToBuffer->texCoords = textureCoords[i];
			data.ptrToBuffer->texIndex = textureIndex;
			data.ptrToBuffer++;
		}

		data.countIndex += data.indiciesPerRectangle;
	}

	void Renderer::generateRotatedQuad(const glm::vec2& position, const glm::vec2& size, GLfloat texIndex, GLfloat rotation) {
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(position, 0.0f))
			* glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		generateQuad(transform, texIndex);
	}

	GLuint* Renderer::generateIndicies(GLint numberOfRectangles, GLint indexCount) {
		GLuint* indicies = new GLuint[indexCount];
		int offset = 0;
		for (int i = 0; i < indexCount - 6; i += 6) {
			indicies[i + 0] = offset + 0;
			indicies[i + 1] = offset + 1;
			indicies[i + 2] = offset + 2;

			indicies[i + 3] = offset + 2;
			indicies[i + 4] = offset + 3;
			indicies[i + 5] = offset + 0;
			offset += 4;
		}
		return indicies;
	}

}

