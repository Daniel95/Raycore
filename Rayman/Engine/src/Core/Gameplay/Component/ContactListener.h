#pragma once
#include <Box2D/Box2D.h>
namespace Engine
{
    class ContactListener : public b2ContactListener
    {
    public:
        ContactListener();
        virtual ~ContactListener();

        virtual void BeginContact(b2Contact* contact);
        virtual void EndContact(b2Contact* contact);
        virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
    };
}