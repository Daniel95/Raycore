#include "RayCorePCH.h"

#include "Core/Gameplay/Component/BoxCollider2D.h"
#include "Core/Utilities/Log.h"
#include "Core/Gameplay/GameObject.h"
#include "Core/Gameplay/Component/Transform.h"
#include "Core/System/Scene/Scene.h"

namespace Engine
{
    BoxCollider2D::BoxCollider2D()
    {
    }

    BoxCollider2D::~BoxCollider2D()
    {
        GetGameObject()->GetScene()->GetWorld()->DestroyBody(m_Body);
    }

    void BoxCollider2D::Init(GameObject* a_GameObject)
    {
        Component::Init(a_GameObject);

        if (m_CollisionType != CollisionType::NONE)
        {
            SetCollisionType(m_CollisionType);
        }
    }

    void BoxCollider2D::Update(float a_DeltaTime)
    {
        _ASSERT(m_CollisionType != CollisionType::NONE);

        GetGameObject()->GetTransform()->SetPosition(DXS::Vector2(m_Body->GetPosition().x / m_Scale, m_Body->GetPosition().y / m_Scale));
        if (m_CollisionType == CollisionType::Player)
        {
            m_Body->SetAwake(true);
            m_Body->SetTransform(m_Body->GetTransform().p + b2Vec2(0.f, .001f), m_Body->GetAngle());
        }
        if (m_CollisionType == CollisionType::FlyingFist)
        {
            m_Body->SetAwake(true);
        }
        a_DeltaTime;
    }

    void BoxCollider2D::FixedUpdate(float a_TimeStep)
    {

    }

    void BoxCollider2D::Inspect()
    {

    }

    void BoxCollider2D::SetLinearVelocity(float a_X, float a_Y)
    {
        m_Body->SetTransform(b2Vec2(m_Body->GetPosition().x + a_X, m_Body->GetPosition().y + a_Y), m_Body->GetAngle());
    }

    void BoxCollider2D::PrepareJump()
    {
        m_Body->SetTransform(m_Body->GetTransform().p + b2Vec2(0.f, 0.001f), m_Body->GetAngle());
    }

    void BoxCollider2D::Jump()
    {
        m_Body->SetLinearVelocity(b2Vec2(m_Body->GetLinearVelocity().x, 0.f));
        m_Body->ApplyLinearImpulseToCenter(b2Vec2(0.f, 25.f), false);
    }

    b2Vec2 BoxCollider2D::GetPosition()
    {
        return m_Body->GetPosition();
    }

    void BoxCollider2D::SetPosition(float a_X, float a_Y)
    {
        m_Body->SetTransform(b2Vec2(a_X, a_Y), m_Body->GetAngle());
    }
    void BoxCollider2D::SetYVelocity(float a_Y)
    {
        if (m_Body->GetLinearVelocity().x > .1f)
        {
            m_Body->SetLinearVelocity(b2Vec2(m_Body->GetLinearVelocity().x, a_Y));
        }
    }

    void BoxCollider2D::SetCollisionType(CollisionType a_CollisionType)
    {
        m_CollisionType = a_CollisionType;

        if (m_CollisionType == CollisionType::Player)
        {
            b2BodyDef bodyDef;
            bodyDef.type = b2_dynamicBody;
            bodyDef.fixedRotation = true;
            bodyDef.position.Set(GetGameObject()->GetTransform()->GetPosition().x * m_Scale, GetGameObject()->GetTransform()->GetPosition().y * m_Scale);
            m_Body = GetGameObject()->GetScene()->GetWorld()->CreateBody(&bodyDef);


            b2PolygonShape dynamicBox;
            dynamicBox.SetAsBox(GetGameObject()->GetTransform()->GetScale().x / 2.f * m_Scale, GetGameObject()->GetTransform()->GetScale().y / 2.f * m_Scale);
            b2FixtureDef fixtureDef;
            fixtureDef.shape = &dynamicBox;

            fixtureDef.density = 0.3f;
            fixtureDef.friction = 1.0f;
            fixtureDef.restitution = 0.f;
            m_Body->CreateFixture(&fixtureDef);
            m_Body->SetUserData(this);
        }
        //Platform

        else if (m_CollisionType == CollisionType::Platform)
        {
            b2BodyDef bodyDef;
            bodyDef.type = b2_staticBody;
            bodyDef.fixedRotation = true;
            bodyDef.position.Set(GetGameObject()->GetTransform()->GetPosition().x * m_Scale, GetGameObject()->GetTransform()->GetPosition().y * m_Scale);
            m_Body = GetGameObject()->GetScene()->GetWorld()->CreateBody(&bodyDef);

            b2PolygonShape dynamicBox;
            dynamicBox.SetAsBox(GetGameObject()->GetTransform()->GetScale().x / 2.f * m_Scale, GetGameObject()->GetTransform()->GetScale().y / 2.f * m_Scale);
            b2FixtureDef fixtureDef;
            fixtureDef.shape = &dynamicBox;

            fixtureDef.density = 1.f;
            fixtureDef.friction = 1.f;
            fixtureDef.restitution = 0.f;
            m_Body->CreateFixture(&fixtureDef);
            m_Body->SetUserData(this);
        }
        //Enemy
        else if (m_CollisionType == CollisionType::Enemy)
        {
            b2BodyDef bodyDef;
            bodyDef.type = b2_dynamicBody;
            bodyDef.fixedRotation = true;
            bodyDef.position.Set(GetGameObject()->GetTransform()->GetPosition().x * m_Scale, GetGameObject()->GetTransform()->GetPosition().y * m_Scale);
            m_Body = GetGameObject()->GetScene()->GetWorld()->CreateBody(&bodyDef);


            b2PolygonShape dynamicBox;
            dynamicBox.SetAsBox(GetGameObject()->GetTransform()->GetScale().x / 2.f * m_Scale, GetGameObject()->GetTransform()->GetScale().y / 2.f * m_Scale);
            b2FixtureDef fixtureDef;
            fixtureDef.shape = &dynamicBox;

            fixtureDef.density = 0.3f;
            fixtureDef.friction = 1.0f;
            fixtureDef.restitution = 0.f;
            m_Body->CreateFixture(&fixtureDef);
            m_Body->SetUserData(this);
            m_Body->SetGravityScale(0.4f);
        }
        //Pickup
        else if (m_CollisionType == CollisionType::Pickup)
        {
            b2BodyDef bodyDef;
            bodyDef.type = b2_dynamicBody;
            bodyDef.fixedRotation = true;
            bodyDef.position.Set(GetGameObject()->GetTransform()->GetPosition().x * m_Scale, GetGameObject()->GetTransform()->GetPosition().y * m_Scale);
            m_Body = GetGameObject()->GetScene()->GetWorld()->CreateBody(&bodyDef);


            b2PolygonShape dynamicBox;
            dynamicBox.SetAsBox(GetGameObject()->GetTransform()->GetScale().x / 2.f * m_Scale, GetGameObject()->GetTransform()->GetScale().y / 2.f * m_Scale);
            b2FixtureDef fixtureDef;
            fixtureDef.shape = &dynamicBox;

            fixtureDef.density = 0.f;
            fixtureDef.friction = 0.0f;
            fixtureDef.restitution = 0.f;
            m_Body->CreateFixture(&fixtureDef);
            m_Body->SetUserData(this);
            m_Body->SetGravityScale(0.f);
        }
        else if (m_CollisionType == CollisionType::FlyingFist)
        {
            b2BodyDef bodyDef;
            bodyDef.type = b2_dynamicBody;
            bodyDef.fixedRotation = true;
            bodyDef.position.Set(GetGameObject()->GetTransform()->GetPosition().x * m_Scale, GetGameObject()->GetTransform()->GetPosition().y * m_Scale);
            m_Body = GetGameObject()->GetScene()->GetWorld()->CreateBody(&bodyDef);

            b2PolygonShape dynamicBox;
            dynamicBox.SetAsBox(GetGameObject()->GetTransform()->GetScale().x / 2.f * m_Scale, GetGameObject()->GetTransform()->GetScale().y / 2.f * m_Scale);
            b2FixtureDef fixtureDef;
            fixtureDef.shape = &dynamicBox;

            fixtureDef.density = 1.f;
            fixtureDef.friction = 1.f;
            fixtureDef.restitution = 0.f;
            m_Body->CreateFixture(&fixtureDef);
            m_Body->SetUserData(this);
            m_Body->SetGravityScale(0.f);
        }
        else if (m_CollisionType == CollisionType::Water)
        {
        b2BodyDef bodyDef;
        bodyDef.type = b2_staticBody;
        bodyDef.fixedRotation = true;
        bodyDef.position.Set(GetGameObject()->GetTransform()->GetPosition().x* m_Scale, GetGameObject()->GetTransform()->GetPosition().y* m_Scale);
        m_Body = GetGameObject()->GetScene()->GetWorld()->CreateBody(&bodyDef);

        b2PolygonShape dynamicBox;
        dynamicBox.SetAsBox(GetGameObject()->GetTransform()->GetScale().x / 2.f * m_Scale, GetGameObject()->GetTransform()->GetScale().y / 2.f * m_Scale);
        b2FixtureDef fixtureDef;
        fixtureDef.shape = &dynamicBox;

        fixtureDef.density = 1.f;
        fixtureDef.friction = 1.f;
        fixtureDef.restitution = 0.f;
        m_Body->CreateFixture(&fixtureDef);
        m_Body->SetUserData(this);
        }
        else if (m_CollisionType == CollisionType::Wall)
        {
        b2BodyDef bodyDef;
        bodyDef.type = b2_staticBody;
        bodyDef.fixedRotation = true;
        bodyDef.position.Set(GetGameObject()->GetTransform()->GetPosition().x * m_Scale, GetGameObject()->GetTransform()->GetPosition().y * m_Scale);
        m_Body = GetGameObject()->GetScene()->GetWorld()->CreateBody(&bodyDef);

        b2PolygonShape dynamicBox;
        dynamicBox.SetAsBox(GetGameObject()->GetTransform()->GetScale().x / 2.f * m_Scale, GetGameObject()->GetTransform()->GetScale().y / 2.f * m_Scale);
        b2FixtureDef fixtureDef;
        fixtureDef.shape = &dynamicBox;

        fixtureDef.density = 1.f;
        fixtureDef.friction = 1.f;
        fixtureDef.restitution = 0.f;
        m_Body->CreateFixture(&fixtureDef);
        m_Body->SetUserData(this);
        }
    }

    CollisionType BoxCollider2D::RTTRGetCollisionType()
    {
        return m_CollisionType;
    }

    void BoxCollider2D::RTTRSetCollisionType(CollisionType a_CollisionType)
    {
        m_CollisionType = a_CollisionType;
    }

    bool BoxCollider2D::JumpCheck()
    {
        if (m_Body->GetLinearVelocity().y <= 0)
        {
            return true;
        }
        return false;
    }
    void BoxCollider2D::KnockBack(float a_Impulse)
    {
        m_Body->SetLinearVelocity(b2Vec2(0.f, 0.f));
        m_Body->ApplyLinearImpulseToCenter(b2Vec2(a_Impulse, 12.f), false);
    }

    void BoxCollider2D::EnemyJump()
    {
        m_Body->SetTransform(b2Vec2(m_Body->GetPosition().x, m_Body->GetPosition().y + 1.f), m_Body->GetAngle());
        m_Body->ApplyLinearImpulseToCenter(b2Vec2(0.f, 5.f), true);
    }
    void BoxCollider2D::DisableGravity()
    {
        m_Body->SetGravityScale(0.f);
    }
    b2Vec2 BoxCollider2D::GetVelocity()
    {
        return m_Body->GetLinearVelocity();
    }

    CollisionType BoxCollider2D::GetCollisionType()
    {
        return m_CollisionType;
    }

    RTTR_REGISTRATION
    {
        rttr::registration::class_<Engine::BoxCollider2D>("BoxCollider2D")
            .constructor<>()
            (
                rttr::policy::ctor::as_raw_ptr
            )
            .property("CollisionType", &Engine::BoxCollider2D::RTTRGetCollisionType, &Engine::BoxCollider2D::RTTRSetCollisionType);

    rttr::registration::enumeration<Engine::CollisionType>("CollisionType")
        (
            rttr::value("NONE", Engine::CollisionType::NONE),
            rttr::value("Player", Engine::CollisionType::Player),
            rttr::value("Enemy", Engine::CollisionType::Enemy),
            rttr::value("Pickup", Engine::CollisionType::Pickup),
            rttr::value("Platform", Engine::CollisionType::Platform),
            rttr::value("FlyingFist", Engine::CollisionType::FlyingFist),
            rttr::value("Grape", Engine::CollisionType::Grape),
            rttr::value("ClimbablePlatform", Engine::CollisionType::ClimbablePlatform),
            rttr::value("Water", Engine::CollisionType::Water),
            rttr::value("Wall", Engine::CollisionType::Wall)
        );

    }
}


