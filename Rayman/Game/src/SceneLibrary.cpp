#include "SceneLibrary.h"

#include "Components/Player.h"
#include "Components/EnemyController.h"
#include "Components/PickupComponent.h"

#include "Core/System/Scene/Scene.h"

#include "Core/Gameplay/GameObject.h"
#include "Core/Gameplay/Component/Camera.h"
#include "Core/Gameplay/Component/BoxCollider2D.h"
#include "Core/Gameplay/Component/ImGuiTest.h"
#include "Core/Gameplay/Component/SpriteRenderer.h"
#include "Core/Application.h"
#include "Core/Utilities/Math/SimpleMath.h"
#include "Components/CameraController.h"
#include "Components/ParalaxScrolling.h"

void SaveLevel1(Engine::Application& a_Application)
{
    Engine::Scene* scene = new Engine::Scene(0, LEVEL_1_NAME);
    scene->SetApplication(a_Application);
    scene->CreateCamera();

    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(1, 3), DXS::Vector2(2, 2));
        gameObject.AddComponent<Player>();
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "Rayman.png");
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetLayer(1);
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Player);
    }

    {
        Engine::GameObject& gameObject = scene->AddGameObject();
        gameObject.AddComponent<CameraController>();
    }
	{
		Engine::GameObject& gameObject = scene->AddGameObject();
		gameObject.AddComponent<ParalaxScrolling>();
	}
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(15, 0), DXS::Vector2(30, 2));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "dirt.png");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Platform);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(3.f, 7.f), DXS::Vector2(3, 1));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "dirt.png");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Platform);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(15.f, 5.f), DXS::Vector2(3, 1));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "dirt.png");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Platform);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(33, -2), DXS::Vector2(6, 2));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "water2.jpg");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Water);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(45, 0), DXS::Vector2(20, 2));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "dirt.png");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Platform);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(57.f, -2), DXS::Vector2(5, 2));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "water2.jpg");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Water);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(62.f, 0), DXS::Vector2(5, 2));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "dirt.png");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Platform);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(66.f, -2), DXS::Vector2(5, 2));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "water2.jpg");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Water);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(76.f, 0), DXS::Vector2(16, 2));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "dirt.png");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Platform);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(80.f, 5.f), DXS::Vector2(3, 1));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "dirt.png");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Platform);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(82.f, 9.f), DXS::Vector2(3, 1));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "dirt.png");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Platform);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(75.f, 13.f), DXS::Vector2(3, 1));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "dirt.png");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Platform);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(68.f, 17.f), DXS::Vector2(3, 1));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "dirt.png");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Platform);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(78.f, 21.f), DXS::Vector2(15, 1));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "dirt.png");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Platform);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(-5.f, 15.f), DXS::Vector2(10, 30));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "dirt.png");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Wall);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(90.f, 15.f), DXS::Vector2(11, 50));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "dirt.png");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Wall);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(100, -10), DXS::Vector2(200, 2));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "water2.jpg");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Water);
    }

    //Pickups
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(3.f, 9.f), DXS::Vector2(1, 1));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "BlueOrb.png");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Pickup);
        gameObject.AddComponent<PickupComponent>().SetPickupType(Engine::PickupTypes::ScoreUp);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(15.f, 7.f), DXS::Vector2(1, 1));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "BlueOrb.png");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Pickup);
        gameObject.AddComponent<PickupComponent>().SetPickupType(Engine::PickupTypes::ScoreUp);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(15.f, 14.f), DXS::Vector2(1, 1));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "BlueOrb.png");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Pickup);
        gameObject.AddComponent<PickupComponent>().SetPickupType(Engine::PickupTypes::ScoreUp);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(17.f, 16.f), DXS::Vector2(1, 1));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "BlueOrb.png");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Pickup);
        gameObject.AddComponent<PickupComponent>().SetPickupType(Engine::PickupTypes::ScoreUp);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(19.f, 18.f), DXS::Vector2(1, 1));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        //    gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "BigPower.png");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Pickup);
        gameObject.AddComponent<PickupComponent>().SetPickupType(Engine::PickupTypes::ScoreUp);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(33, 7), DXS::Vector2(1, 1));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "BlueOrb.png");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Pickup);
        gameObject.AddComponent<PickupComponent>().SetPickupType(Engine::PickupTypes::ScoreUp);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(30, 5), DXS::Vector2(1, 1));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "BlueOrb.png");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Pickup);
        gameObject.AddComponent<PickupComponent>().SetPickupType(Engine::PickupTypes::ScoreUp);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(36, 5), DXS::Vector2(1, 1));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "BlueOrb.png");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Pickup);
        gameObject.AddComponent<PickupComponent>().SetPickupType(Engine::PickupTypes::ScoreUp);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(57.f, 5), DXS::Vector2(1, 1));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "BlueOrb.png");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Pickup);
        gameObject.AddComponent<PickupComponent>().SetPickupType(Engine::PickupTypes::ScoreUp);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(66.f, 5), DXS::Vector2(1, 1));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "BlueOrb.png");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Pickup);
        gameObject.AddComponent<PickupComponent>().SetPickupType(Engine::PickupTypes::ScoreUp);
    }

    //EndLevel
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(85.f, 23.f), DXS::Vector2(2, 2));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "FinishLevel.jpg");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Pickup);
        gameObject.AddComponent<PickupComponent>().SetPickupType(Engine::PickupTypes::FinishLevel);
    }

    scene->Update(0.016f);
    scene->Save(GAME_SCENE_PATH, LEVEL_1_NAME);

    delete scene;
}

void SaveLevel2(Engine::Application& a_Application)
{
    Engine::Scene* scene = new Engine::Scene(0, LEVEL_2_NAME);
    scene->SetApplication(a_Application);
    scene->CreateCamera();

    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(1, 3), DXS::Vector2(2, 2));
        gameObject.AddComponent<Player>();
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "Rayman.png");
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetLayer(1);
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Player);
    }

    {
        Engine::GameObject& gameObject = scene->AddGameObject();
        gameObject.AddComponent<CameraController>();
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(10, 0), DXS::Vector2(20, 2));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "dirt.png");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Platform);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(24, 0), DXS::Vector2(3, .5f));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "dirt.png");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Platform);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(29, 4), DXS::Vector2(3, .5f));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "dirt.png");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Platform);
    }

    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(36, 3), DXS::Vector2(3, .5f));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "dirt.png");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Platform);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(30, -2), DXS::Vector2(20, 2));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "water2.jpg");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Water);
    }

    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(44, 0), DXS::Vector2(6, 2));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "dirt.png");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Platform);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(49, -2), DXS::Vector2(4, 2));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "water2.jpg");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Water);
    }

    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(53, 0), DXS::Vector2(4, 2));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "dirt.png");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Platform);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(57, -2), DXS::Vector2(4, 2));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "water2.jpg");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Water);
    }

    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(61, 0), DXS::Vector2(4, 2));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "dirt.png");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Platform);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(65, -2), DXS::Vector2(4, 2));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "water2.jpg");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Water);
    }

    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(73, 0), DXS::Vector2(12, 2));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "dirt.png");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Platform);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(75, 2), DXS::Vector2(8, 2));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "dirt.png");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Platform);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(77, 4), DXS::Vector2(4, 2));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "dirt.png");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Platform);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(85, 0), DXS::Vector2(12, 2));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "dirt.png");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Platform);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(93, -2), DXS::Vector2(4, 2));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "water2.jpg");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Water);
    }

    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(97, 0), DXS::Vector2(4, 2));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "dirt.png");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Platform);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(101, -2), DXS::Vector2(4, 2));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "water2.jpg");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Water);
    }

    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(105, 0), DXS::Vector2(4, 2));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "dirt.png");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Platform);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(109, -2), DXS::Vector2(4, 2));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "water2.jpg");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Water);
    }

    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(112, 4), DXS::Vector2(4, .5f));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "dirt.png");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Platform);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(116, -2), DXS::Vector2(4, 2));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "water2.jpg");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Water);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(123, 0), DXS::Vector2(10, 2));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "dirt.png");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Platform);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(130, -2), DXS::Vector2(4, 2));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "water2.jpg");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Water);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(137, 0), DXS::Vector2(10, 2));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "dirt.png");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Platform);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(144, -2), DXS::Vector2(4, 2));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "water2.jpg");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Water);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(151, 0), DXS::Vector2(10, 2));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "dirt.png");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Platform);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(155, 4), DXS::Vector2(3, .5));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "dirt.png");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Platform);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(160, 6), DXS::Vector2(3, .5));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "dirt.png");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Platform);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(165, 8), DXS::Vector2(3, .5));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "dirt.png");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Platform);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(170, 10), DXS::Vector2(3, .5));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "dirt.png");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Platform);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(182, 12), DXS::Vector2(14, .5));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "dirt.png");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Platform);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(0, 20), DXS::Vector2(3, 50));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "dirt.png");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Wall);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(192, 25), DXS::Vector2(3, 50));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "dirt.png");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Wall);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(168, -2), DXS::Vector2(34, 2));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "water2.jpg");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Water);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(100, -10), DXS::Vector2(200, 2));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "water2.jpg");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Water);
    }


    //Pickups
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(38, 8), DXS::Vector2(1, 1));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "BlueOrb.png");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Pickup);
        gameObject.AddComponent<PickupComponent>().SetPickupType(Engine::PickupTypes::ScoreUp);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(39, 7), DXS::Vector2(1, 1));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "BlueOrb.png");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Pickup);
        gameObject.AddComponent<PickupComponent>().SetPickupType(Engine::PickupTypes::ScoreUp);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(40, 6), DXS::Vector2(1, 1));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "BlueOrb.png");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Pickup);
        gameObject.AddComponent<PickupComponent>().SetPickupType(Engine::PickupTypes::ScoreUp);
    }

    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(41, 5), DXS::Vector2(1, 1));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "BlueOrb.png");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Pickup);
        gameObject.AddComponent<PickupComponent>().SetPickupType(Engine::PickupTypes::ScoreUp);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(97, 5), DXS::Vector2(1, 1));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "BlueOrb.png");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Pickup);
        gameObject.AddComponent<PickupComponent>().SetPickupType(Engine::PickupTypes::ScoreUp);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(96, 6), DXS::Vector2(1, 1));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "BlueOrb.png");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Pickup);
        gameObject.AddComponent<PickupComponent>().SetPickupType(Engine::PickupTypes::ScoreUp);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(95, 7), DXS::Vector2(1, 1));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "BlueOrb.png");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Pickup);
        gameObject.AddComponent<PickupComponent>().SetPickupType(Engine::PickupTypes::ScoreUp);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(85, 7), DXS::Vector2(1, 1));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "BlueOrb.png");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Pickup);
        gameObject.AddComponent<PickupComponent>().SetPickupType(Engine::PickupTypes::ScoreUp);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(90, 7), DXS::Vector2(1, 1));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        // gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "BigPower.png");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Pickup);
        gameObject.AddComponent<PickupComponent>().SetPickupType(Engine::PickupTypes::BigPower);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(105, 4), DXS::Vector2(1, 1));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "BlueOrb.png");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Pickup);
        gameObject.AddComponent<PickupComponent>().SetPickupType(Engine::PickupTypes::ScoreUp);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(112, 11), DXS::Vector2(1, 1));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "BlueOrb.png");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Pickup);
        gameObject.AddComponent<PickupComponent>().SetPickupType(Engine::PickupTypes::ScoreUp);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(109, 9), DXS::Vector2(1, 1));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "BlueOrb.png");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Pickup);
        gameObject.AddComponent<PickupComponent>().SetPickupType(Engine::PickupTypes::ScoreUp);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(120, 7), DXS::Vector2(1, 1));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "BlueOrb.png");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Pickup);
        gameObject.AddComponent<PickupComponent>().SetPickupType(Engine::PickupTypes::ScoreUp);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(122, 9), DXS::Vector2(1, 1));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "BlueOrb.png");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Pickup);
        gameObject.AddComponent<PickupComponent>().SetPickupType(Engine::PickupTypes::ScoreUp);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(125, 7), DXS::Vector2(1, 1));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "BlueOrb.png");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Pickup);
        gameObject.AddComponent<PickupComponent>().SetPickupType(Engine::PickupTypes::ScoreUp);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(155, 6), DXS::Vector2(1, 1));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "BlueOrb.png");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Pickup);
        gameObject.AddComponent<PickupComponent>().SetPickupType(Engine::PickupTypes::ScoreUp);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(160, 8), DXS::Vector2(1, 1));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "BlueOrb.png");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Pickup);
        gameObject.AddComponent<PickupComponent>().SetPickupType(Engine::PickupTypes::ScoreUp);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(165, 10), DXS::Vector2(1, 1));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "BlueOrb.png");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Pickup);
        gameObject.AddComponent<PickupComponent>().SetPickupType(Engine::PickupTypes::ScoreUp);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(170, 12), DXS::Vector2(1, 1));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "BlueOrb.png");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Pickup);
        gameObject.AddComponent<PickupComponent>().SetPickupType(Engine::PickupTypes::ScoreUp);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(182, 18), DXS::Vector2(1, 1));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "BlueOrb.png");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Pickup);
        gameObject.AddComponent<PickupComponent>().SetPickupType(Engine::PickupTypes::ScoreUp);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(179, 16), DXS::Vector2(1, 1));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "BlueOrb.png");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Pickup);
        gameObject.AddComponent<PickupComponent>().SetPickupType(Engine::PickupTypes::ScoreUp);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(185, 16), DXS::Vector2(1, 1));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "BlueOrb.png");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Pickup);
        gameObject.AddComponent<PickupComponent>().SetPickupType(Engine::PickupTypes::ScoreUp);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(176, 14), DXS::Vector2(1, 1));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "BlueOrb.png");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Pickup);
        gameObject.AddComponent<PickupComponent>().SetPickupType(Engine::PickupTypes::ScoreUp);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(188, 14), DXS::Vector2(1, 1));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "BlueOrb.png");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Pickup);
        gameObject.AddComponent<PickupComponent>().SetPickupType(Engine::PickupTypes::ScoreUp);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(188, 14), DXS::Vector2(2, 2));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "FinishLevel.jpg");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Pickup);
        gameObject.AddComponent<PickupComponent>().SetPickupType(Engine::PickupTypes::FinishLevel);
    }
    //Enemies
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(53, 2), DXS::Vector2(1, 1));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Enemy);
        gameObject.AddComponent<EnemyController>().SetEnemyType(EnemyType::PatrolEnemy);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(62, 2), DXS::Vector2(1, 1));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Enemy);
        gameObject.AddComponent<EnemyController>().SetEnemyType(EnemyType::PatrolEnemy);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(81, 2), DXS::Vector2(1, 1));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Enemy);
        gameObject.AddComponent<EnemyController>().SetEnemyType(EnemyType::JumpEnemy);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(120, 2), DXS::Vector2(1, 1));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Enemy);
        gameObject.AddComponent<EnemyController>().SetEnemyType(EnemyType::PatrolEnemy);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(125, 2), DXS::Vector2(1, 1));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Enemy);
        gameObject.AddComponent<EnemyController>().SetEnemyType(EnemyType::PatrolEnemy);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(151, 2), DXS::Vector2(1, 1));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Enemy);
        gameObject.AddComponent<EnemyController>().SetEnemyType(EnemyType::AwareEnemy);
    }

    scene->Update(0.016f);
    scene->Save(GAME_SCENE_PATH, LEVEL_2_NAME);

    delete scene;
}

void SaveLevel3(Engine::Application& a_Application)
{
    Engine::Scene* scene = new Engine::Scene(0, LEVEL_3_NAME);
    scene->SetApplication(a_Application);
    scene->CreateCamera();

    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(1, 3), DXS::Vector2(2, 2));
        gameObject.AddComponent<Player>();
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "Rayman.png");
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetLayer(1);
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Player);
    }

    {
        Engine::GameObject& gameObject = scene->AddGameObject();
        gameObject.AddComponent<CameraController>();
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(10, 0), DXS::Vector2(20, 2));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "dirt.png");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Platform);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(28, 0), DXS::Vector2(10, 2));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "dirt.png");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Platform);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(21.5f, -2), DXS::Vector2(3, 2));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "water2.jpg");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Water);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(31, 0), DXS::Vector2(10, 2));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "dirt.png");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Platform);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(38, -2), DXS::Vector2(4, 2));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "water2.jpg");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Water);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(45, 0), DXS::Vector2(10, 2));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "dirt.png");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Platform);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(52, -2), DXS::Vector2(4, 2));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "water2.jpg");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Water);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(59, 0), DXS::Vector2(10, 2));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "dirt.png");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Platform);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(66, -2), DXS::Vector2(4, 2));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "water2.jpg");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Water);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(73, 0), DXS::Vector2(10, 2));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "dirt.png");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Platform);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(73, 0), DXS::Vector2(10, 2));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "dirt.png");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Platform);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(77, 5), DXS::Vector2(3, .5));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "dirt.png");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Platform);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(81, 9), DXS::Vector2(3, .5));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "dirt.png");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Platform);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(84, 13), DXS::Vector2(3, .5));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "dirt.png");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Platform);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(87, 17), DXS::Vector2(3, .5));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "dirt.png");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Platform);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(94, 19), DXS::Vector2(8, 2));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "dirt.png");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Platform);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(110, 19), DXS::Vector2(14, 2));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "dirt.png");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Platform);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(122, 17), DXS::Vector2(3, .5));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "dirt.png");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Platform);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(122, 11), DXS::Vector2(8, .5));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "dirt.png");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Platform);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(116, 5), DXS::Vector2(20, 2));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "dirt.png");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Platform);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(135, 19), DXS::Vector2(14, 2));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "dirt.png");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Platform);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(149, 15), DXS::Vector2(14, .5));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "dirt.png");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Platform);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(149, 7), DXS::Vector2(14, 2));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "dirt.png");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Platform);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(159, 11), DXS::Vector2(3, .5));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "dirt.png");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Platform);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(165, 14), DXS::Vector2(3, .5));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "dirt.png");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Platform);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(170, 17), DXS::Vector2(3, .5));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "dirt.png");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Platform);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(188, 21), DXS::Vector2(25, .5));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "dirt.png");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Platform);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(186, 12), DXS::Vector2(25, .5));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "dirt.png");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Platform);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(-3, 20), DXS::Vector2(6, 40));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "dirt.png");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Wall);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(200, 20), DXS::Vector2(6, 40));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "dirt.png");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Wall);
    }

    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(87, -2), DXS::Vector2(15, 2));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "water2.jpg");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Water);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(100, 17), DXS::Vector2(8, 2));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "water2.jpg");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Water);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(155, 3), DXS::Vector2(70, 2));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "water2.jpg");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Water);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(100, -10), DXS::Vector2(200, 2));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "water2.jpg");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Water);
    }
    //Pickups
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(28, 8), DXS::Vector2(1, 1));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Pickup);
        gameObject.AddComponent<PickupComponent>().SetPickupType(PickupTypes::GoldenFist);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(60, 8), DXS::Vector2(1, 1));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Pickup);
        gameObject.AddComponent<PickupComponent>().SetPickupType(PickupTypes::GoldenFist);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(77, 7), DXS::Vector2(1, 1));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "BlueOrb.png");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Pickup);
        gameObject.AddComponent<PickupComponent>().SetPickupType(PickupTypes::ScoreUp);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(81, 11), DXS::Vector2(1, 1));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "BlueOrb.png");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Pickup);
        gameObject.AddComponent<PickupComponent>().SetPickupType(PickupTypes::ScoreUp);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(84, 15), DXS::Vector2(1, 1));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "BlueOrb.png");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Pickup);
        gameObject.AddComponent<PickupComponent>().SetPickupType(PickupTypes::ScoreUp);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(87, 19), DXS::Vector2(1, 1));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "BlueOrb.png");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Pickup);
        gameObject.AddComponent<PickupComponent>().SetPickupType(PickupTypes::ScoreUp);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(115, 25), DXS::Vector2(1, 1));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "BlueOrb.png");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Pickup);
        gameObject.AddComponent<PickupComponent>().SetPickupType(PickupTypes::ScoreUp);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(122, 14), DXS::Vector2(1, 1));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "BlueOrb.png");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Pickup);
        gameObject.AddComponent<PickupComponent>().SetPickupType(PickupTypes::ScoreUp);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(118, 7), DXS::Vector2(1, 1));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "BlueOrb.png");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Pickup);
        gameObject.AddComponent<PickupComponent>().SetPickupType(PickupTypes::ScoreUp);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(126, 7), DXS::Vector2(1, 1));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "BlueOrb.png");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Pickup);
        gameObject.AddComponent<PickupComponent>().SetPickupType(PickupTypes::ScoreUp);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(145, 9), DXS::Vector2(1, 1));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "BlueOrb.png");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Pickup);
        gameObject.AddComponent<PickupComponent>().SetPickupType(PickupTypes::ScoreUp);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(159, 13), DXS::Vector2(1, 1));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "BlueOrb.png");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Pickup);
        gameObject.AddComponent<PickupComponent>().SetPickupType(PickupTypes::ScoreUp);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(180, 23), DXS::Vector2(1, 1));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "BlueOrb.png");
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Pickup);
        gameObject.AddComponent<PickupComponent>().SetPickupType(PickupTypes::ScoreUp);
    }
    //Enemies
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(28, 2), DXS::Vector2(1, 1));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Enemy);
        gameObject.AddComponent<EnemyController>().SetEnemyType(EnemyType::AwareEnemy);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(45, 2), DXS::Vector2(1, 1));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Enemy);
        gameObject.AddComponent<EnemyController>().SetEnemyType(EnemyType::AttackingEnemy);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(73, 2), DXS::Vector2(1, 1));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Enemy);
        gameObject.AddComponent<EnemyController>().SetEnemyType(EnemyType::AttackingEnemy);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(110, 21), DXS::Vector2(2, 2));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Enemy);
        gameObject.AddComponent<EnemyController>().SetEnemyType(EnemyType::ShootingEnemy);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(115, 21), DXS::Vector2(1, 1));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Enemy);
        gameObject.AddComponent<EnemyController>().SetEnemyType(EnemyType::AttackingEnemy);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(120, 13), DXS::Vector2(1, 1));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Enemy);
        gameObject.AddComponent<EnemyController>().SetEnemyType(EnemyType::AttackingEnemy);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(124, 13), DXS::Vector2(1, 1));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Enemy);
        gameObject.AddComponent<EnemyController>().SetEnemyType(EnemyType::AwareEnemy);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(120, 7), DXS::Vector2(1, 1));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Enemy);
        gameObject.AddComponent<EnemyController>().SetEnemyType(EnemyType::AttackingEnemy);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(124, 7), DXS::Vector2(1, 1));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Enemy);
        gameObject.AddComponent<EnemyController>().SetEnemyType(EnemyType::AttackingEnemy);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(130, 21), DXS::Vector2(1, 1));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Enemy);
        gameObject.AddComponent<EnemyController>().SetEnemyType(EnemyType::AwareEnemy);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(133, 21), DXS::Vector2(1, 1));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Enemy);
        gameObject.AddComponent<EnemyController>().SetEnemyType(EnemyType::AttackingEnemy);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(136, 21), DXS::Vector2(1, 1));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Enemy);
        gameObject.AddComponent<EnemyController>().SetEnemyType(EnemyType::AttackingEnemy);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(147, 9), DXS::Vector2(1, 1));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Enemy);
        gameObject.AddComponent<EnemyController>().SetEnemyType(EnemyType::AwareEnemy);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(151, 9), DXS::Vector2(1, 1));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Enemy);
        gameObject.AddComponent<EnemyController>().SetEnemyType(EnemyType::AttackingEnemy);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(185, 23), DXS::Vector2(1, 1));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Enemy);
        gameObject.AddComponent<EnemyController>().SetEnemyType(EnemyType::AwareEnemy);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(189, 23), DXS::Vector2(1, 1));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Enemy);
        gameObject.AddComponent<EnemyController>().SetEnemyType(EnemyType::AttackingEnemy);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(193, 23), DXS::Vector2(1, 1));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Enemy);
        gameObject.AddComponent<EnemyController>().SetEnemyType(EnemyType::AwareEnemy);
    }
    {
        Engine::GameObject& gameObject = scene->AddGameObject(DXS::Vector2(190, 14), DXS::Vector2(2, 2));
        gameObject.AddComponent<Engine::SpriteRenderer>();
        gameObject.AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Enemy);
        gameObject.AddComponent<EnemyController>().SetEnemyType(EnemyType::ShootingEnemy);
    }
    scene->Update(0.016f);
    scene->Save(GAME_SCENE_PATH, LEVEL_3_NAME);

    delete scene;
}
