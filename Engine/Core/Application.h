#pragma once
#include"DllMacro.h"
#include"Events/Event.h"
#include<memory>

namespace Engine {
	class Window;
	class Camera;
	class Application {
	public:
		Application();
		virtual ~Application();
		void Run();
		static Application& Get() { return *instance; }
		Window& GetWindow() { return *window.get(); };
		void OnEvent(BaseEvent& event);
		void OnWindowClose(BaseEvent& event);
		void OnWindowResize(BaseEvent& event);
		std::shared_ptr<Camera>& GetCamera() { return camera; }
	protected:
		virtual void OnUpdate() {}
		std::unique_ptr<Window> window;
		std::shared_ptr<Camera> camera;
		std::unique_ptr<EventDispatcher> dispatcher;
		static Application* instance;
	private:
		bool running;
	};
	Application* CreateApplication();
}


