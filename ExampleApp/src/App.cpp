#include"App.h"
#include"Game.h"

Engine::Application* Engine::CreateApplication() {
	return new ExampleApp();
}

ExampleApp::ExampleApp() : deltaTime(0.0f), lastFrame(0.0f) {
	instance = this;
	const Engine::WindowProperties properties{ 800, 600, "siema" };
	window = std::make_unique<Engine::Window>(properties);
	window->setCallbackFunction([this](Engine::BaseEvent& event) {
		OnEvent(event);
	});
	dispatcher->subscribe<Engine::MousePressedEvent>(std::bind(&ExampleApp::OnMousePressedEvent, this, std::placeholders::_1)); 
	game = new Game();
}

void ExampleApp::OnUpdate() {
	float currentFrame = (float)glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
	game->OnUpdate(deltaTime);
}

void ExampleApp::OnMousePressedEvent(Engine::BaseEvent& event) {
	switch (game->gameState) {
	case GameState::GAME_OVER: {
		game->Reset();
		game->gameState = GameState::GAME_MENU;
		break;
	}
	case GameState::GAME_MENU: {
		game->gameState = GameState::GAME_ACTIVE;
		game->GetMap().SpawnPipes();
		game->GetMap().GetPlayer().OnEvent(event);
		break;
	}
	case GameState::GAME_ACTIVE: {
		game->GetMap().GetPlayer().OnEvent(event);
		break;
	}
	default:
		return;
	}
}
