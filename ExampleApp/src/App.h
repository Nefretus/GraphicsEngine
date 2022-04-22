#pragma once
#include <Engine.h>
#include"Core/EntryPoint.h"
#include"Game.h"

class ExampleApp : public Engine::Application {
public:
	ExampleApp();
	~ExampleApp() override { delete game; }
private:
	void OnUpdate() override;
	void OnMousePressedEvent(Engine::BaseEvent& event);
	Game* game;
	float deltaTime, lastFrame;
};
