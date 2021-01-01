#include "PickupComponent.h"
#include "Core/Gameplay/Component/BoxCollider2D.h"
#include "Core/Gameplay/GameObject.h"
#include "Core/System/Scene/Scene.h"
#include "Core/System/SceneSystem.h"
#include "Core/System/Manager/SystemManager.h"
#include "Player.h"

PickupComponent::PickupComponent()
{
    m_PickupType = Engine::PickupTypes::LifeUp;
}
void PickupComponent::Init(Engine::GameObject* a_GameObject)
{
    Component::Init(a_GameObject);
}
PickupComponent::~PickupComponent()
{
}

void PickupComponent::Update(float a_DeltaTime)
{
    a_DeltaTime;
}

void PickupComponent::OnCollide(bool a_IsLeft, Engine::BoxCollider2D* a_ThisComponent, Engine::BoxCollider2D* a_OtherComponent)
{
    if (a_ThisComponent->GetCollisionType() == Engine::CollisionType::Pickup && a_OtherComponent->GetCollisionType() == Engine::CollisionType::Player)
    {
        Player* player = a_OtherComponent->GetGameObject()->GetComponent<Player>();
        switch (m_PickupType)
        {
        case Engine::PickupTypes::ScoreUp:
            if (!m_IsInteractedWith)
            {
                player->SetScore(player->GetScore() + 1);
                GetGameObject()->Destroy();
                m_IsInteractedWith = true;
            }
            break;
        case Engine::PickupTypes::LifeUp:
            player->SetLives(player->GetLives() + 1);
            GetGameObject()->Destroy();
            break;
        case Engine::PickupTypes::BigPower:
            player->SetHealth(5);
            GetGameObject()->Destroy();
            break;
        case Engine::PickupTypes::GoldenFist:
            player->SetFistType(fistType::GoldenFist);
            GetGameObject()->Destroy();
            break;
        case Engine::PickupTypes::SpeedFist:
            player->SetFistType(fistType::SpeedFist);
            GetGameObject()->Destroy();
            break;
        case Engine::PickupTypes::FinishLevel:
            if (GetGameObject()->GetScene()->GetName() == LEVEL_1_NAME)
            {
                GetGameObject()->GetSystemManager()->GetSystem<Engine::SceneSystem>().LoadScene(LEVEL_2_NAME);
            }
            else if (GetGameObject()->GetScene()->GetName() == LEVEL_2_NAME)
            {
                GetGameObject()->GetSystemManager()->GetSystem<Engine::SceneSystem>().LoadScene(LEVEL_3_NAME);
            }
            
            break;
        default:
            break;
        }
    }
    a_IsLeft;
}
void PickupComponent::PickedUp()
{
}
Engine::PickupTypes PickupComponent::GetPickupType()
{
    return m_PickupType;
}
void PickupComponent::SetPickupType(Engine::PickupTypes a_PickupType)
{
    m_PickupType = a_PickupType;

}
RTTR_REGISTRATION
{
    rttr::registration::class_<PickupComponent>("PickupComponent")
        .constructor<>()
        (
            rttr::policy::ctor::as_raw_ptr
        )
            .property("PickupTypes", &PickupComponent::GetPickupType, &PickupComponent::SetPickupType);

    rttr::registration::enumeration<Engine::PickupTypes>("PickupTypes")
        (
            rttr::value("ScoreUp", Engine::PickupTypes::ScoreUp),
            rttr::value("LifeUp", Engine::PickupTypes::LifeUp),
            rttr::value("BigPower", Engine::PickupTypes::BigPower),
            rttr::value("GoldenFist", Engine::PickupTypes::GoldenFist),
            rttr::value("SpeedFist", Engine::PickupTypes::SpeedFist),
            rttr::value("FinishLevel", Engine::PickupTypes::FinishLevel)
        );
}