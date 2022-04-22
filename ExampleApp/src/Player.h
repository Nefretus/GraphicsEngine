#pragma once
#include"glad/glad.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include"Engine.h"

class GameObject {
public:
    GameObject(const glm::vec2& _pos, const glm::vec2& _size) : position(_pos), size(_size) {}
    GameObject() : position(0.0f, 0.0f), size(40.0f, 40.0f) {}

    glm::vec2 GetPos() const { return position; }
    glm::vec2 GetSize() const { return size; }
    void SetPos(const glm::vec2& _pos) { position.x = _pos.x; position.y = _pos.y; }
    void SetSize(const glm::vec2& _size) { size.x = _size.x; size.y = _size.y; }
protected:
    glm::vec2 position, size;
};

class Player : public GameObject {
public:
    Player() : GameObject(), velocity(125.0f, 0.0f) {}
    Player(const glm::vec2& _pos, const glm::vec2& _size, glm::vec2 _velocity = { 125.0f, 0.0f }) : GameObject(_pos, _size), velocity(_velocity) {}

    void SetVelocity(const glm::vec2& _vel) { velocity = _vel; }
    GLfloat GetRotation() { return glm::clamp((velocity.y / 10.0f), -20.0f, 8.0f); }
    void OnUpdate(float deltaTime, bool gravityIsActive = true);
    void OnRenderer();
    void OnEvent(Engine::BaseEvent& event) const;
private:
    mutable glm::vec2 velocity;
    float gravity = 10.0f;
};
