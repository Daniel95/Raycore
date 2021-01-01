#pragma once
#include "Core/Gameplay/Component/Component.h"

#include <DirectXMath.h>
#include "Core/Utilities/Math/SimpleMath.h"

#include <rttr/registration_friend>

namespace Engine
{
	class Camera : public Component
	{
		RTTR_ENABLE(Component, Inspectable);
		RTTR_REGISTRATION_FRIEND;

	public:
		Camera();
		virtual ~Camera();

		virtual void Init(GameObject* a_GameObject) override;
		virtual void Update(float a_DeltaTime) override;
        void Inspect() override;

		void SetMainCamera();
		void SetBounds(const DXS::Vector2& a_Bounds);
		void SetRenderDistance(const float& a_NearZ, const float& a_FarZ);
		void SetOrthographicProjection(const int& a_Width, const int& a_Height);

		DXS::Matrix GetProjectionMatrix();
		DXS::Matrix GetInverseProjectionMatrix();
		DXS::Matrix GetViewMatrix();
		DXS::Matrix GetInverseViewMatrix();

		void LookAt(const DXS::Vector3& a_Target, const DXS::Vector3& a_Up);

		static Camera& GetMainCamera();
		static bool HasMainCamera();

	protected:
		static Camera* ms_MainCamera;

        virtual void OnEnable() override;
        virtual void OnDisable() override;

	private:
		void UpdateProjectionMatrix();
		void UpdateViewMatrix();

		// This data must be aligned otherwise the SSE intrinsics fail and throw exceptions.
		__declspec(align(16)) struct AlignedData
		{
			// World-space position of the camera.
			DirectX::XMVECTOR m_Translation;
			// World-space rotation of the camera. This is an QUATERNION!
			DirectX::XMVECTOR m_Rotation;

			DirectX::XMMATRIX m_ViewMatrix, m_InverseViewMatrix;
			DirectX::XMMATRIX m_ProjectionMatrix, m_InverseProjectionMatrix;
		};
		AlignedData* m_Data = nullptr;

		int m_Width = 1280;
		int m_Height = 720;
		float m_NearZ = 0.1f;
		float m_FarZ = 100.0f;
		DXS::Vector2 m_Bounds = DXS::Vector2(30.f, 20.f);

		bool m_DirtyProjection = true;
		bool m_DirtyView = true;

	};
}