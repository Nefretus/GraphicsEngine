#include "Player.h"
#include"Game.h"

void Player::OnUpdate(float deltaTime, bool gravityIsActive) {
	if (gravityIsActive) velocity.y -= gravity;
	if (Game::gameState == GameState::GAME_OVER) {
		velocity.x = 0.0f;
		position.y += velocity.y * 10.0f;
	}
	else {
		position += (glm::ivec2) (velocity * 0.025f);
	}
}

void Player::OnEvent(Engine::BaseEvent& event) const {
	auto& e = static_cast<Engine::MousePressedEvent&>(event);
	if(e.getButton() == MOUSE_BUTTON_1)
		velocity.y = 200.0f;
}

void Player::OnRenderer() {
	Engine::Renderer::generateRotatedQuad({ position.x, position.y }, {size.x + 10.0f, size.y + 10.0f}, Engine::TextureMenager::findTextureSlot("bird"), GetRotation());
}
