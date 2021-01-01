#pragma once
#include "Core/Gameplay/Component/Component.h"

#include "Core/System/EventSystem.h"

namespace Engine
{
    class GameObject;
    class BoxCollider2D;
    enum class CollisionTypes;
}
enum class fistType { Normal, GoldenFist, SpeedFist };
class Player : public Engine::Component
{
    RTTR_ENABLE(Engine::Component, Engine::Inspectable);

public:
    Player();
    virtual ~Player();

    virtual void Init(Engine::GameObject* a_GameObject) override;
    virtual void Update(float a_DeltaTime) override;
    virtual void OnCollide(bool a_IsLeft, Engine::BoxCollider2D* a_ThisComponent, Engine::BoxCollider2D* a_OtherComponent) override;
    void Grimace();
    void Jump();
    void Damage(bool a_PlayerIsLeft);
    void Die();
    int GetScore();
    void SetScore(int a_Score);
    int GetLives();
    void SetLives(int a_Lives);
    int GetHealth();
    void SetHealth(int a_Health);
    fistType getFistType();
    void CreateFlyingFist();
    void SetFistType(fistType a_FistType);
    void Inspect() override;

private:
    float m_Speed = 8.0f;
    bool m_IsJumping = false;
    bool m_InputEnabled = true;
    int m_Score = 0;
    int m_Lives = 3;
    int m_Health = 3;
    bool m_IsLeft = false;
    bool m_IsChargingFist = false;
    bool m_Died = false;
    fistType m_FistType;
    Engine::EventSystem::EventHandle m_KeyEventHandle;
    Engine::EventSystem::EventHandle m_KeyPressedHandle;
    Engine::EventSystem::EventHandle m_KeyReleasedHandle;
    Engine::GameObject* m_FlyingFist;

};