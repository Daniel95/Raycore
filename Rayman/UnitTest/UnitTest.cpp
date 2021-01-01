#include "pch.h"
#include "CppUnitTest.h"
#include "Core/Gameplay/Component/BoxCollider2D.h"
#include "Core/Application.h"
#include "Core/System/Scene/Scene.h"
#include "Core/Gameplay/GameObject.h"
#include "Core/Gameplay/Component/TestComponent.h"
#include "Core/Utilities/Math/SimpleMath.h"
#include "Core/Gameplay/Component/BoxCollider2D.h"
#include "Core/System/DrawSystem.h"
#include "Core/System/EventSystem.h"
#include "Core/System/GameSystem.h"
#include "Core/System/ImGuiSystem.h"
#include "Core/System/ResourceSystem.h"
#include "Core/System/SceneSystem.h"
#include "Core/System/SoundSystem.h"
#include "Core/System/InputSystem.h"
#include "Core/System/Manager/SystemManager.h"
#include "Core/System/Resource/Material.h"
#include "Core/System/Resource/Mesh.h"
#include "Core/System/Resource/Texture.h"
#include "Core/System/Scene/Scene.h"
#include "Core/System/Manager/ISystem.h"
#include <Core\Gameplay\Component\SpriteRenderer.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ExampleUnitTest
{
    TEST_CLASS(ExampleUnitTest)
    {
    public:
        TEST_METHOD(ExampleUnitTestMethod)
        {
            bool unitTestSucceeded = true;
            Assert::IsTrue(unitTestSucceeded);
        }
    };
}

namespace UnitTest
{
    Engine::Application* application = nullptr;

    Engine::Application* GetApplication()
    {
        if (application == nullptr)
        {
            application = new Engine::Application;
        }
        return application;
    }

	TEST_CLASS(UnitTest)
	{
	public:
		
		TEST_METHOD(TestTransform)
		{
            //Init
            Engine::Scene* scene = new Engine::Scene(0, "test");
            scene->SetApplication(*GetApplication());
            scene->CreateCamera();

            DXS::Vector2 position = DXS::Vector2(42, 66.66f);
            DXS::Vector2 scale = DXS::Vector2(23.3f, 77.123f);
            
            Engine::GameObject& gameObject1 = scene->AddGameObject(position, scale);
            Engine::Transform* transform = gameObject1.GetTransform();

            //Tests:
            Assert::AreEqual(transform->GetPosition().x, position.x);
            Assert::AreEqual(transform->GetPosition().y, position.y);
            Assert::AreEqual(transform->GetPosition().z, 0.f);

            Assert::AreEqual(transform->GetScale().x, scale.x);
            Assert::AreEqual(transform->GetScale().y, scale.y);
            Assert::AreEqual(transform->GetScale().z, 1.f);

            /*
            transform->SetRotation(DXS::Quaternion(0.1f, 0.9f, 0.5f, 1));

            DXS::Matrix rotationMatrix = transform->GetRotationMatrix();
            DXS::Matrix comparisonRotationMatrix = DXS::Matrix(
                -0.0241546f, -0.3961353f, 0.9178744f, 0.f,
                0.5700483f, 0.7487923f, 0.3381642f, 0.f,
                -0.8212560f, 0.5314010f, 0.2077295f, 0.f,
                0.f, 0.f, 0.f, 0.f
            );

            bool isEqual = rotationMatrix == comparisonRotationMatrix;
            Assert::IsTrue(isEqual);

            */


            //Cleanup

            delete scene;
		}

        TEST_METHOD(TestScene)
        {
            //Init
            Engine::Scene* scene = new Engine::Scene(0, "test");
            scene->SetApplication(*GetApplication());
            scene->CreateCamera();

            int numberOfGameObjects = 11;

            for (size_t i = 0; i < numberOfGameObjects - 1; i++)
            {
                Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(0, 0), DXS::Vector2(1, 1));
            }

            {
                bool isEqual = scene->GetGameObjects().size() == 0;
                Assert::IsTrue(isEqual);
            }

            scene->Update(0.016f);

            {
                bool isEqual = scene->GetGameObjects().size() == numberOfGameObjects;
                Assert::IsTrue(isEqual);
            }

            scene->DestroyAllGameObjects();

            {
                bool isEqual = scene->GetGameObjects().size() == 0;
                Assert::IsTrue(isEqual);
            }

            delete scene;
        }

        TEST_METHOD(TestECS)
        {
            //Init
            Engine::Scene* scene = new Engine::Scene(0, "test");
            scene->SetApplication(*GetApplication());
            scene->CreateCamera();

            Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(0, 0), DXS::Vector2(1, 1));

            gameObject.AddComponent<Engine::TestComponent>();

            {
                bool isEqual = gameObject.GetComponents().size() == 2;
                Assert::IsTrue(isEqual);
            }

            gameObject.RemoveComponent<Engine::TestComponent>();

            {
                bool isEqual = gameObject.GetComponents().size() == 1;
                Assert::IsTrue(isEqual);
            }

            //Cleanup
            delete scene;
        }

        TEST_METHOD(TestSystems)
        {
            Engine::SystemManager* systemManager = new Engine::SystemManager();

            systemManager->CreateSystem<Engine::SoundSystem>();
            systemManager->CreateSystem<Engine::EventSystem>();
            systemManager->CreateSystem<Engine::InputSystem>();
            systemManager->CreateSystem<Engine::GameSystem>();

            {
                bool isEqual = systemManager->GetAllSystems().size() == 4;
                Assert::IsTrue(isEqual);
            }

            {
                bool isEqual = &systemManager->GetSystem<Engine::GameSystem>() != nullptr;
                Assert::IsTrue(isEqual);
            }

            systemManager->DeleteSystem<Engine::SoundSystem>();
            systemManager->DeleteSystem<Engine::EventSystem>();
            systemManager->DeleteSystem<Engine::InputSystem>();
            systemManager->DeleteSystem<Engine::GameSystem>();

            {
                bool isEqual = &systemManager->GetSystem<Engine::GameSystem>() == nullptr;
                Assert::IsTrue(isEqual);
            }

            {
                bool isEqual = systemManager->GetAllSystems().size() == 0;
                Assert::IsTrue(isEqual);
            }
            
            delete systemManager;
        }

        TEST_METHOD(TestResources)
        {
            Engine::SystemManager* systemManager = new Engine::SystemManager();
            Engine::ResourceSystem* resourceSystem = &systemManager->CreateSystem<Engine::ResourceSystem>();

            resourceSystem->LoadResource<Engine::Scene>(GAME_SCENE_PATH + "Level01.txt");
            resourceSystem->LoadResource<Engine::Scene>(GAME_SCENE_PATH + "Level01.txt");

            {
                bool isEqual = resourceSystem->GetAllResources().size() == 1;
                Assert::IsTrue(isEqual);
            }
        }
	};
}

namespace GameplayTests {
    Engine::Application* application = nullptr;

    Engine::Application* GetApplication()
    {
        if (application == nullptr)
        {
            application = new Engine::Application;
        }
        return application;
    }

    TEST_CLASS(Gameplaytests)
    {
    public:
        TEST_METHOD(TestCollisionType)
        {
            //Init
            Engine::Scene* scene = new Engine::Scene(0, "test");
            scene->SetApplication(*GetApplication());
            scene->CreateCamera();

            Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(1, 3), DXS::Vector2(2, 2));
            gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Player);

            bool isEqual = gameObject.GetComponent<Engine::BoxCollider2D>()->GetCollisionType() == Engine::CollisionType::Player;

            Assert::IsTrue(isEqual);
            //Cleanup
            delete scene;
        }

        TEST_METHOD(TestPlayerGravity)
        {
            //Init
            Engine::Scene* scene = new Engine::Scene(0, "test");
            scene->SetApplication(*GetApplication());
            scene->CreateCamera();

            Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(0, 0), DXS::Vector2(1, 1));
            gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Player);

            for (int i = 0; i < 100; i++)
            {
                scene->Update(0.016f);
            }
            bool isEqual = gameObject.GetComponent<Engine::Transform>()->GetPosition() != DXS::Vector3(0, 0, 0);

            Assert::IsTrue(isEqual);
            //Cleanup
            delete scene;
        }
        TEST_METHOD(TestPlayerFloorCollision)
        {
            //Init
            Engine::Scene* scene = new Engine::Scene(0, "test");
            scene->SetApplication(*GetApplication());
            scene->CreateCamera();

            Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(0, 0), DXS::Vector2(1, 1));
            gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Player);
            Engine::GameObject& gameObject1 = scene->AddGameObject(DXS::Vector2(0, -10), DXS::Vector2(1, 1));
            gameObject1.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Platform);

            for (int i = 0; i < 5000; i++)
            {
                scene->Update(0.016f);
                scene->FixedUpdate(0.016f);
            }
            bool isEqual = false;
            if (gameObject.GetComponent<Engine::Transform>()->GetPosition().y > -9 && gameObject.GetComponent<Engine::Transform>()->GetPosition().y < -8)
            {
                isEqual = true;
            }
            Assert::IsTrue(isEqual);
            //Cleanup
            delete scene;
        }

        TEST_METHOD(TestPlayerJumpThroughFloorCollision)
        {
            //Init
            Engine::Scene* scene = new Engine::Scene(0, "test");
            scene->SetApplication(*GetApplication());
            scene->CreateCamera();

            Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(0, 0), DXS::Vector2(1, 1));
            gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Player);

            //Bottom platform
            Engine::GameObject& gameObject2 = scene->AddGameObject(DXS::Vector2(0, -3), DXS::Vector2(20, 2));
            gameObject2.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Platform);


            //Platform player jumps through and should land on
            Engine::GameObject& gameObject1 = scene->AddGameObject(DXS::Vector2(0, 6), DXS::Vector2(20, 1));
            gameObject1.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Platform);


            for (int i = 0; i < 20000; i++)
            {
                if (i == 5000)
                {
                   gameObject.GetComponent<Engine::BoxCollider2D>()->Jump();
                }
                scene->Update(0.016f);
                scene->FixedUpdate(0.016f);
            }
            bool isEqual = false;
            if (gameObject.GetComponent<Engine::Transform>()->GetPosition().y > 6 && gameObject.GetComponent<Engine::Transform>()->GetPosition().y < 8)
            {
                isEqual = true;
            }
            Assert::IsTrue(isEqual);
            //Cleanup
            delete scene;
        }
    };
}