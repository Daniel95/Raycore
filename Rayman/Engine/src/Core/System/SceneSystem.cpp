#include "RayCorePCH.h"

#include "Core/System/SceneSystem.h"

#include "Core/Application.h"
#include "Core/Gameplay/GameObject.h"
#include "Core/Gameplay/Component/BoxCollider2D.h"
#include "Core/Gameplay/Component/SpriteRenderer.h"
#include "Core/System/ResourceSystem.h"
#include "Core/System/Manager/ISystem.h"
#include "Core/System/Manager/SystemManager.h"
#include "Core/System/Scene/Scene.h"
#include "Core/Utilities/Log.h"

#include <imgui.h>

namespace Engine 
{
    SceneSystem::SceneSystem(SystemManager& a_SystemManager, Application& a_Application)
        : ISystem(a_SystemManager)
    {
        m_Application = &a_Application;
        m_SubInspectables.push_back(SubInspectable("Loaded Scenes", &m_InspectLoadedScenes));
    }

    SceneSystem::~SceneSystem()
    {
        if (m_ActiveScene != nullptr)
        {
            delete m_ActiveScene;
        }
    }

    void SceneSystem::Initialize()
    {
    }

    void SceneSystem::Update(float a_DeltaTime)
    {
        if (m_SceneNameToLoad != "")
        {
            LoadSceneImmediate(m_SceneNameToLoad);
            m_SceneNameToLoad = "";
        }

        if (m_ActiveScene != nullptr)
        {
            m_ActiveScene->Update(a_DeltaTime);
        }
    }

    void SceneSystem::FixedUpdate(float a_TimeStep)
    {
        if (m_SceneNameToLoad == "")
        {
            if (m_ActiveScene != nullptr)
            {
                m_ActiveScene->FixedUpdate(a_TimeStep);
            }
        }
    }

    void SceneSystem::Terminate()
    {
    }

    void SceneSystem::Inspect()
    {
        if (m_InspectLoadedScenes)
        {
            if (ImGui::Begin("Loaded Scenes", &m_InspectLoadedScenes))
            {
                ImGui::Text("WIP, please try next version.");
                ImGui::Text("Next version will feature a list of scenes.\nThe current active scene will be highlighted.");

                // Loop through the every scene that is in the list
            }
            ImGui::End(); // End of Loaded Scenes
        }

        m_ActiveScene->Inspect();
    }

    void SceneSystem::NewScene()
    {
        if (m_ActiveScene != nullptr)
        {
            std::string oldScenePath = GAME_SCENE_PATH + m_ActiveScene->GetName() + ".txt";
            m_SystemManager.GetSystem<ResourceSystem>().UnloadResource<Scene>(oldScenePath);
        }

        std::string newScenePath = GAME_SCENE_PATH + "NewScene.txt";
        m_ActiveScene = m_SystemManager.GetSystem<ResourceSystem>().LoadResource<Scene>(newScenePath);
        m_ActiveScene->Init(*m_Application, true);
    }

    void SceneSystem::LoadScene(const std::string& a_SceneName)
    {
        m_SceneNameToLoad = a_SceneName;
    }

    void SceneSystem::ReloadScene()
    {
        _ASSERT(m_ActiveScene != nullptr);

        m_SceneNameToLoad = m_ActiveScene->GetName();
    }

    Scene* SceneSystem::GetActiveScene()
    {
        return m_ActiveScene;
    }

    void SceneSystem::AddSubInspectable(std::string a_InspectableName, bool* a_IsInspectableEnabled)
    {
        m_SubInspectables.push_back(SubInspectable(a_InspectableName, a_IsInspectableEnabled));
    }

    void SceneSystem::RemoveSubInspectable(std::string a_InspectableName)
    {
        for (auto inspectableIterator = m_SubInspectables.begin(); inspectableIterator != m_SubInspectables.end(); ++inspectableIterator)
        {
            std::string inspectableName = (*inspectableIterator).GetName();
            if (inspectableName == a_InspectableName)
            {
                m_SubInspectables.erase(inspectableIterator);
                break;
            }
        }
    }

    void SceneSystem::LoadSceneImmediate(const std::string& a_SceneName)
    {
        if (m_ActiveScene != nullptr)
        {
            std::string oldScenePath = GAME_SCENE_PATH + m_ActiveScene->GetName() + ".txt";
            m_SystemManager.GetSystem<ResourceSystem>().UnloadResource<Scene>(oldScenePath);
        }

        std::string newScenePath = GAME_SCENE_PATH + a_SceneName + ".txt";
        m_ActiveScene = m_SystemManager.GetSystem<ResourceSystem>().LoadResource<Scene>(newScenePath);
        m_ActiveScene->Init(*m_Application);
        m_ActiveScene->Load(GAME_SCENE_PATH, a_SceneName);
    }
}
