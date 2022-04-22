#include"CompiledHeader.h"
#include"Input.h"
#include"Window.h"
#include"Application.h"

namespace Engine {
	Input* Input::instance = nullptr;

	Input* Input::GetInstance() {
		if (instance == nullptr)
			instance = new Input();
		return instance;
	}

	bool Input::IsKeyPressedImpl(int keycode) {
		GLFWwindow& window = Application::Get().GetWindow().getGLFWwindow();
		int state = glfwGetKey(&window, keycode);
		if (state == GLFW_PRESS || state == GLFW_REPEAT) return true;
		return false;
	}

	float Input::GetMousePosXImpl() {
		GLFWwindow& window = Application::Get().GetWindow().getGLFWwindow();
		double posX, posY;
		glfwGetCursorPos(&window, &posX, &posY);
		return (float)posX;
	 }
	
	float Input::GetMousePosYImpl() {
		GLFWwindow& window = Application::Get().GetWindow().getGLFWwindow();
		double posX, posY;
		glfwGetCursorPos(&window, &posX, &posY);
		return (float)posY;
	 }

	bool Input::IsMousePressedImpl(int button) {
		GLFWwindow& window = Application::Get().GetWindow().getGLFWwindow();
		int state = glfwGetMouseButton(&window, button);
		if (state == GLFW_PRESS) return true;
		return false;
	}
}