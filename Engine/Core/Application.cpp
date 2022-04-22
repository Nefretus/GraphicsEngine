#include"CompiledHeader.h"
#include "Application.h"
#include"Window.h"
#include"Events/KeyEvent.h"
#include"Events/MouseEvent.h"
#include"Events/WindowsEvent.h"
#include"Input.h"
#include"KeyCodes.h"	
#include"Renderer/Renderer.h"
#include"Renderer/Camera.h"
#include"Renderer/TextureMenager.h"

namespace Engine {
	Application* Application::instance = nullptr;

	Application::Application() : running(true) { 
		camera = std::make_shared<Engine::Camera>();
		dispatcher = std::make_unique<Engine::EventDispatcher>();
		dispatcher->subscribe<Engine::WindowClosedEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));
		dispatcher->subscribe<Engine::WindowResizedEvent>(std::bind(&Application::OnWindowResize, this, std::placeholders::_1));
	}

	Application::~Application() {
		for (auto& element : TextureMenager::textures) {
			delete element.second;
		}
	}

	void Application::OnEvent(BaseEvent& event) {
		switch (event.GetEventType()) {
		case eventType::WINDOW_CLOSED:
			dispatcher->dispatch<WindowClosedEvent>(event);
			break;
		case eventType::WINDOW_RESIZED:
			dispatcher->dispatch<WindowResizedEvent>(event);
			break;
		case eventType::MOUSE_PRESSED:
			dispatcher->dispatch<MousePressedEvent>(event);
			break;
		default:
			return;
		}
	}

	void Application::OnWindowClose(BaseEvent& event) {
		running = false;
	}

	void Application::OnWindowResize(BaseEvent& event) {
		auto& e = static_cast<WindowResizedEvent&>(event);
		camera->UpdateScreenSize(window->getWidth(), window->getHeight());
		glViewport(0, 0, e.GetWidth(), e.GetHeight());
	}

	void Application::Run() {
		while (running) {
			OnUpdate();
			window->onUpdate();
		}
	}
}
