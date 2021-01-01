#pragma once
#include "Core/Gameplay/Component/Component.h"
#include "Core/Gameplay/Component/BoxCollider2D.h"
namespace Engine
{
    class GameObject;
    enum class CollisionTypes;
    enum class PickupTypes {ScoreUp, LifeUp, BigPower, GoldenFist, SpeedFist, FinishLevel};
}
class PickupComponent : public Engine::Component
{
public:
    PickupComponent();
    virtual void Init(Engine::GameObject* a_GameObject);
    virtual ~PickupComponent();
    virtual void Update(float a_DeltaTime) override;
    virtual void OnCollide(bool a_IsLeft, Engine::BoxCollider2D* a_ThisComponent, Engine::BoxCollider2D* a_OtherComponent) override;
    void PickedUp();
    Engine::PickupTypes GetPickupType();
    void SetPickupType(Engine::PickupTypes a_PickupType);
    RTTR_ENABLE(Component);
private:
    Engine::PickupTypes m_PickupType;
    bool m_IsInteractedWith = false;
};
