#pragma once
#include"Player.h"
#include<vector>

class GameMap {
public:
	GameMap();
	~GameMap() {}

	void OnUpdate(float timeStep);
	void OnRenderer();
	void Reset();
	bool GameIsOver() const { return gameOver; }
	const Player& GetPlayer() const { return player; }
	void SpawnPipes();
private:
	bool CheckCollision();
	void CreatePipes(float xPosition);
	bool gameOver = false;
	Player player;
	std::vector<GameObject> pipes;
};
