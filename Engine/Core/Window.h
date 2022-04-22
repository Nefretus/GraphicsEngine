#pragma once
#include"Events/Event.h"
#include<functional>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

namespace Engine {
	struct WindowInitError {};

	struct WindowProperties {
		GLuint width, height;
		std::string title;
		std::function<void(Engine::BaseEvent& event)> eventCallbackFuntion;
	};

	class Window {
	public:
		Window(const WindowProperties& _properties);
		~Window();
		void onUpdate();
		static std::unique_ptr<Window> create(const WindowProperties& _properties);
		GLuint getWidth() const { return properties.width; }
		GLuint getHeight() const { return properties.height; }
		GLFWwindow& getGLFWwindow() { return *window; }
		void TurnOnBlending();
		void setCallbackFunction(std::function<void(Engine::BaseEvent&)> _callBackFunction) { properties.eventCallbackFuntion = _callBackFunction; }
	private:
		void setGLFWCallbacks();
		void setHints();
		WindowProperties properties;
		GLFWwindow* window;
	};
}