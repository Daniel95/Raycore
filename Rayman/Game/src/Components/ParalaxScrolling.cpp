#include "ParalaxScrolling.h"

#include "Core/Utilities/Defines.h"
#include "Core/System/Scene/Scene.h"
#include "Core/Gameplay/GameObject.h"
#include "Core/Gameplay/Component/SpriteRenderer.h"
#include "Core/Gameplay/Component/Camera.h"
#include "Core/Gameplay/Component/BoxCollider2D.h"
#include "Core/Application.h"

ParalaxScrolling::ParalaxScrolling()
{

}

ParalaxScrolling::~ParalaxScrolling()
{
	for (ParallaxObject* po : m_ObjectsToParalax)
	{
		if (po != nullptr)
		{
			delete po;
		}
	}
	m_ObjectsToParalax.clear();
}

void ParalaxScrolling::Init(GameObject* a_GameObject)
{
	Component::Init(a_GameObject);

	if (!GetGameObject()->GetScene()->GetApplication()->IsEditorMode())
	{
		//Yes yes I know you could do this with 2 or 3 copies but I don't have time to make that.
		//So instead I'm populating the scene with enough of them to cover the level.
		for (int i = -m_AmountOfCopies; i < m_AmountOfCopies; i++)
		{
			//Background.
			{
				ParallaxObject* po = new ParallaxObject();

				po->m_GameObject = &GetGameObject()->GetScene()->AddGameObject(DXS::Vector2(0, 0), DXS::Vector2(100, 50));
				po->m_GameObject->AddComponent<Engine::SpriteRenderer>();
				po->m_GameObject->GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "mountains-back.png");
				po->m_OffsetX = 100.f * i;
				po->m_OffsetY = 10.f;
				po->m_ParallaxIndex = 7;

				m_ObjectsToParalax.push_back(po);
			}

			{
				ParallaxObject* po = new ParallaxObject();

				po->m_GameObject = &GetGameObject()->GetScene()->AddGameObject(DXS::Vector2(0, 0), DXS::Vector2(100, 50));
				po->m_GameObject->AddComponent<Engine::SpriteRenderer>();
				po->m_GameObject->GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "mountains-mid1.png");
				po->m_OffsetX = 100.f * i;
				po->m_OffsetY = 10.f;
				po->m_ParallaxIndex = 6;

				m_ObjectsToParalax.push_back(po);
			}

			{
				ParallaxObject* po = new ParallaxObject();

				po->m_GameObject = &GetGameObject()->GetScene()->AddGameObject(DXS::Vector2(0, 0), DXS::Vector2(100, 50));
				po->m_GameObject->AddComponent<Engine::SpriteRenderer>();
				po->m_GameObject->GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "mountains-mid2.png");
				po->m_OffsetX = 100.f * i;
				po->m_OffsetY = 10.f;
				po->m_ParallaxIndex = 5;

				m_ObjectsToParalax.push_back(po);
			}

			//Water.
			{
				ParallaxObject* po = new ParallaxObject();

				po->m_GameObject = &GetGameObject()->GetScene()->AddGameObject(DXS::Vector2(100.f * i, -6.f), DXS::Vector2(100, 10));
				po->m_GameObject->AddComponent<Engine::BoxCollider2D>().SetCollisionType(Engine::CollisionType::Water);
				po->m_GameObject->AddComponent<Engine::SpriteRenderer>();
				po->m_GameObject->GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "water1.png");
				po->m_OffsetX = 100.f * i;
				po->m_OffsetY = -6.f;
				po->m_ParallaxIndex = -2;
				po->m_MultiplierX = 0.f;
				po->m_MultiplierY = 0.f;

				m_ObjectsToParalax.push_back(po);
			}

			{
				ParallaxObject* po = new ParallaxObject();

				po->m_GameObject = &GetGameObject()->GetScene()->AddGameObject(DXS::Vector2(100.f * i, -6.f), DXS::Vector2(100, 10));
				po->m_GameObject->AddComponent<Engine::SpriteRenderer>();
				po->m_GameObject->GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "water2.png");
				po->m_OffsetX = 100.f * i;
				po->m_OffsetY = -6.f;
				po->m_ParallaxIndex = -3;
				po->m_MultiplierX = 2.f;
				po->m_MultiplierY = 0.f;

				m_ObjectsToParalax.push_back(po);
			}

			{
				ParallaxObject* po = new ParallaxObject();

				po->m_GameObject = &GetGameObject()->GetScene()->AddGameObject(DXS::Vector2(100.f * i, -6.f), DXS::Vector2(100, 10));
				po->m_GameObject->AddComponent<Engine::SpriteRenderer>();
				po->m_GameObject->GetComponent<Engine::SpriteRenderer>()->SetTexture(GAME_TEXTURES_PATH + "water3.png");
				po->m_OffsetX = 100.f * i;
				po->m_OffsetY = -6.f;
				po->m_ParallaxIndex = -4;
				po->m_MultiplierX = 2.f;
				po->m_MultiplierY = 0.f;

				m_ObjectsToParalax.push_back(po);
			}
		}
	}
}

void ParalaxScrolling::Update(float a_DeltaTime)
{
	if (Engine::Camera::HasMainCamera())
	{
		Engine::Camera& cam = Engine::Camera::GetMainCamera();
		const DXS::Vector3& pos = cam.GetGameObject()->GetTransform()->GetPosition();

		for (ParallaxObject* po : m_ObjectsToParalax)
		{
			DXS::Vector3 p;
			p.x = (pos.x / po->m_ParallaxIndex * po->m_MultiplierX) + po->m_OffsetX;
			p.y = (pos.y / po->m_ParallaxIndex * po->m_MultiplierY) + po->m_OffsetY;
			p.z = -po->m_ParallaxIndex;

			po->m_GameObject->GetTransform()->SetPosition(p);
		}
	}
}

RTTR_REGISTRATION
{
	rttr::registration::class_<ParalaxScrolling>("ParalaxScrolling")
		.constructor<>()
		(
			rttr::policy::ctor::as_raw_ptr
		)
		.property("AmountOfCopies", &ParalaxScrolling::m_AmountOfCopies);
}