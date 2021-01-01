#pragma once

#include "Core/Gameplay/Component/Component.h"
#include <Box2D/Box2D.h>

namespace Engine
{
    class GameObject;
    enum class CollisionType { NONE, Player, Enemy, Pickup, Platform, FlyingFist, Grape, ClimbablePlatform, Water, Wall };

    class BoxCollider2D : public Component
    {
        RTTR_ENABLE(Component, Inspectable);

    public:
        BoxCollider2D();
        virtual ~BoxCollider2D();

        virtual void Init(GameObject* a_GameObject);
        virtual void Update(float a_DeltaTime) override;
        virtual void FixedUpdate(float a_TimeStep) override;
        void Inspect() override;

        void SetLinearVelocity(float a_X, float a_Y);
        void SetPosition(float a_X, float a_Y);
        void PrepareJump();
        void Jump();
        b2Vec2 GetPosition();
        void SetYVelocity(float a_Y);
        bool JumpCheck();
        void KnockBack(float a_Impulse);
        void EnemyJump();
        void DisableGravity();
        b2Vec2 GetVelocity();
        CollisionType GetCollisionType();
        void SetCollisionType(CollisionType a_CollisionType);
        CollisionType RTTRGetCollisionType();
        void RTTRSetCollisionType(CollisionType a_CollisionType);

    private:
        b2Body* m_Body;
        float m_Scale = 1.f;
        CollisionType m_CollisionType;
    };
}