#include"CompiledHeader.h"
#include"Camera.h"

namespace Engine {
	Camera::Camera(float windowWidth, float windowHeight)
		: projectionMatrix(glm::ortho(0.0f, windowWidth, 0.0f, windowHeight, -1.0f, 1.0f)),
		viewMatrix(glm::mat4(1.0f)), position(glm::vec3(0.0f, 0.0f, 0.0f))
	{}

	void Camera::onUpdate() {
		viewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(position, 0.0f));
	}
}
