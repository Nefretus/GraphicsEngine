#pragma once
#include"GameMap.h"
#include"Engine.h"
#include<memory>

enum class GameState {
	GAME_ACTIVE,
	GAME_MENU,
	GAME_OVER
};

class Game {
public:
	Game();
	~Game() {}
	static GameState gameState;
	void OnUpdate(float timeStep);
	void Reset();
	GameMap& GetMap() const { return *map; }
private:
	std::unique_ptr<GameMap> map;
};
