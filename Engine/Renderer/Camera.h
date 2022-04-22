#pragma once
#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"
#include<glm/gtc/type_ptr.hpp>
#include"Core/DllMacro.h"

namespace Engine {
	class Camera {
	public:
		Camera(float windowWidth = 800.0f, float windowHeight = 400.0f);
		const glm::mat4 getViewProjectionMatrix() const { return projectionMatrix * viewMatrix; };
		void setPosition(const glm::vec2& _pos) { position = _pos; onUpdate(); }
		void UpdateScreenSize(float width, float height) { projectionMatrix = glm::ortho(0.0f, width, 0.0f, height, -1.0f, 1.0f); }
	private:
		void onUpdate();

		glm::mat4 viewMatrix;
		glm::mat4 projectionMatrix;
		glm::vec2 position;
	};
}
