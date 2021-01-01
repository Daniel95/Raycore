#include "FlyingFistComponent.h"
#include "Core/System/Scene/Scene.h"
#include "EnemyController.h"
#include "Core/Gameplay/Component/Transform.h"

FlyingFistComponent::FlyingFistComponent()
{
}

FlyingFistComponent::~FlyingFistComponent()
{
}

void FlyingFistComponent::Init(Engine::GameObject* a_GameObject)
{
    Component::Init(a_GameObject);
}

void FlyingFistComponent::Update(float a_DeltaTime)
{
    a_DeltaTime;
    if (m_ChargeTime > 0.f)
    {
        m_ChargeTime += a_DeltaTime;
    }
    if (!m_FistIsIdle)
    {
        if (m_IsGoing)
        {
            if (m_IsLeft)
            {
				GetGameObject()->GetTransform()->SetScale(DXS::Vector2(-1.f, 1.f));
                GetGameObject()->GetComponent<Engine::BoxCollider2D>()->SetLinearVelocity(-10.f * a_DeltaTime, 0.f);
                if (GetGameObject()->GetTransform()->GetPosition().x < m_StartX - m_Distance)
                {
                    m_IsGoing = false;
                }
            }
            else
            {
				GetGameObject()->GetTransform()->SetScale(DXS::Vector2(1.f, 1.f));
                GetGameObject()->GetComponent<Engine::BoxCollider2D>()->SetLinearVelocity(10.f  * a_DeltaTime, 0.f);
                if (GetGameObject()->GetTransform()->GetPosition().x > m_StartX + m_Distance)
                {
                    m_IsGoing = false;
                }
            }
        }
        else
        {
            float xAdjustment = 0.f;
            float yAdjustment = 0.f;
            if (GetGameObject()->GetTransform()->GetPosition().x > m_Player->GetTransform()->GetPosition().x)
            {
                xAdjustment = -10.f;
            }
            if (GetGameObject()->GetTransform()->GetPosition().x < m_Player->GetTransform()->GetPosition().x)
            {
                xAdjustment = 10.f;
            }
            if (GetGameObject()->GetTransform()->GetPosition().y > m_Player->GetTransform()->GetPosition().y)
            {
                yAdjustment = -10.f;
            }
            if (GetGameObject()->GetTransform()->GetPosition().y < m_Player->GetTransform()->GetPosition().y)
            {
                yAdjustment = 10.f;
            }
            GetGameObject()->GetComponent<Engine::BoxCollider2D>()->SetLinearVelocity(xAdjustment * a_DeltaTime, yAdjustment * a_DeltaTime);
            if (GetGameObject()->GetTransform()->GetPosition().x + 1.f > m_Player->GetTransform()->GetPosition().x &&
                GetGameObject()->GetTransform()->GetPosition().x - 1.0f < m_Player->GetTransform()->GetPosition().x&&
                GetGameObject()->GetTransform()->GetPosition().y + 1.0f > m_Player->GetTransform()->GetPosition().y &&
                GetGameObject()->GetTransform()->GetPosition().y - 1.0f < m_Player->GetTransform()->GetPosition().y)
            {
                m_FistIsIdle = true;
            }
        }
    }
    else
    {
        GetGameObject()->GetComponent<Engine::BoxCollider2D>()->SetPosition(m_Player->GetTransform()->GetPosition().x, m_Player->GetTransform()->GetPosition().y);
    }
}

void FlyingFistComponent::StartChargeFist()
{
    m_ChargeTime += 0.01f;
}

void FlyingFistComponent::ThrowFist(float a_StartX, float a_StartY, bool a_IsLeft)
{
    if (m_FistIsIdle)
    {
        m_StartX = a_StartX;
        m_StartY = a_StartY;
        m_IsLeft = a_IsLeft;
        GetGameObject()->GetComponent<Engine::BoxCollider2D>()->SetPosition(a_StartX, a_StartY);
        m_FistIsIdle = false;
        m_Distance = m_ChargeTime * 10.f;
        if (m_Distance > 7.f)
        {
            m_Distance = 7.f;
        }
        m_IsGoing = true;
    }
    m_ChargeTime = 0.f;
}

void FlyingFistComponent::OnCollide(bool a_IsLeft, Engine::BoxCollider2D* a_ThisComponent, Engine::BoxCollider2D* a_OtherComponent)
{
    if (!m_FistIsIdle)
    {
        if (a_ThisComponent->GetCollisionType() == Engine::CollisionType::Enemy)
        {
            if (a_ThisComponent->GetGameObject()->GetComponent<EnemyController>()->getEnemyType() != EnemyType::HammerEnemy)
            {
                a_ThisComponent->GetGameObject()->Destroy();
                m_IsGoing = false;

            }
        }
        if (a_OtherComponent->GetCollisionType() == Engine::CollisionType::Enemy)
        {
            if (a_OtherComponent->GetGameObject()->GetComponent<EnemyController>()->getEnemyType() != EnemyType::HammerEnemy)
            {
                a_OtherComponent->GetGameObject()->Destroy();
                m_IsGoing = false;

            }
        }
        if (a_ThisComponent->GetCollisionType() == Engine::CollisionType::Platform || a_OtherComponent->GetCollisionType() == Engine::CollisionType::Platform)
        {
            m_IsGoing = false;
        }
    }
}

void FlyingFistComponent::SetPlayer(Engine::GameObject* a_Player)
{
    m_Player = a_Player;
}


RTTR_REGISTRATION
{
    rttr::registration::class_<FlyingFistComponent>("FlyingFistComponent")
        .constructor<>()
        (
            rttr::policy::ctor::as_raw_ptr
        );
}
