#pragma once
#include "Core/Gameplay/Component/Component.h"
#include "Core/Gameplay/Component/BoxCollider2D.h"
#include "Core/Gameplay/GameObject.h"
namespace Engine
{
    class GameObject;
}

class FlyingFistComponent : public Engine::Component
{
public:
    FlyingFistComponent();
    virtual ~FlyingFistComponent();
    virtual void Init(Engine::GameObject* a_GameObject);
    virtual void Update(float a_DeltaTime) override;
    void StartChargeFist();
    void ThrowFist(float a_StartX, float a_StartY, bool a_IsLeft);
    virtual void OnCollide(bool a_IsLeft, Engine::BoxCollider2D* a_ThisComponent, Engine::BoxCollider2D* a_OtherComponent) override;
    void SetPlayer(Engine::GameObject* a_Player);
    RTTR_ENABLE(Component);

private:
    float m_ChargeTime = 0.f;
    bool m_FistIsIdle = true;
    float m_StartX = 0.f;
    float m_StartY = 0.f;
    bool m_IsLeft = false;
    bool m_IsGoing = true;
    float m_Distance = 0.f;
    Engine::GameObject* m_Player;

};