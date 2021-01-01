#pragma once

#include "Core/System/EventSystem.h"
#include "Core/System/Resource/Resource.h"
#include "Core/Gameplay/Component/ContactListener.h"
#include "Core/Gameplay/Component/Component.h"
#include "Core/Gameplay/Component/Transform.h"
#include "Core/Utilities/Defines.h"
#include "Core/Utilities/Inspectable.h"

#include <Box2D/Box2D.h>
#include <rttr/variant.h>

#include <deque>
#include <string>
#include <vector>

namespace DirectX
{
    namespace SimpleMath
    {
        struct Vector2;
    }
}

namespace Engine 
{
    class Application;
    class GameObject;

	class Scene : public Resource, public Inspectable
	{
        RTTR_ENABLE(Resource, Inspectable);

	public:
		Scene(ullong a_ID, const std::string& a_Path);
        ~Scene();

        void Init(Application& a_Application, bool a_CreateCamera = false);
        void SetApplication(Application& a_Application);
        void CreateCamera();
        void DestroyAllGameObjects();
        GameObject& AddGameObject();
        GameObject& AddGameObject(const DirectX::SimpleMath::Vector2 & a_Position, const DirectX::SimpleMath::Vector2 & a_Size);
        void RemoveGameObject(GameObject& a_GameObject);
        void Update(float a_DeltaTime);
        void FixedUpdate(float a_TimeStep);
        void Inspect() override; 
        Application* GetApplication() const;
        const std::vector<GameObject*> & GetGameObjects();
        void SetGameObjects(const std::vector<GameObject*> & a_GameObjects);
        void Deserialize(const std::string& a_Path);
        std::string Serialize();
        void Save(const std::string& a_Path, const std::string& a_Name);
		void Load(const std::string& a_Path, const std::string& a_Name);
        void SaveState();
        GameObject* CreateEditorCamera();
        void DestroyEditorCamera();
        void DestroyGameObjectImmediate(GameObject* a_GameObject);
        bool CanUndo();
        bool CanRedo();
        void Undo();
        void Redo();
        b2World* GetWorld();
        const std::string& GetName() const;
        void SetName(const std::string& a_Name);
        void EditorInteractions(float a_DeltaTime);

    private:
        Application* m_Application;
        std::vector<GameObject*> m_GameObjectsToUpdate;
        std::vector<GameObject*> m_GameObjectsToAdd;
        std::vector<GameObject*> m_GameObjectsToRemove;
        std::deque<std::string> m_States;
        std::string m_Name;
        const int mc_MaxStateSaves = 20;
        int m_CurrentStateIndex = 0;
        Engine::EventSystem::EventHandle m_KeyEventHandle;
        b2World* m_World;
        ContactListener m_MyContactListener;

        bool m_IsSceneGraphInspectable = true;
        bool m_IsPropertyWindowInspectable = true;
        rttr::variant m_CurrentlySelectedSceneGraphItem;

        int32 m_VelocityIterations = 5;
        int32 m_PositionIterations = 1;
        void RTTRToImGui(rttr::variant& a_Variant, std::string a_VariableName);
        void Unload();

	};
}