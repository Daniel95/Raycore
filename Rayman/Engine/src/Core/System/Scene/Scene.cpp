#include "RayCorePCH.h"

#include "Core/System/Scene/Scene.h"

#include "Core/Application.h"
#include "Core/Gameplay/GameObject.h"
#include "Core/Gameplay/Component/BoxCollider2D.h"
#include "Core/Gameplay/Component/Camera.h"
#include "Core/Gameplay/Component/Transform.h"
#include "Core/Gameplay/Component/EditorCamera.h"
#include "Core/Gameplay/Component/SpriteRenderer.h"
#include "Core/System/InputSystem.h"
#include "Core/System/SceneSystem.h"
#include "Core/System/Manager/SystemManager.h"
#include "Core/Utilities/json/from_json.h"
#include "Core/Utilities/json/to_json.h"
#include "Core/Utilities/Math/SimpleMath.h"

#include <imgui.h>
#include <rttr/registration>

namespace Engine
{
    Scene::Scene(ullong a_ID, const std::string& a_Path)
        : Resource(a_ID, a_Path)
    {
        m_Name = a_Path;
        Replace(m_Name, GAME_SCENE_PATH, "");
        Replace(m_Name, ".txt", "");

        b2Vec2 gravity(.0f, -40.f);
        m_World = new b2World(gravity);

        m_World->SetContactListener(&m_MyContactListener);
    }

    Scene::~Scene()
    {
        Unload();
        _ASSERT(m_GameObjectsToUpdate.size() == 0);

        delete m_World;
    }

    void Scene::Init(Application& a_Application, bool a_CreateCamera)
    {
        m_Application = &a_Application;

        SceneSystem& sceneSystem = m_Application->GetSystemManager()->GetSystem<SceneSystem>();
        sceneSystem.AddSubInspectable("Scene Graph", &m_IsSceneGraphInspectable);
        sceneSystem.AddSubInspectable("Property Window", &m_IsPropertyWindowInspectable);

        if (a_CreateCamera)
        {
        #ifdef EDITOR
            CreateEditorCamera();
        #else
            CreateCamera();
        #endif // EDITOR
        }
    }

    void Scene::SetApplication(Application& a_Application)
    {
        m_Application = &a_Application;

        // Here temporarily, to make it work
        SceneSystem& sceneSystem = m_Application->GetSystemManager()->GetSystem<SceneSystem>();
        sceneSystem.AddSubInspectable("Scene Graph", &m_IsSceneGraphInspectable);
        sceneSystem.AddSubInspectable("Property Window", &m_IsPropertyWindowInspectable);
    }

    void Scene::CreateCamera()
    {
        if (!Camera::HasMainCamera())
        {
            Engine::GameObject& gameCamera = AddGameObject(DXS::Vector2(0, 0), DXS::Vector2(1, 1));
            gameCamera.AddComponent<Engine::Camera>();
        }
    }

    void Scene::Unload()
    {
        SceneSystem& sceneSystem = m_Application->GetSystemManager()->GetSystem<SceneSystem>();
        sceneSystem.RemoveSubInspectable("Scene Graph");
        sceneSystem.RemoveSubInspectable("Property Window");

        DestroyAllGameObjects();
    }

    void Scene::DestroyAllGameObjects()
    {
        for (GameObject* gameObject : m_GameObjectsToUpdate)
        {
            delete gameObject;
        }
        m_GameObjectsToUpdate.clear();

        for (GameObject* gameObject : m_GameObjectsToAdd)
        {
            delete gameObject;
        }
        m_GameObjectsToAdd.clear();

        for (GameObject* gameObject : m_GameObjectsToRemove)
        {
            delete gameObject;
        }
        m_GameObjectsToRemove.clear();
    }

    GameObject& Scene::AddGameObject()
    {
        GameObject* gameObject = new GameObject();
        gameObject->Init(*this);
        m_GameObjectsToAdd.push_back(gameObject);
        return *gameObject;
    }

    GameObject& Scene::AddGameObject(const DXS::Vector2& a_Position, const DXS::Vector2& a_Size)
    {
        GameObject& gameObject = AddGameObject();
        gameObject.GetTransform()->SetPosition(a_Position);
        gameObject.GetTransform()->SetScale(a_Size);
        return gameObject;
    }

    void Scene::RemoveGameObject(GameObject& a_GameObject)
    {
        _ASSERT(std::find(m_GameObjectsToRemove.begin(), m_GameObjectsToRemove.end(), &a_GameObject) == m_GameObjectsToRemove.end());
        m_GameObjectsToRemove.push_back(&a_GameObject);
    }

    void Scene::Update(float a_DeltaTime)
    {
        for (GameObject* gameObject : m_GameObjectsToAdd)
        {
            m_GameObjectsToUpdate.push_back(gameObject);
        }
        m_GameObjectsToAdd.clear();

    #ifndef EDITOR
        for (GameObject* gameObject : m_GameObjectsToUpdate)
        {
            gameObject->Update(a_DeltaTime);
        }
    #else 
        for (GameObject* gameObject : m_GameObjectsToUpdate)
        {
            if (gameObject->HasComponent<SpriteRenderer>())
            {
                gameObject->GetComponent<SpriteRenderer>()->Update(a_DeltaTime);
            }
        }

        EditorInteractions(a_DeltaTime);
    #endif

        for (GameObject* gameObjectToRemove : m_GameObjectsToRemove)
        {
            DestroyGameObjectImmediate(gameObjectToRemove);
        }
        m_GameObjectsToRemove.clear();
    }

    void Scene::FixedUpdate(float a_TimeStep)
    {
        for (GameObject* gameObject : m_GameObjectsToUpdate)
        {
            gameObject->FixedUpdate(a_TimeStep);
        }
        GetWorld()->Step(a_TimeStep, m_VelocityIterations, m_PositionIterations);
    }

    void Scene::Inspect()
    {
        if (m_IsSceneGraphInspectable)
        {
            if (ImGui::Begin("Scene Graph", &m_IsSceneGraphInspectable))
            {
                std::string sceneID = m_Name;
                sceneID.append("###Scene");

                ImGui::Unindent(ImGui::GetTreeNodeToLabelSpacing());
                bool treeOpened = ImGui::TreeNodeEx(sceneID.c_str(), ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_DefaultOpen);
                if (ImGui::IsItemClicked()) // Scene was clicked (needs to be checked before actually opening the tree)
                {
                    m_CurrentlySelectedSceneGraphItem = this;
                }

                if (treeOpened)
                {
                    for (unsigned int objectCounter = 0; objectCounter < m_GameObjectsToUpdate.size(); objectCounter++)
                    {
                        GameObject* gameObject = m_GameObjectsToUpdate[objectCounter];
                        rttr::instance objectInstance = gameObject;
                        rttr::type objectType = objectInstance.get_derived_type();
                        std::string objectName = objectType.get_name().to_string();

                        std::string imguiObjectName = objectName;
                        imguiObjectName.append("###");
                        imguiObjectName.append(objectName);
                        imguiObjectName += std::to_string(objectCounter);

                        bool subTreeOpened = ImGui::TreeNode(imguiObjectName.c_str());
                        if (ImGui::IsItemClicked()) // Game object was clicked (needs to be checked before actually opening the tree)
                        {
                            m_CurrentlySelectedSceneGraphItem = gameObject;
                        }

                        if (subTreeOpened)
                        {
                            std::vector<Component*> components = gameObject->GetComponents();
                            for (unsigned int componentCounter = 0; componentCounter < components.size(); componentCounter++)
                            {
                                Component* component = components[componentCounter];
                                rttr::instance componentInstance = component;
                                rttr::type componentType = componentInstance.get_derived_type();
                                std::string componentName = componentType.get_name().to_string();

                                std::string imguiComponentName = componentName;
                                imguiComponentName.append("###");
                                imguiComponentName.append(objectName); // GameObjectIdentifier
                                imguiComponentName.append(componentName); // ComponentIdentifier
                                imguiComponentName += std::to_string(componentCounter); // Not necessary? Because components are unique to game objects

                                // No need to store the result in a bool, since it doesn't go deeper than this.
                                ImGui::TreeNodeEx(imguiComponentName.c_str(), ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen);

                                if (ImGui::IsItemClicked()) // Component was clicked
                                {
                                    m_CurrentlySelectedSceneGraphItem = component;
                                }
                            }
                            ImGui::TreePop();
                        }
                    }

                    ImGui::TreePop();
                }
            }
            ImGui::End(); // End of Scene Graph
        }

        if (m_IsPropertyWindowInspectable)
        {
            if (ImGui::Begin("Property Window", &m_IsPropertyWindowInspectable))
            {
                if (m_CurrentlySelectedSceneGraphItem.is_valid())
                {
                    rttr::instance instanceObject = m_CurrentlySelectedSceneGraphItem;
                    rttr::type objectType = instanceObject.get_derived_type();
                    std::string objectName = objectType.get_name().to_string();
                    ImGui::Text(objectName.c_str());
                    ImGui::Separator();

                    ImGui::Columns(2);

                    rttr::filter_items filter = (rttr::filter_item) 31;
                    auto prop_list = instanceObject.get_derived_type().get_properties(filter);
                    for (rttr::property prop : prop_list)
                    {
                        rttr::variant prop_value = prop.get_value(instanceObject);
                        if (!prop_value)
                        {
                            continue;
                        }

                        ImGui::Text(prop.get_name().to_string().c_str());
                        ImGui::NextColumn();
                        RTTRToImGui(prop_value, objectName + prop.get_name().to_string()); // Will print the value
                        if (prop.get_value(instanceObject) != prop_value) // Checks if the value has changed
                        {
                            prop.set_value(instanceObject, prop_value); // Will change the actual value
                        }
                        ImGui::NextColumn();
                    }

                    ImGui::Columns();
                }
                else
                {
                    ImGui::Text("Select an object."); // Currently nothing is selected
                }
            }
            ImGui::End(); // End of Property WIndow
        }
    }

    Application* Scene::GetApplication() const
    {
        return m_Application;
    }

    const std::vector<GameObject*>& Scene::GetGameObjects()
    {
        return m_GameObjectsToUpdate;
    }

    void Scene::SetGameObjects(const std::vector<GameObject*>& a_GameObjects)
    {
        m_GameObjectsToUpdate = a_GameObjects;
    }

    void Scene::Deserialize(const std::string& a_json)
    {
    #ifdef EDITOR
        GameObject* objectWithCam = nullptr;
        if (Camera::HasMainCamera())
        {
            objectWithCam = Camera::GetMainCamera().GetGameObject();
            bool isEditorCam = objectWithCam->HasComponent<EditorCamera>();
            if (isEditorCam)
            {
                for (auto objectItr = m_GameObjectsToUpdate.begin(); objectItr != m_GameObjectsToUpdate.end(); ++objectItr)
                {
                    GameObject* object = *objectItr;
                    if (object == objectWithCam)
                    {
                        m_GameObjectsToUpdate.erase(objectItr);
                        break;
                    }
                }
            }
            else
            {
                objectWithCam = nullptr; // MainCam is not an editor cam, thus correctly created later
            }
        }
    #endif // EDITOR

        Unload();

        io::from_json(a_json, *this);

    #ifdef EDITOR
        if (objectWithCam != nullptr)
        {
            m_GameObjectsToUpdate.push_back(objectWithCam);
        }
    #endif // EDITOR

        for (GameObject* gameObject : m_GameObjectsToUpdate)
        {
            gameObject->Init(*this);

            for (Component* component : gameObject->GetComponents())
            {
                component->Init(gameObject);
            }

        #ifdef EDITOR
            if (gameObject->GetComponent<Camera>() != nullptr)
            {
                gameObject->Disable();
            }
        #endif // EDITOR
        }

    #ifdef EDITOR
        CreateEditorCamera()->Enable();
    #endif // EDITOR

        // Here temporarily, to make it work (preferably inside an init)
        SceneSystem& sceneSystem = m_Application->GetSystemManager()->GetSystem<SceneSystem>();
        sceneSystem.AddSubInspectable("Scene Graph", &m_IsSceneGraphInspectable);
        sceneSystem.AddSubInspectable("Property Window", &m_IsPropertyWindowInspectable);
    }

    std::string Scene::Serialize()
    {
        return io::to_json(*this);
    }

    void Scene::Save(const std::string& a_Path, const std::string& a_Name)
    {
        const std::string fullPath = a_Path + a_Name + ".txt";
        std::experimental::filesystem::path path{ fullPath }; //creates TestingFolder object on C:
        std::experimental::filesystem::create_directories(path.parent_path()); //add directories based on the object path (without this line it will not work)

    #ifdef EDITOR
        DestroyEditorCamera();

        GameObject* objectWithCam = nullptr;
        for (GameObject* gameObject : m_GameObjectsToUpdate)
        {
            if (gameObject->GetComponent<Camera>() != nullptr)
            {
                objectWithCam = gameObject;
                gameObject->Enable();
                break;
            }
        }
    #endif // EDITOR

        std::string jsonString = Serialize();

    #ifdef EDITOR
        if (objectWithCam != nullptr)
        {
            objectWithCam->Disable();
        }

        CreateEditorCamera();
    #endif // EDITOR

        std::ofstream ofs(path);
        ofs << jsonString;
        ofs.close();
    }

    void Scene::Load(const std::string& a_Path, const std::string& a_Name)
    {
        const std::string fullPath = a_Path + a_Name + ".txt";

        if (!std::experimental::filesystem::exists(fullPath))
        {
            LOG_ENGINE_ERROR("Scene does not exists! {0}", fullPath);
            _ASSERT(false);
        }

        std::ifstream stream(fullPath);
        std::string sceneJSON((std::istreambuf_iterator<char>(stream)),
                              std::istreambuf_iterator<char>());

        Deserialize(sceneJSON);
    }

    void Scene::SaveState()
    {
        _ASSERT(mc_MaxStateSaves > 0);

        while (m_CurrentStateIndex < m_States.size())
        {
            m_States.pop_back(); // Remove any undo's from stack if a change has been made
        }

    #ifdef EDITOR
        GameObject* objectWithCam = nullptr;
        if (Camera::HasMainCamera())
        {
            objectWithCam = Camera::GetMainCamera().GetGameObject();
            bool isEditorCam = objectWithCam->HasComponent<EditorCamera>();
            if (isEditorCam)
            {
                for (auto objectItr = m_GameObjectsToUpdate.begin(); objectItr != m_GameObjectsToUpdate.end(); ++objectItr)
                {
                    GameObject* object = *objectItr;
                    if (object == objectWithCam)
                    {
                        m_GameObjectsToUpdate.erase(objectItr);
                        break;
                    }
                }
            }
            else
            {
                objectWithCam = nullptr; // MainCam is not an editor cam, thus correctly created later
            }
        }
    #endif // EDITOR

        std::string serialized = Serialize();
        m_States.push_back(serialized);

    #ifdef EDITOR
        if (objectWithCam != nullptr)
        {
            m_GameObjectsToUpdate.push_back(objectWithCam);
        }
    #endif // EDITOR

        if (m_States.size() > mc_MaxStateSaves + 1)
        {
            LOG_ENGINE_ERROR("m_States size is over the m_UndoCount");
            _ASSERT(false);
        }
        else if (m_States.size() > mc_MaxStateSaves)
        {
            m_States.pop_front();
        }

        m_CurrentStateIndex = (int) m_States.size();

        LOG_ENGINE_INFO("m_CurrentStateIndex: {0}", m_CurrentStateIndex);
    }

    GameObject* Scene::CreateEditorCamera()
    {
        GameObject* cameraGameObject = nullptr;
        for (GameObject* gameObject : m_GameObjectsToUpdate)
        {
            if (gameObject->GetComponent<EditorCamera>() != nullptr)
            {
                cameraGameObject = gameObject;
                break;
            }
        }

        if (cameraGameObject == nullptr)
        {
            cameraGameObject = &AddGameObject();
            cameraGameObject->AddComponent<EditorCamera>();
        }

        return cameraGameObject;
    }

    void Scene::DestroyEditorCamera()
    {
        for (GameObject* gameObject : m_GameObjectsToAdd)
        {
            if (gameObject->GetComponent<EditorCamera>() != nullptr)
            {
                DestroyGameObjectImmediate(gameObject);
                break;
            }
        }

        for (GameObject* gameObject : m_GameObjectsToUpdate)
        {
            if (gameObject->GetComponent<EditorCamera>() != nullptr)
            {
                DestroyGameObjectImmediate(gameObject);
                break;
            }
        }
    }

    void Scene::DestroyGameObjectImmediate(GameObject* a_GameObject)
    {
        m_GameObjectsToAdd.erase(std::remove(m_GameObjectsToAdd.begin(), m_GameObjectsToAdd.end(), a_GameObject), m_GameObjectsToAdd.end());
        m_GameObjectsToUpdate.erase(std::remove(m_GameObjectsToUpdate.begin(), m_GameObjectsToUpdate.end(), a_GameObject), m_GameObjectsToUpdate.end());

        delete a_GameObject;
    }

    bool Scene::CanUndo()
    {
        return m_States.size() > 0 && m_CurrentStateIndex > 0;
    }

    bool Scene::CanRedo()
    {
        return m_States.size() > 0 && m_CurrentStateIndex < m_States.size() - 1;
    }

    void Scene::Undo()
    {
        if (CanUndo())
        {
            m_CurrentStateIndex--;
            std::string serialized = m_States.at(m_CurrentStateIndex);
            Deserialize(serialized);

            LOG_ENGINE_INFO("m_CurrentStateIndex: {0}", m_CurrentStateIndex);
        }
    }

    void Scene::Redo()
    {
        if (m_States.size() > 0
            && m_CurrentStateIndex < m_States.size() - 1)
        {
            m_CurrentStateIndex++;
            std::string serialized = m_States.at(m_CurrentStateIndex);
            Deserialize(serialized);

            LOG_ENGINE_INFO("m_CurrentStateIndex: {0}", m_CurrentStateIndex);
        }
    }

    b2World* Scene::GetWorld()
    {
        return m_World;
    }

    const std::string& Scene::GetName() const
    {
        return m_Name;
    }

    void Scene::SetName(const std::string& a_Name)
    {
        m_Name = a_Name;
    }

    void Scene::EditorInteractions(float a_DeltaTime)
    {
        Camera::GetMainCamera().GetGameObject()->Update(a_DeltaTime);

        Engine::InputSystem* inputSystem = &GetApplication()->GetSystemManager()->GetSystem<Engine::InputSystem>();
        if (inputSystem->GetKeyboardKey(KeyCode::ControlKey)
            && inputSystem->GetKeyboardKeyDown(KeyCode::Z))
        {
            LOG_ENGINE_INFO("ctrl-z");

            Undo();
        }

        if (inputSystem->GetKeyboardKey(KeyCode::ControlKey)
            && inputSystem->GetKeyboardKeyDown(KeyCode::Y))
        {
            LOG_ENGINE_INFO("ctrl-y");

            Redo();
        }
    }

    void Scene::RTTRToImGui(rttr::variant& a_Variant, std::string a_VariableName)
    {
        rttr::type variantType = a_Variant.get_type();
        bool valueHasChanged = false;
        bool valueDoneChanging = false;

        std::string imguiStringID = "##";
        imguiStringID.append(a_VariableName);
        imguiStringID.append("#");
        imguiStringID.append(variantType.get_name().to_string());

        ImGui::PushItemWidth(-0.1f); // Makes the next Input maximum width
        if (variantType == rttr::type::get<bool>())
        {
            imguiStringID.append("Boolean");

            bool variantValue = a_Variant.to_bool();
            valueHasChanged = ImGui::Checkbox(imguiStringID.c_str(), &variantValue);
            valueDoneChanging = valueHasChanged;
            if (valueHasChanged)
            {
                a_Variant = variantValue;
            }
        }
        else if (variantType == rttr::type::get<char>())
        {
            imguiStringID.append("Character");

            char variantValue[2] = {a_Variant.to_int8(), '\0'};
            valueHasChanged = ImGui::InputText(imguiStringID.c_str(), variantValue, 1);
            valueDoneChanging = valueHasChanged;

            a_Variant = variantValue[0];
        }
        else if (variantType == rttr::type::get<int8_t>())
        {
            imguiStringID.append("Byte");

            int8_t variantValue = a_Variant.to_int8();

            int smallStep = 1;
            int bigStep = 64;
            ImGuiInputTextFlags flags = ImGuiInputTextFlags_None;
            const char* format = (flags & ImGuiInputTextFlags_CharsHexadecimal) ? "%08X" : "%d";
            ImGui::InputScalar(imguiStringID.c_str(), ImGuiDataType_S8, &variantValue, &smallStep, &bigStep, format, flags);
            valueDoneChanging = ImGui::IsItemDeactivatedAfterEdit();

            a_Variant = variantValue;
        }
        else if (variantType == rttr::type::get<int16_t>())
        {
            imguiStringID.append("Short");

            int16_t variantValue = a_Variant.to_int16();

            int smallStep = 4;
            int bigStep = 256;
            ImGuiInputTextFlags flags = ImGuiInputTextFlags_None;
            const char* format = (flags & ImGuiInputTextFlags_CharsHexadecimal) ? "%08X" : "%d";
            ImGui::InputScalar(imguiStringID.c_str(), ImGuiDataType_S16, &variantValue, &smallStep, &bigStep, format, flags);
            valueDoneChanging = ImGui::IsItemDeactivatedAfterEdit();

            a_Variant = variantValue;
        }
        else if (variantType == rttr::type::get<int32_t>())
        {
            imguiStringID.append("Integer");

            int32_t variantValue = a_Variant.to_int32();

            int smallStep = 16;
            int bigStep = 1024;
            ImGuiInputTextFlags flags = ImGuiInputTextFlags_None;
            const char* format = (flags & ImGuiInputTextFlags_CharsHexadecimal) ? "%08X" : "%d";
            ImGui::InputScalar(imguiStringID.c_str(), ImGuiDataType_S32, &variantValue, &smallStep, &bigStep, format, flags);
            valueDoneChanging = ImGui::IsItemDeactivatedAfterEdit();

            a_Variant = variantValue;
        }
        else if (variantType == rttr::type::get<int64_t>())
        {
            imguiStringID.append("LongLong");

            int64_t variantValue = a_Variant.to_int64();

            int smallStep = 64;
            int bigStep = 4096;
            ImGuiInputTextFlags flags = ImGuiInputTextFlags_None;
            const char* format = (flags & ImGuiInputTextFlags_CharsHexadecimal) ? "%08X" : "%I64d";
            ImGui::InputScalar(imguiStringID.c_str(), ImGuiDataType_S64, &variantValue, &smallStep, &bigStep, format, flags);
            valueDoneChanging = ImGui::IsItemDeactivatedAfterEdit();

            a_Variant = variantValue;
        }
        else if (variantType == rttr::type::get<uint8_t>())
        {
            imguiStringID.append("UnsignedByte");

            uint8_t variantValue = a_Variant.to_uint8();

            int smallStep = 1;
            int bigStep = 64;
            ImGuiInputTextFlags flags = ImGuiInputTextFlags_None;
            const char* format = (flags & ImGuiInputTextFlags_CharsHexadecimal) ? "%08X" : "%u";
            ImGui::InputScalar(imguiStringID.c_str(), ImGuiDataType_U8, &variantValue, &smallStep, &bigStep, format, flags);
            valueDoneChanging = ImGui::IsItemDeactivatedAfterEdit();

            a_Variant = variantValue;
        }
        else if (variantType == rttr::type::get<uint16_t>())
        {
            imguiStringID.append("UnsignedShort");

            uint16_t variantValue = a_Variant.to_uint16();

            int smallStep = 4;
            int bigStep = 256;
            ImGuiInputTextFlags flags = ImGuiInputTextFlags_None;
            const char* format = (flags & ImGuiInputTextFlags_CharsHexadecimal) ? "%08X" : "%u";
            ImGui::InputScalar(imguiStringID.c_str(), ImGuiDataType_U16, &variantValue, &smallStep, &bigStep, format, flags);
            valueDoneChanging = ImGui::IsItemDeactivatedAfterEdit();

            a_Variant = variantValue;
        }
        else if (variantType == rttr::type::get<uint32_t>())
        {
            imguiStringID.append("UnsignedInteger");

            uint32_t variantValue = a_Variant.to_uint32();

            int smallStep = 16;
            int bigStep = 1024;
            ImGuiInputTextFlags flags = ImGuiInputTextFlags_None;
            const char* format = (flags & ImGuiInputTextFlags_CharsHexadecimal) ? "%08X" : "%u";
            ImGui::InputScalar(imguiStringID.c_str(), ImGuiDataType_U32, &variantValue, &smallStep, &bigStep, format, flags);
            valueDoneChanging = ImGui::IsItemDeactivatedAfterEdit();

            a_Variant = variantValue;
        }
        else if (variantType == rttr::type::get<uint64_t>())
        {
            imguiStringID.append("UnsignedLongLong");

            uint64_t variantValue = a_Variant.to_uint64();

            int smallStep = 64;
            int bigStep = 4096;
            ImGuiInputTextFlags flags = ImGuiInputTextFlags_None;
            const char* format = (flags & ImGuiInputTextFlags_CharsHexadecimal) ? "%08X" : "%I64u";
            ImGui::InputScalar(imguiStringID.c_str(), ImGuiDataType_U64, &variantValue, &smallStep, &bigStep, format, flags);
            valueDoneChanging = ImGui::IsItemDeactivatedAfterEdit();

            a_Variant = variantValue;
        }
        else if (variantType == rttr::type::get<float>())
        {
            imguiStringID.append("FloatingPoint");

            float variantValue = a_Variant.to_float();

            float smallStep = 16.f;
            float bigStep = 1024.f;
            ImGuiInputTextFlags flags = ImGuiInputTextFlags_None;
            flags |= ImGuiInputTextFlags_CharsScientific;
            const char* format = "%.3f";
            ImGui::InputScalar(imguiStringID.c_str(), ImGuiDataType_Float, &variantValue, &smallStep, &bigStep, format, flags);
            valueDoneChanging = ImGui::IsItemDeactivatedAfterEdit();

            a_Variant = variantValue;
        }
        else if (variantType == rttr::type::get<double>())
        {
            imguiStringID.append("DoublePrecision");

            double variantValue = a_Variant.to_double();

            double smallStep = 64.0;
            double bigStep = 4096.0;
            ImGuiInputTextFlags flags = ImGuiInputTextFlags_None;
            flags |= ImGuiInputTextFlags_CharsScientific;
            const char* format = "%.6f";
            ImGui::InputScalar(imguiStringID.c_str(), ImGuiDataType_Double, &variantValue, &smallStep, &bigStep, format, flags);
            valueDoneChanging = ImGui::IsItemDeactivatedAfterEdit();

            a_Variant = variantValue;
        }
        else if (variantType == rttr::type::get<std::string>())
        {
            imguiStringID.append("String");

            std::string variantValue = a_Variant.to_string();
            ImGui::InputText(imguiStringID.c_str(), variantValue);
            valueDoneChanging = ImGui::IsItemDeactivatedAfterEdit();

            a_Variant = variantValue;
        }
        else if (variantType.is_enumeration())
        {
            imguiStringID.append("Enumeration");

            rttr::enumeration enumType = variantType.get_enumeration();
            auto enumValues = enumType.get_names();
            std::string variantValue = enumType.value_to_name(a_Variant).to_string();

            if (ImGui::BeginCombo(imguiStringID.c_str(), variantValue.c_str()))
            {
                for (auto enumItr : enumValues)
                {
                    std::string enumValue = enumItr.to_string();
                    bool isSelected = variantValue == enumValue;
                    if (ImGui::Selectable(enumValue.c_str(), isSelected))
                    {
                        variantValue = enumValue;
                        valueDoneChanging = true;
                    }

                    if (isSelected)
                    {
                        ImGui::SetItemDefaultFocus();
                    }
                }

                ImGui::EndCombo();

                a_Variant = enumType.name_to_value(variantValue);
            }
        }
        else if (variantType.is_sequential_container())
        {
            imguiStringID.append("Vector");
            // Do something for array's/vectors/lists

            rttr::variant_sequential_view seqList = a_Variant.create_sequential_view();
            rttr::type variantItemType = seqList.get_value_type();
            rttr::type variantItemRawType = variantItemType.get_raw_type();
            std::string variantRawTypeName = variantItemRawType.get_name().to_string();

            if (ImGui::CollapsingHeader(variantRawTypeName.c_str()))
            {
                if (variantItemType.is_associative_container() || variantItemType.is_sequential_container())
                {
                    ImGui::TextDisabled("%s inside a list is not supported", variantItemType.get_name().to_string().c_str());
                }
                else
                {
                    std::string baseSeqVariableName = a_VariableName;
                    baseSeqVariableName.append(variantType.get_name().to_string());
                    baseSeqVariableName.append("ListItem");

                    ImGuiStyle& style = ImGui::GetStyle();
                    const float spacing = style.ItemInnerSpacing.x;
                    const float frameHeight = ImGui::GetFrameHeight();
                    const ImVec2 buttonSize = ImVec2(frameHeight, frameHeight);
                    const float buttonWidth = frameHeight + spacing;
                    const float deleteButtonPosition = std::max(1.0f, ImGui::GetWindowContentRegionMax().x - (buttonWidth + ImGui::GetColumnOffset()));
                    const ImVec2 backup_frame_padding = style.FramePadding;
                    style.FramePadding.x = style.FramePadding.y;

                    // Loop all the items
                    unsigned int itemCounter = 0;
                    for (auto seqIterator = seqList.begin(); seqIterator != seqList.end(); /* Counting up is done inside the loop. */)
                    {
                        rttr::variant seqListItemVariant = *seqIterator;
                        std::string seqVariableName = baseSeqVariableName + std::to_string(itemCounter++);
                        rttr::instance instanceObject = seqListItemVariant;
                        std::string derivedVariantTypeName = instanceObject.get_wrapped_instance().get_derived_type().get_name().to_string();

                        ImGui::PushID(seqVariableName.c_str());
                        ImGui::Text(derivedVariantTypeName.c_str());

                        if (instanceObject.get_wrapped_instance().get_derived_type() != rttr::type::get<Engine::Transform>()) // Transform is the only exception (cannot ever be deleted)
                        {
                            ImGui::SameLine(deleteButtonPosition, spacing);

                            if (ImGui::Button("X", buttonSize))
                            {
                                seqIterator = seqList.erase(seqIterator);
                                rttr::type seqListItemType = seqListItemVariant.get_type().get_wrapped_type();
                                if (seqListItemType.is_pointer())
                                {
                                    seqListItemType.destroy(seqListItemVariant);
                                    valueDoneChanging = true;
                                }
                            }
                            else
                            {
                                ++seqIterator;
                            }
                        }
                        else
                        {
                            ++seqIterator;
                        }

                        ImGui::PopID();
                    }

                    style.FramePadding = backup_frame_padding; // Reset/restore framepadding

                    std::string newItemLabel = "Add new ";
                    newItemLabel.append(variantRawTypeName);
                    const float contentButtonWidth = std::max(1.0f, ImGui::GetWindowContentRegionMax().x - ImGui::GetColumnOffset());
                    const ImVec2 maxWidthButtonSize = ImVec2(contentButtonWidth, frameHeight);

                    if (ImGui::Button(newItemLabel.c_str(), maxWidthButtonSize))
                    {
                        ImGui::OpenPopup("Add New Object"); // Add new item
                    }

                    if (ImGui::BeginPopupModal("Add New Object", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
                    {
                        imguiStringID.append("NewItem");
                        static std::string newItemName = "New Item";

                        auto derivedTypes = variantItemRawType.get_derived_classes();

                        if (derivedTypes.size() == 0) // If it doesn't have any implementations, just get the default one
                        {
                            newItemName = variantItemRawType.get_name().to_string();
                            ImGui::Text("Adding \"%s\"", newItemName.c_str());
                        }
                        else
                        {
                            ImGui::PushItemWidth(-0.1f);
                            if (ImGui::BeginCombo(imguiStringID.c_str(), newItemName.c_str()))
                            {
                                for (auto type : derivedTypes)
                                {
                                    std::string typeValue = type.get_name().to_string();
                                    bool isSelected = newItemName == typeValue;
                                    if (ImGui::Selectable(typeValue.c_str(), isSelected))
                                    {
                                        newItemName = typeValue;
                                    }

                                    if (isSelected)
                                    {
                                        ImGui::SetItemDefaultFocus();
                                    }
                                }

                                ImGui::EndCombo();
                            }
                        }

                        ImGui::NewLine();
                        ImGui::Separator();
                        const float popupButtonWidth = 120.f;
                        const float popupButtonPosition = std::max(1.0f, ImGui::GetWindowContentRegionMax().x - ((2.f * (popupButtonWidth + spacing)) + ImGui::GetColumnOffset()));
                        ImGui::NewLine();
                        ImGui::SameLine(popupButtonPosition, spacing);

                        bool disableAdd = newItemName == "New Item";
                        if (disableAdd)
                        {
                            ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);
                            ImGui::Button("Add", ImVec2(popupButtonWidth, 0));
                            ImGui::PopStyleVar();
                        }
                        else if (ImGui::Button("Add", ImVec2(popupButtonWidth, 0)))
                        {
                            size_t lastIndex = seqList.get_size();
                            seqList.set_size(lastIndex + 1);

                            rttr::variant var_tmp = seqList.get_value(lastIndex);
                            rttr::variant wrapped_var = var_tmp.extract_wrapped_value();
                            const rttr::type temp_type = wrapped_var.get_type();

                            rttr::type objectType = rttr::type::get_by_name(newItemName);
                            rttr::variant objectVariant = objectType.create();
                            objectVariant.convert(temp_type);

                            seqList.set_value(lastIndex, objectVariant);
                            // Do init or something

                            if (variantItemRawType == rttr::type::get<GameObject>())
                            {
                                GameObject* go = objectVariant.get_value<GameObject*>();
                                go->Init(*this);
                                m_GameObjectsToUpdate.push_back(go); // Or use ToAdd list?
                            }
                            else if (variantItemRawType == rttr::type::get<Component>())
                            {
                                GameObject* go = m_CurrentlySelectedSceneGraphItem.get_value<GameObject*>();
                                Component* comp = objectVariant.get_value<Component*>();
                                comp->Init(go);
                                go->AddRawComponent(comp);

                                if (newItemName == rttr::type::get<BoxCollider2D>().get_name().to_string())
                                {
                                    objectVariant.get_value<BoxCollider2D*>()->SetCollisionType(CollisionType::Platform);
                                }
                            }

                            valueDoneChanging = true;
                            newItemName = "New Item";
                            ImGui::CloseCurrentPopup();
                        }

                        ImGui::SetItemDefaultFocus();
                        ImGui::SameLine(0, spacing);

                        if (ImGui::Button("Cancel", ImVec2(popupButtonWidth, 0)))
                        {
                            ImGui::CloseCurrentPopup();
                        }

                        ImGui::EndPopup();
                    }
                }
            }
        }
        else if (variantType.is_associative_container())
        {
            imguiStringID.append("Map");
            ImGui::TextDisabled("%s not supported", variantType.get_name().to_string().c_str());
            // Implement map (like) support?
        }
        else if (variantType == rttr::type::get<DXS::Vector2>())
        {
            imguiStringID.append("Vector2");

            DXS::Vector2 variantValue = a_Variant.convert<DXS::Vector2>();
            float rawValues[2] = {variantValue.x, variantValue.y};

            ImGui::PushItemWidth(-0.1f);
            valueHasChanged = ImGui::DragFloat2(imguiStringID.c_str(), rawValues);
            valueDoneChanging = ImGui::IsItemDeactivatedAfterEdit();
            valueHasChanged |= valueDoneChanging;

            variantValue = {rawValues[0], rawValues[1]};
            a_Variant = variantValue;
        }
        else if (variantType == rttr::type::get<DXS::Vector3>())
        {
            imguiStringID.append("Vector3");

            DXS::Vector3 variantValue = a_Variant.convert<DXS::Vector3>();
            float rawValues[3] = {variantValue.x, variantValue.y, variantValue.z};

            ImGui::PushItemWidth(-0.1f);
            valueHasChanged = ImGui::DragFloat3(imguiStringID.c_str(), rawValues);
            valueDoneChanging = ImGui::IsItemDeactivatedAfterEdit();
            valueHasChanged |= valueDoneChanging;

            variantValue = {rawValues[0], rawValues[1], rawValues[2]};
            a_Variant = variantValue;
        }
        else if (variantType == rttr::type::get<DXS::Quaternion>())
        {
            imguiStringID.append("Quaternion");

            DXS::Quaternion variantValue = a_Variant.convert<DXS::Quaternion>();
            float rawValues[3] = {variantValue.x, variantValue.y, variantValue.z}; // The w value needs to be 1 always

            ImGui::PushItemWidth(-0.1f);
            valueHasChanged = ImGui::DragFloat3(imguiStringID.c_str(), rawValues, (1.f / 90.f), 0.f, 1.f);
            valueDoneChanging = ImGui::IsItemDeactivatedAfterEdit();
            valueHasChanged |= valueDoneChanging;

            /* Attempt to fix/improve quat's
            ImGui::PushItemWidth(-0.1f);

            const int numComponentsToExpose = 3;
            const float fullWidth = ImGui::CalcItemWidth();
            const ImGuiStyle& style = ImGui::GetStyle();
            const float spacing = style.ItemInnerSpacing.x;
            const float itemWidth = std::max(1.0f, (float) (int) ((fullWidth - (spacing) * (numComponentsToExpose - 1)) / (float) numComponentsToExpose));
            const float lastItemWidth = std::max(1.0f, (float) (int) (fullWidth - (itemWidth + spacing) * (numComponentsToExpose - 1)));

            ImGui::PopItemWidth();
            ImGui::BeginGroup();
            ImGui::PushID(imguiStringID.c_str());

            for (int i = 0; i < numComponentsToExpose; i++)
            {
                if (i > 0)
                {
                    ImGui::SameLine(0, spacing);
                }

                ImGui::PushID(i);
                ImGui::PushItemWidth(i + 1 == numComponentsToExpose ? lastItemWidth : itemWidth);
                valueHasChanged |= ImGui::SliderAngle("", &rawValues[i]);
                valueHasChanged |= ImGui::IsItemDeactivatedAfterEdit();
                ImGui::PopItemWidth();
                ImGui::PopID();
            }

            ImGui::PopID();
            ImGui::EndGroup();*/

            variantValue = {rawValues[0], rawValues[1], rawValues[2], variantValue.w};
            a_Variant = variantValue;
        }
        else if (variantType == rttr::type::get<DXS::Plane>())
        {
            imguiStringID.append("Plane");

            DXS::Plane variantValue = a_Variant.convert<DXS::Plane>();
            float rawValues[4] = {variantValue.x, variantValue.y, variantValue.z, variantValue.w};

            ImGui::PushItemWidth(-0.1f);
            valueHasChanged = ImGui::DragFloat4(imguiStringID.c_str(), rawValues);
            valueDoneChanging = ImGui::IsItemDeactivatedAfterEdit();
            valueHasChanged |= valueDoneChanging;

            variantValue = {rawValues[0], rawValues[1], rawValues[2], rawValues[3]};
            a_Variant = variantValue;
        }
        else
        {
            imguiStringID.append("Class");
            ImGui::TextDisabled("%s not supported", variantType.get_name().to_string().c_str());
            // Implement custom class support?
        }

        if (valueHasChanged && m_CurrentlySelectedSceneGraphItem.get_type() == rttr::type::get<Component*>())
        {
            Inspectable* inspectableComponent = m_CurrentlySelectedSceneGraphItem.get_value<Inspectable*>(); // Every component is (/should be) an Inspectable.
            inspectableComponent->Inspect(); // Only Components need to run this function
        }

        if (valueDoneChanging)
        {
            SaveState();
        }
    }

    RTTR_REGISTRATION
    {
        rttr::registration::class_<Scene>("Scene")
            .constructor<ullong, const std::string&>()
            (
                rttr::policy::ctor::as_raw_ptr
            )
            .property("Name", &Scene::GetName, &Scene::SetName)
            .property("GameObjects", &Scene::GetGameObjects, &Scene::SetGameObjects)
        ;
    }
}