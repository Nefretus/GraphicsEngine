#include "GameMap.h"
#include"Engine.h"
#include"Game.h"

const int pipeCount = 100;

GameMap::GameMap() { player.SetPos({ 0.0f, Engine::Application::Get().GetWindow().getHeight() / 2 }); }

void GameMap::CreatePipes(float xPosition) {
    float playerPos = player.GetPos().x;
    const auto& window = Engine::Application::Get().GetWindow();
    const GLuint height = window.getWidth();
    const GLuint width = window.getWidth();
    float gapYSize = 0.25f * height;
    float gapXSize = 50.0f;
    float gapYPos = (float)(rand() % (int)(height - 2.9 * gapYSize) + (gapYSize - height/9));
    glm::vec2 lowerPipePos{xPosition, 0.0f};
    glm::vec2 lowerPipeSize{ gapXSize, gapYPos };
    glm::vec2 upperPipePos{ xPosition, gapYPos + gapYSize};
    glm::vec2 upperPipeSize{ gapXSize, height -  (gapYPos + gapYSize)};
    pipes.push_back(GameObject(lowerPipePos, lowerPipeSize));
    pipes.push_back(GameObject(upperPipePos, upperPipeSize));
}

void GameMap::OnUpdate(float timeStep) {
    switch (Game::gameState) {
    case GameState::GAME_ACTIVE: {
        if (CheckCollision())
            gameOver = true;
        player.OnUpdate(timeStep);
             break;
        }
    case GameState::GAME_MENU: {
        player.OnUpdate(timeStep, false);
        break;
    }
    default:
        break;
    }
}

bool GameMap::CheckCollision() {
    const auto& window = Engine::Application::Get().GetWindow();
    const GLuint height = window.getWidth();
    const GLuint width = window.getWidth();
    if (player.GetPos().y <= 0.0f) return true;
    for (size_t i = 0; i < pipes.size(); i++) {
        if (pipes[i].GetPos().x > (player.GetPos().x + width))
            continue;
        else if (pipes[i].GetPos().x < (player.GetPos().x - width))
            continue; 
        else {
            bool xAxisOverlap = (player.GetPos().x + player.GetSize().x >= pipes[i].GetPos().x + 15.0f)
                && (pipes[i].GetPos().x + 15.0f + pipes[i].GetSize().x >= player.GetPos().x);
            bool yAxisOverlap = player.GetPos().y + player.GetSize().y >= pipes[i].GetPos().y + 15.0f
                && ((pipes[i].GetPos().y + 15.0f + pipes[i].GetSize().y) >= player.GetPos().y);
            if (xAxisOverlap && yAxisOverlap)
                return true;
            else
                continue;
        }
    }
    return false;
}

void GameMap::OnRenderer() {
    float posistion = -1000.0f;
    bool reverseTexture = true;
    GLfloat texIndex = Engine::TextureMenager::findTextureSlot("background");
    const int height = Engine::Application::Get().GetWindow().getHeight();
    const int width = Engine::Application::Get().GetWindow().getWidth();
    for(int i = (int)posistion; i < posistion + 10000.0f; i += 200)
        Engine::Renderer::generateQuad({ (float)i, 0.0f }, { 200.0f , height }, texIndex);
    if (!pipes.empty()) {
        texIndex = Engine::TextureMenager::findTextureSlot("pipe");
        for (size_t i = 0; i < pipeCount; i++) {
            if (i % 2 == 0)
                Engine::Renderer::generateQuad({ pipes[i].GetPos().x, pipes[i].GetPos().y }, { pipes[i].GetSize().x, pipes[i].GetSize().y }, texIndex);
            else
                Engine::Renderer::generateQuad({ pipes[i].GetPos().x, pipes[i].GetPos().y }, { pipes[i].GetSize().x, pipes[i].GetSize().y }, texIndex, reverseTexture);
        }
    }
    const float messageSizeX = 300.0f, messageSizeY = 300.0f;
    if (Game::gameState == GameState::GAME_MENU)
        Engine::Renderer::generateQuad({ player.GetPos().x - messageSizeX / 2, height / 2 - 100.0f}, { messageSizeX, messageSizeY }, Engine::TextureMenager::findTextureSlot("menu"));
    else if (Game::gameState == GameState::GAME_OVER)
        Engine::Renderer::generateQuad({ player.GetPos().x - messageSizeX / 2, height / 2 + messageSizeY/4 }, { messageSizeX, messageSizeY/2 }, Engine::TextureMenager::findTextureSlot("gameover"));
    player.OnRenderer();
}

void GameMap::SpawnPipes() {
    float curentPos = player.GetPos().x + 500.0f;
    for (int i = 0; i < pipeCount / 2; i++) {
        CreatePipes(curentPos);
        curentPos += 0.25f * 800.0f;
    }
}

void GameMap::Reset() {
    gameOver = false;
    player = Player();
    player.SetPos({ 0.0f, Engine::Application::Get().GetWindow().getHeight() / 2 });
    pipes.clear();
}
