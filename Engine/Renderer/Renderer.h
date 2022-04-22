#pragma once
#include<glad/glad.h>
#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"
#include<glm/gtc/type_ptr.hpp>
#include <memory>
#include"Core/DllMacro.h"

namespace Engine {
	class VertexArray;
	class Shader;
	class Camera;
	class Renderer {
	public:
		static void init(const std::shared_ptr<Camera>& _camera);
		static void onDestroy();

		static void beginBatch();
		static void endBatch();

		static void draw();
		static void clear();

		static void generateQuad(const glm::vec2& position, const glm::vec2& size, GLfloat texIndex, bool reverseTexture = false);
		static void generateQuad(const glm::mat4& transform, GLfloat texIndex);
		static void generateRotatedQuad(const glm::vec2& position, const glm::vec2& size, GLfloat texIndex, GLfloat rotation);
	private:
		static GLuint* generateIndicies(GLint numberOfRectangles, GLint indexCount);
	};

}
