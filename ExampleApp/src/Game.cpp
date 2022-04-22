#include "Game.h"
#include"Engine.h"

GameState Game::gameState = GameState::GAME_MENU;

Game::Game() {
	map = std::make_unique<GameMap>();
	Engine::Window& window = Engine::Application::Get().GetWindow();
	auto& camera = Engine::Application::Get().GetCamera();
	camera->UpdateScreenSize(window.getWidth(), window.getHeight());
	Engine::Renderer::init(Engine::Application::Get().GetCamera());
}

void Game::OnUpdate(float timeStep) {
	const auto& playerPos = map->GetPlayer().GetPos();
	if (map->GameIsOver()) gameState = GameState::GAME_OVER;
	map->OnUpdate(timeStep);
	Engine::Application::Get().GetCamera()->setPosition({ -playerPos.x + Engine::Application::Get().GetWindow().getWidth() / 2, 0.0f });
	Engine::Renderer::clear();
	Engine::Renderer::beginBatch();
	map->OnRenderer();
	Engine::Renderer::endBatch();
}

void Game::Reset() {
	map->Reset();
}
