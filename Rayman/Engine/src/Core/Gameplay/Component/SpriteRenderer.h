#pragma once

#include "Core/Gameplay/Component/Component.h"

#include <rttr/registration_friend>

namespace Engine
{
    class GameObject;
	class Texture;
	class Material;
    struct DrawData;
		
	class SpriteRenderer : public Component
    {
        RTTR_ENABLE(Component, Inspectable);
		RTTR_REGISTRATION_FRIEND;

    public:
        SpriteRenderer();
        virtual ~SpriteRenderer();
        virtual void Init(GameObject* a_GameObject) override;
        virtual void Update(float a_DeltaTime) override;

		virtual void OnEnable() override;
		virtual void OnDisable() override;

        void Inspect() override;

		//Sets the render order of the sprite.
		void SetLayer(int a_Layer);
		int GetLayer();
		//Set sprite material.
		void SetMaterial(Material& a_Material);
		//Set sprite texture.
		void SetTexture(const std::string& a_TexturePath);

    private:
        DrawData* m_DrawData = nullptr;

		//Sprite data.
		int m_Layer = 0;
		std::string m_TextureName = "";
    };
}