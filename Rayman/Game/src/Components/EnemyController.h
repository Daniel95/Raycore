#pragma once
#include "Core/Gameplay/Component/Component.h"
#include "Core/Gameplay/Component/BoxCollider2D.h"
#include "Core/Gameplay/GameObject.h"
namespace Engine
{
    class GameObject;
}
enum class EnemyType { PatrolEnemy, JumpEnemy, AwareEnemy, FlyingEnemy, AttackingEnemy, ShootingEnemy, HammerEnemy };
class EnemyController : public Engine::Component
{
public:
    EnemyController();
    virtual ~EnemyController();
    virtual void Init(Engine::GameObject* a_GameObject);
    virtual void Update(float a_DeltaTime) override;
    bool RayCastDown(Engine::BoxCollider2D* a_Box);
    void PatrolEnemyAction(const float& a_DeltaTime);
    void AwareEnemyAction(const float& a_DeltaTime);
    void AttackingEnemyAction(const float& a_DeltaTime);
    void JumpEnemyAction();
    void FlyEnemyAction(const float& a_DeltaTime);
    void ShootingEnemyAction();
    void HammerEnemyAction(const float& a_DeltaTime);
    EnemyType getEnemyType();
    void SetEnemyType(EnemyType a_EnemyType);
    RTTR_ENABLE(Component);

private:
    float m_Speed = 2.0f;
    float m_ActionTimer = 0.f;
    bool m_IsLeft = false;
    EnemyType m_EnemyType;
};
