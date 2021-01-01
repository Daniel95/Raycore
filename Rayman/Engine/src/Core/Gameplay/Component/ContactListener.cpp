#include "RayCorePCH.h"

#include "ContactListener.h"
#include "Core/Gameplay/Component/BoxCollider2D.h"
#include "Core/Gameplay/GameObject.h"

namespace Engine
{
    ContactListener::ContactListener()
    {

    }

    ContactListener::~ContactListener()
    {
    }
    void ContactListener::BeginContact(b2Contact* contact)
    {
        contact;
    }
    void ContactListener::EndContact(b2Contact* contact)
    {
        contact->SetEnabled(true);
    }
    void ContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
    {
        b2Fixture* DynamicFixture = nullptr;
        b2Fixture* StaticFixture = nullptr;

        //Figure out if A or B is Dynamic body
        if (contact->GetFixtureA()->GetBody()->GetType() == b2_staticBody)
        {
            StaticFixture = contact->GetFixtureA();
        }
        if (contact->GetFixtureA()->GetBody()->GetType() == b2_dynamicBody)
        {
            DynamicFixture = contact->GetFixtureA();
        }
        if (contact->GetFixtureB()->GetBody()->GetType() == b2_staticBody)
        {
            StaticFixture = contact->GetFixtureB();
        }
        if (contact->GetFixtureB()->GetBody()->GetType() == b2_dynamicBody)
        {
            DynamicFixture = contact->GetFixtureB();
        }
        if (StaticFixture != nullptr)
        {
            //Not collide if the dynamic object is flying fist
            BoxCollider2D* dynamicObject = static_cast<BoxCollider2D*>(DynamicFixture->GetBody()->GetUserData());
            if (dynamicObject->GetCollisionType() == CollisionType::FlyingFist)
            {
                BoxCollider2D* staticObject = static_cast<BoxCollider2D*>(StaticFixture->GetBody()->GetUserData());
                std::vector<Component*> components = dynamicObject->GetGameObject()->GetComponents();
                for (Component* component : components)
                {
                    component->OnCollide(false, dynamicObject, staticObject);
                }
                contact->SetEnabled(false);
                return;
            }


            BoxCollider2D* staticObject = static_cast<BoxCollider2D*>(StaticFixture->GetBody()->GetUserData());
            if (staticObject->GetCollisionType() == CollisionType::Water)
            {
                std::vector<Component*> components = dynamicObject->GetGameObject()->GetComponents();
                for (Component* component : components)
                {
                    component->OnCollide(false, dynamicObject, staticObject);
                }
            }
            if (staticObject->GetCollisionType() == CollisionType::Wall)
            {
                return;
            }
            //Check if contact points are moving downwardint numPoints = contact->GetManifold()->pointCount;
            int numPoints = contact->GetManifold()->pointCount;
            b2WorldManifold worldManifold;
            contact->GetWorldManifold(&worldManifold);

            //check if contact points are moving downward
            if (numPoints > 0)
            {
                b2Vec2 pointVel = DynamicFixture->GetBody()->GetLinearVelocityFromWorldPoint(worldManifold.points[0]);
                if (pointVel.y > 0)
                {
                    contact->SetEnabled(false);
                    return;
                }
                else
                {
                    contact->SetEnabled(true);
                }
            }
        }
        //Interaction between dynamic objects
        else
        {
            bool playerIsLeft = false;
            StaticFixture = contact->GetFixtureA();
            BoxCollider2D* dynamicObject = static_cast<BoxCollider2D*>(DynamicFixture->GetBody()->GetUserData());
            BoxCollider2D* StaticObject = static_cast<BoxCollider2D*>(StaticFixture->GetBody()->GetUserData());
            if (dynamicObject->GetCollisionType() == CollisionType::Player)
            {
                if (DynamicFixture->GetBody()->GetPosition().x >= StaticFixture->GetBody()->GetPosition().x)
                {
                    playerIsLeft = false;
                }
                else
                {
                    playerIsLeft = true;
                }
            }
            else if (StaticObject->GetCollisionType() == CollisionType::Player)
            {
                if (StaticFixture->GetBody()->GetPosition().x >= DynamicFixture->GetBody()->GetPosition().x)
                {
                    playerIsLeft = false;
                }
                else
                {
                    playerIsLeft = true;
                }
            }
            if (dynamicObject->GetCollisionType() == CollisionType::FlyingFist || StaticObject->GetCollisionType() == CollisionType::FlyingFist)
            {
                if (dynamicObject->GetCollisionType() == CollisionType::Player || StaticObject->GetCollisionType() == CollisionType::Player)
                {
          //          LOG_APP_INFO("Tried to hit Player");
                    contact->SetEnabled(false);
             //       return;
                }
                if (dynamicObject->GetCollisionType() == CollisionType::Platform || StaticObject->GetCollisionType() == CollisionType::Platform)
                {
                    LOG_APP_INFO("Tried to hit Platform");
                    contact->SetEnabled(false);
                    return;
                }
                if (dynamicObject->GetCollisionType() == CollisionType::Enemy || StaticObject->GetCollisionType() == CollisionType::Enemy)
                {
                    LOG_APP_INFO("Tried to hit Enemy");
                    contact->SetEnabled(true);
                }
            }
            if (StaticObject->GetCollisionType() == CollisionType::Pickup || dynamicObject->GetCollisionType() == CollisionType::Pickup)
            {
                contact->SetEnabled(false);
            }
            std::vector<Component*> components = dynamicObject->GetGameObject()->GetComponents();
            for (Component* component : components)
            {
                component->OnCollide(playerIsLeft, dynamicObject, StaticObject);
            }
            components = StaticObject->GetGameObject()->GetComponents();
            for (Component* component : components)
            {
                component->OnCollide(playerIsLeft, StaticObject, dynamicObject);
            }
            if (StaticObject->GetCollisionType() == CollisionType::Enemy || dynamicObject->GetCollisionType() == CollisionType::Enemy)
            {
                contact->SetEnabled(false);
            }
        }
        oldManifold;
    }

    RTTR_REGISTRATION
    {
        rttr::registration::class_<Engine::ContactListener>("ContactListener")
            .constructor<>()
            (
                rttr::policy::ctor::as_raw_ptr
            );
    }
}