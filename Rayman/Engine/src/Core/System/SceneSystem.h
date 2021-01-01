#pragma once
#include "Core/System/Manager/ISystem.h"

#include "Core/Utilities/Inspectable.h"

#include <string>
#include <vector>

namespace Engine 
{
    class Application;
    class GameObject;
    class Scene;
    class SystemManager;

    class SceneSystem : public ISystem, public Inspectable, public SystemRegistry<SceneSystem>
    {
        RTTR_ENABLE(ISystem, Inspectable);

    public:
        SceneSystem(SystemManager& a_SystemManager, Application& a_Application);
        ~SceneSystem();

        void Initialize();
        void Update(float a_DeltaTime);
        void FixedUpdate(float a_TimeStep);
        void Terminate();

        void Inspect() override;

        void NewScene();
        void LoadScene(const std::string& a_SceneName);
        void ReloadScene();
        Scene* GetActiveScene();

        void AddSubInspectable(std::string a_InspectableName, bool* a_IsInspectableEnabled);
        void RemoveSubInspectable(std::string a_InspectableName);
        
    private:
        void LoadSceneImmediate(const std::string& a_SceneName);

    private:
        Application* m_Application;
        std::string m_SceneNameToLoad;

        Scene* m_ActiveScene = nullptr;
        bool m_InspectLoadedScenes = false;


    };
}