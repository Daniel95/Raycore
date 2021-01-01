#include "EnemyController.h"
#include "Core/System/Scene/Scene.h"
#include "Core/Gameplay/Component/SpriteRenderer.h"
#include "Core/Gameplay/Component/BoxCollider2D.h"

EnemyController::EnemyController()
{
    m_EnemyType = EnemyType::AttackingEnemy;
}

EnemyController::~EnemyController()
{
}

void EnemyController::Init(Engine::GameObject* a_GameObject)
{
    Component::Init(a_GameObject);
}

void EnemyController::Update(float a_DeltaTime)
{
    m_ActionTimer += a_DeltaTime;

    switch (m_EnemyType)
    {
    case EnemyType::PatrolEnemy:
        PatrolEnemyAction(a_DeltaTime);
        break;
    case EnemyType::JumpEnemy:
        JumpEnemyAction();
        break;
    case EnemyType::AwareEnemy:
        AwareEnemyAction(a_DeltaTime);
        break;
    case EnemyType::FlyingEnemy:
        FlyEnemyAction(a_DeltaTime);
        break;
    case EnemyType::AttackingEnemy:
        AttackingEnemyAction(a_DeltaTime);
        break;
    case EnemyType::ShootingEnemy:
        ShootingEnemyAction();
        break;
    case EnemyType::HammerEnemy:
        HammerEnemyAction(a_DeltaTime);
        break;
    default:
        break;
    }

    a_DeltaTime;
}

void EnemyController::PatrolEnemyAction(const float& a_DeltaTime)
{
    Engine::BoxCollider2D* boxColliderComponent = GetGameObject()->GetComponent<Engine::BoxCollider2D>();
    RayCastDown(boxColliderComponent);
    if (m_IsLeft)
    {
		GetGameObject()->GetTransform()->SetScale(DXS::Vector2(-1.f, 1.f));
        boxColliderComponent->SetLinearVelocity(-m_Speed * a_DeltaTime, 0.f);
    }
    else
    {
		GetGameObject()->GetTransform()->SetScale(DXS::Vector2(1.f, 1.f));
        boxColliderComponent->SetLinearVelocity(m_Speed * a_DeltaTime, 0.f);
    }
}

void EnemyController::AwareEnemyAction(const float& a_DeltaTime)
{
    if (m_ActionTimer > 3.f)
    {
        if (m_ActionTimer > 4.5f)
        {
            m_ActionTimer = 0.f;
        }
    }
    else
    {
        Engine::BoxCollider2D* boxColliderComponent = GetGameObject()->GetComponent<Engine::BoxCollider2D>();
        RayCastDown(boxColliderComponent);
        if (m_IsLeft)
        {
			GetGameObject()->GetTransform()->SetScale(DXS::Vector2(-1.f, 1.f));
            boxColliderComponent->SetLinearVelocity(-m_Speed * a_DeltaTime, 0.f);
        }
        else
        {
			GetGameObject()->GetTransform()->SetScale(DXS::Vector2(1.f, 1.f));
            boxColliderComponent->SetLinearVelocity(m_Speed * a_DeltaTime, 0.f);
        }
    }
}

void EnemyController::AttackingEnemyAction(const float& a_DeltaTime)
{
    bool hit = false;
    Engine::BoxCollider2D* BoxColliderComponent = GetGameObject()->GetComponent<Engine::BoxCollider2D>();
    b2RayCastInput Linput;
    if (m_IsLeft)
    {
		GetGameObject()->GetTransform()->SetScale(DXS::Vector2(-1.f, 1.f));
        Linput.p1 = BoxColliderComponent->GetPosition() - b2Vec2(1.f, 0.f);
        Linput.p2 = Linput.p1 - b2Vec2(5.f, 0.f);
    }
    else
    {
		GetGameObject()->GetTransform()->SetScale(DXS::Vector2(1.f, 1.f));
        Linput.p1 = BoxColliderComponent->GetPosition() + b2Vec2(1.f, 0.f);
        Linput.p2 = Linput.p1 + b2Vec2(5.f, 0.f);
    }
    Linput.maxFraction = 1.f;

    float LclosestFraction = 1; //start with end of line as p2
    b2Vec2 LintersectionNormal(0, 0);
    for (b2Body* b = GetGameObject()->GetScene()->GetWorld()->GetBodyList(); b; b = b->GetNext()) {
        for (b2Fixture* f = b->GetFixtureList(); f; f = f->GetNext()) {

            b2RayCastOutput output;
            if (!f->RayCast(&output, Linput, 0))
                continue;
            if (output.fraction < LclosestFraction) {
                if (b->GetType() == b2_dynamicBody)
                {
                    Engine::BoxCollider2D* BoxCollider = static_cast<Engine::BoxCollider2D*>(b->GetUserData());
                    if (BoxCollider->GetCollisionType() == Engine::CollisionType::Player)
                    {
                        hit = true;
                    }
                }
            }
        }
    }
    RayCastDown(BoxColliderComponent);
    if (hit)
    {
        //Run faster towards player trying to hit it
        if (m_IsLeft)
        {
            BoxColliderComponent->SetLinearVelocity(-m_Speed * 3.f * a_DeltaTime, 0.f);
        }
        else
        {
            BoxColliderComponent->SetLinearVelocity(m_Speed * 3.f * a_DeltaTime, 0.f);
        }
    }
    else
    {
        if (m_IsLeft)
        {
            BoxColliderComponent->SetLinearVelocity(-m_Speed * a_DeltaTime, 0.f);
        }
        else
        {
            BoxColliderComponent->SetLinearVelocity(m_Speed * a_DeltaTime, 0.f);
        }
    }

}

void EnemyController::JumpEnemyAction()
{
    if (m_ActionTimer >= 5.f)
    {
        m_ActionTimer = 0.f;
        Engine::BoxCollider2D* boxColliderComponent = GetGameObject()->GetComponent<Engine::BoxCollider2D>();
        boxColliderComponent->EnemyJump();
    }
}

void EnemyController::FlyEnemyAction(const float& a_DeltaTime)
{
    Engine::BoxCollider2D* boxColliderComponent = GetGameObject()->GetComponent<Engine::BoxCollider2D>();
    boxColliderComponent->DisableGravity();
    boxColliderComponent->SetLinearVelocity(0.f, 1.f * a_DeltaTime);
}

void EnemyController::ShootingEnemyAction()
{   
    if (m_ActionTimer >= 5.f)
    {
        Engine::GameObject& gameObject6 = GetGameObject()->GetScene()->AddGameObject(DXS::Vector2(GetGameObject()->GetTransform()->GetPosition().x, GetGameObject()->GetTransform()->GetPosition().y), DXS::Vector2(-1, 1));
        gameObject6.AddComponent<EnemyController>();
        gameObject6.AddComponent<Engine::SpriteRenderer>().SetTexture(GAME_TEXTURES_PATH + "Bullet.png");
        gameObject6.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Enemy);
        gameObject6.GetComponent<EnemyController>()->m_EnemyType = EnemyType::HammerEnemy;
        gameObject6.GetComponent<EnemyController>()->m_IsLeft = true;

        m_ActionTimer = 0;
    }
    
}

void EnemyController::HammerEnemyAction(const float& a_DeltaTime)
{
    Engine::BoxCollider2D* boxColliderComponent = GetGameObject()->GetComponent<Engine::BoxCollider2D>();
    boxColliderComponent->DisableGravity();
    if (m_IsLeft)
    {
		GetGameObject()->GetTransform()->SetScale(DXS::Vector2(-1.f, 1.f));
        boxColliderComponent->SetLinearVelocity(-3.f * a_DeltaTime, 0.f);
    }
    else
    {
		GetGameObject()->GetTransform()->SetScale(DXS::Vector2(1.f, 1.f));
        boxColliderComponent->SetLinearVelocity(3.f * a_DeltaTime, 0.f);
    }
    if (m_ActionTimer > 10.f)
    {
        GetGameObject()->Destroy();
    }
}

EnemyType EnemyController::getEnemyType()
{
    return m_EnemyType;
}

void EnemyController::SetEnemyType(EnemyType a_EnemyType)
{
    m_EnemyType = a_EnemyType;
}

bool EnemyController::RayCastDown(Engine::BoxCollider2D* a_Box)
{
    bool hit = false;
    Engine::BoxCollider2D* BoxColliderComponent = GetGameObject()->GetComponent<Engine::BoxCollider2D>();
    b2RayCastInput Linput;
    Linput.p1 = BoxColliderComponent->GetPosition() - b2Vec2(0.f, 0.f);
    Linput.p2 = Linput.p1 - b2Vec2(0, 1.1f);
    Linput.maxFraction = 1.f;

    float LclosestFraction = 1; //start with end of line as p2
    b2Vec2 LintersectionNormal(0, 0);
    for (b2Body* b = GetGameObject()->GetScene()->GetWorld()->GetBodyList(); b; b = b->GetNext()) {
        for (b2Fixture* f = b->GetFixtureList(); f; f = f->GetNext()) {

            b2RayCastOutput output;
            if (!f->RayCast(&output, Linput, 0))
                continue;
            if (output.fraction < LclosestFraction) {
                if (b->GetType() == b2_staticBody)
                {
                    hit = true;
                }
            }
        }
    }
    if (!hit)
    {
        if (m_IsLeft)
        {
            m_IsLeft = false;
        }
        else
        {
            m_IsLeft = true;
        }
    }
    return false;
}
RTTR_REGISTRATION
{
    rttr::registration::class_<EnemyController>("EnemyController")
        .constructor<>()
        (
            rttr::policy::ctor::as_raw_ptr
        ).property("EnemyType", &EnemyController::getEnemyType, &EnemyController::SetEnemyType);

    rttr::registration::enumeration<EnemyType>("EnemyType")
        (
            rttr::value("PatrolEnemy", EnemyType::PatrolEnemy),
            rttr::value("JumpEnemy", EnemyType::JumpEnemy),
            rttr::value("AwareEnemy", EnemyType::AwareEnemy),
            rttr::value("FlyingEnemy", EnemyType::FlyingEnemy),
            rttr::value("AttackingEnemy", EnemyType::AttackingEnemy),
            rttr::value("ShootingEnemy", EnemyType::ShootingEnemy),
            rttr::value("HammerEnemy", EnemyType::HammerEnemy)
        );
}