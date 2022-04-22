#pragma once
#include<glad/glad.h>
#include <GLFW/glfw3.h>

namespace Engine {
	class Application {
	public:
		Application() {}
		virtual ~Application() {}
		void Run() {  }
	private:

	};
	Application* CreateApplication();
}