#include "Player.h"
#include "Core/Gameplay/GameObject.h"
#include "Core/Gameplay/Component/Transform.h"
#include "Core/System/Scene/Scene.h"
#include "Core/Application.h"
#include "Core/System/SceneSystem.h"
#include "Core/System/Manager/SystemManager.h"
#include "Core/System/InputSystem.h"
#include "Core/System/GameSystem.h"
#include "Core/System/ResourceSystem.h"
#include "Core/System/Resource/Texture.h"
#include "Components/FlyingFistComponent.h"
#include "Core/Gameplay/Component/BoxCollider2D.h"
#include "Core/Gameplay/Component/SpriteRenderer.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::Init(Engine::GameObject* a_GameObject)
{
    Component::Init(a_GameObject);
    m_Lives = GetGameObject()->GetSystemManager()->GetSystem<Engine::GameSystem>().GetLives();
    LOG_APP_INFO("Lives = {0}", m_Lives);
}

void Player::Update(float a_DeltaTime)
{
    if (m_FlyingFist == nullptr)
    {
        CreateFlyingFist();
    }
    a_DeltaTime;

    Engine::InputSystem* inputSystem = &GetGameObject()->GetSystemManager()->GetSystem<Engine::InputSystem>();

    if (m_InputEnabled)
    {
        if (!m_IsChargingFist)
        {
            if (inputSystem->GetKeyboardKey(KeyCode::Right))
            {
                GetGameObject()->GetTransform()->SetScale(DXS::Vector2(2.f, 2.f));
                Engine::BoxCollider2D* BoxColliderComponent = GetGameObject()->GetComponent<Engine::BoxCollider2D>();
                BoxColliderComponent->SetLinearVelocity(m_Speed * a_DeltaTime, 0.f);
                m_IsLeft = false;
            }

            if (inputSystem->GetKeyboardKey(KeyCode::Left))
            {
                GetGameObject()->GetTransform()->SetScale(DXS::Vector2(-2.f, 2.f));
                Engine::BoxCollider2D* BoxColliderComponent = GetGameObject()->GetComponent<Engine::BoxCollider2D>();
                BoxColliderComponent->SetLinearVelocity(-m_Speed * a_DeltaTime, 0.f);
                m_IsLeft = true;
            }

            if (inputSystem->GetKeyboardKey(KeyCode::Up))
            {
                Jump();
            }

            if (inputSystem->GetKeyboardKey(KeyCode::Down))
            {
                Grimace();
            }
        }
    }
    else
    {
        Engine::BoxCollider2D* BoxColliderComponent = GetGameObject()->GetComponent<Engine::BoxCollider2D>();
        if (BoxColliderComponent->GetVelocity().y <= 0.f)
        {
            b2RayCastInput Linput;
            Linput.p1 = BoxColliderComponent->GetPosition() - b2Vec2(1.f, 1.f);
            Linput.p2 = Linput.p1 - b2Vec2(0.f, .1f);
            Linput.maxFraction = 1.f;

            float LclosestFraction = 1; //start with end of line as p2
            b2Vec2 LintersectionNormal(0, 0);
            for (b2Body* b = GetGameObject()->GetScene()->GetWorld()->GetBodyList(); b; b = b->GetNext())
            {
                for (b2Fixture* f = b->GetFixtureList(); f; f = f->GetNext())
                {

                    b2RayCastOutput output;
                    if (!f->RayCast(&output, Linput, 0))
                        continue;
                    if (output.fraction < LclosestFraction)
                    {
                        m_InputEnabled = true;
                    }
                }
            }
            b2RayCastInput Rinput;
            Rinput.p1 = BoxColliderComponent->GetPosition() - b2Vec2(-1.f, 1.f);
            Rinput.p2 = Rinput.p1 - b2Vec2(0, .1f);
            Rinput.maxFraction = 1.f;

            float RclosestFraction = 1; //start with end of line as p2
            b2Vec2 RintersectionNormal(0, 0);
            for (b2Body* b = GetGameObject()->GetScene()->GetWorld()->GetBodyList(); b; b = b->GetNext())
            {
                for (b2Fixture* f = b->GetFixtureList(); f; f = f->GetNext())
                {

                    b2RayCastOutput output;
                    if (!f->RayCast(&output, Rinput, 0))
                        continue;
                    if (output.fraction < RclosestFraction)
                    {
                        m_InputEnabled = true;
                    }
                }
            }
        }
    }

    if (inputSystem->GetKeyboardKeyDown(KeyCode::X) || inputSystem->GetKeyboardKeyDown(KeyCode::Space))
    {
        m_FlyingFist->GetComponent<FlyingFistComponent>()->StartChargeFist();
        m_IsChargingFist = true;
    }

    if (inputSystem->GetKeyboardKeyUp(KeyCode::X) || inputSystem->GetKeyboardKeyUp(KeyCode::Space))
    {
        m_FlyingFist->GetComponent<FlyingFistComponent>()->ThrowFist(GetGameObject()->GetTransform()->GetPosition().x, GetGameObject()->GetTransform()->GetPosition().y, m_IsLeft);
        m_IsChargingFist = false;
    }
}

void Player::Inspect()
{

}

void Player::OnCollide(bool a_IsLeft, Engine::BoxCollider2D* a_ThisComponent, Engine::BoxCollider2D* a_OtherComponent)
{
    if (a_ThisComponent->GetCollisionType() == Engine::CollisionType::Player)
    {
        if (a_OtherComponent->GetCollisionType() == Engine::CollisionType::Enemy && m_InputEnabled)
        {
            Damage(a_IsLeft);
        }
        if (a_OtherComponent->GetCollisionType() == Engine::CollisionType::Pickup)
        {
        }
        if (a_OtherComponent->GetCollisionType() == Engine::CollisionType::Water)
        {
            if (m_Died == false)
            {
                Engine::BoxCollider2D* BoxColliderComponent = GetGameObject()->GetComponent<Engine::BoxCollider2D>();
                BoxColliderComponent->KnockBack(10.f);
                this->Die();
                m_Died = true;
            }
        }
    }
}

void Player::Grimace()
{
}

void Player::Jump()
{
    Engine::BoxCollider2D* BoxColliderComponent = GetGameObject()->GetComponent<Engine::BoxCollider2D>();
    if (m_IsJumping == false)
    {
        //   LOG_APP_INFO("Jump!");
        m_IsJumping = true;
        BoxColliderComponent->Jump();
    }
    else
    {
        //Left Ray
        b2RayCastInput Linput;
        Linput.p1 = BoxColliderComponent->GetPosition() - b2Vec2(1.f, 1.f);
        Linput.p2 = Linput.p1 - b2Vec2(0.f, .1f);
        Linput.maxFraction = 1.f;

        float LclosestFraction = 1; //start with end of line as p2
        b2Vec2 LintersectionNormal(0, 0);
        for (b2Body* b = GetGameObject()->GetScene()->GetWorld()->GetBodyList(); b; b = b->GetNext()) {
            for (b2Fixture* f = b->GetFixtureList(); f; f = f->GetNext()) {

                b2RayCastOutput output;
                if (!f->RayCast(&output, Linput, 0))
                    continue;
                if (output.fraction < LclosestFraction) {

                    if (BoxColliderComponent->JumpCheck())
                    {
                        Engine::BoxCollider2D* BoxCollider = static_cast<Engine::BoxCollider2D*>(b->GetUserData());
                        if (BoxCollider->GetCollisionType() == Engine::CollisionType::Platform)
                        {
                            m_IsJumping = false;
                            BoxColliderComponent->SetYVelocity(0.f);
                        }
                    }
                    //   LOG_APP_INFO("Casted!");
                    m_InputEnabled = true;
                }
            }
        }

        //Right Ray
        b2RayCastInput Rinput;
        Rinput.p1 = BoxColliderComponent->GetPosition() - b2Vec2(-1.f, 1.f);
        Rinput.p2 = Rinput.p1 - b2Vec2(0.f, .1f);
        Rinput.maxFraction = 1.f;

        float RclosestFraction = 1; //start with end of line as p2
        b2Vec2 RintersectionNormal(0, 0);
        for (b2Body* b = GetGameObject()->GetScene()->GetWorld()->GetBodyList(); b; b = b->GetNext()) {
            for (b2Fixture* f = b->GetFixtureList(); f; f = f->GetNext()) {

                b2RayCastOutput output;
                if (!f->RayCast(&output, Rinput, 0))
                    continue;
                if (output.fraction < RclosestFraction) {

                    if (BoxColliderComponent->JumpCheck())
                    {
                        Engine::BoxCollider2D* BoxCollider = static_cast<Engine::BoxCollider2D*>(b->GetUserData());
                        if (BoxCollider->GetCollisionType() == Engine::CollisionType::Platform)
                        {
                            m_IsJumping = false;
                            BoxColliderComponent->SetYVelocity(0.f);
                        }
                    }
                    //   LOG_APP_INFO("Casted!");
                    m_InputEnabled = true;
                }
            }
        }
    }
}

void Player::Damage(bool a_PlayerIsLeft)
{
    SetHealth(m_Health - 1);

    Engine::BoxCollider2D* BoxColliderComponent = GetGameObject()->GetComponent<Engine::BoxCollider2D>();
    if (a_PlayerIsLeft)
    {
        BoxColliderComponent->KnockBack(-10.f);
    }
    else
    {
        BoxColliderComponent->KnockBack(10.f);
    }
    m_InputEnabled = false;
}

void Player::Die()
{
    m_Lives -= 1;
    if (m_Lives <= 0)
    {
        GetGameObject()->GetSystemManager()->GetSystem<Engine::GameSystem>().SetLives(3);
        GetGameObject()->GetSystemManager()->GetSystem<Engine::SceneSystem>().LoadScene(LEVEL_1_NAME);
    }
    else
    {
        GetGameObject()->GetSystemManager()->GetSystem<Engine::GameSystem>().SetLives(m_Lives);
        GetGameObject()->GetSystemManager()->GetSystem<Engine::SceneSystem>().ReloadScene();
    }

}

int Player::GetScore()
{
    return m_Score;
}

void Player::SetScore(int a_Score)
{
    m_Score = a_Score;
}

int Player::GetLives()
{
    return m_Lives;
}

void Player::SetLives(int a_Lives)
{
    m_Lives = a_Lives;
}

int Player::GetHealth()
{
    return m_Health;
}

void Player::SetHealth(int a_Health)
{
    m_Health = a_Health;
    if (m_Health <= 0)
    {
        Die();
    }
}

fistType Player::getFistType()
{
    return m_FistType;
}

void Player::CreateFlyingFist()
{
    m_FlyingFist = &GetGameObject()->GetScene()->AddGameObject(DXS::Vector2(this->GetGameObject()->GetTransform()->GetPosition().x, this->GetGameObject()->GetTransform()->GetPosition().y), DXS::Vector2(1, 1));
    m_FlyingFist->AddComponent<FlyingFistComponent>();
    m_FlyingFist->AddComponent<Engine::SpriteRenderer>().SetTexture(GAME_TEXTURES_PATH + "RaymanFist.png");
	m_FlyingFist->GetComponent<Engine::SpriteRenderer>()->SetLayer(2);
    m_FlyingFist->AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::FlyingFist);
    m_FlyingFist->GetComponent<FlyingFistComponent>()->SetPlayer(this->GetGameObject());
}

void Player::SetFistType(fistType a_FistType)
{
    m_FistType = a_FistType;
}
RTTR_REGISTRATION
{
    rttr::registration::class_<Player>("Player")
        .constructor<>()
        (
            rttr::policy::ctor::as_raw_ptr
        );
}