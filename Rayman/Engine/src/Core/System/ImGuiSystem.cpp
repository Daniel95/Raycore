#include "RayCorePCH.h"

#include "Core/System/ImGuiSystem.h"

#include "Core/System/SceneSystem.h"
#include "Core/System/Manager/SystemManager.h"
#include "Core/System/Scene/Scene.h"
#include "Core/Utilities/Inspectable.h"
#include "Core/Utilities/Log.h"

#include "Core/System/ImGuiRenderer/DX12ImGuiRenderer.h"

using ImGuiRenderer = Engine::DX12ImGuiRenderer;

namespace Engine
{
    ImGuiSystem::ImGuiSystem(SystemManager& a_SystemManager)
        : ISystem(a_SystemManager)
    {
        m_ImGuiRenderer = new ImGuiRenderer(); // Is aliased to the right Renderer (see top)
        //m_SubInspectables.push_back(SubInspectable("", new bool)); // Serves as an example

    #if EDITOR
        m_IsEnabled = true;
    #else
        m_IsEnabled = false;
    #endif // EDITOR
    }

    ImGuiSystem::~ImGuiSystem()
    {
        delete m_ImGuiRenderer;
    }

    void ImGuiSystem::Initialize()
    {
        m_ImGuiRenderer->Init();
    }

    void ImGuiSystem::Update(float a_DeltaTime)
    {
        a_DeltaTime;
        m_ImGuiRenderer->Update();
    }

    void ImGuiSystem::Terminate()
    {
        m_ImGuiRenderer->Terminate();
    }

    void ImGuiSystem::Inspect()
    {
        if (ImGui::BeginMainMenuBar())
        {
            SceneSystem& sceneSystem = m_SystemManager.GetSystem<SceneSystem>();
            Scene* currentScene = sceneSystem.GetActiveScene();

            bool openLevelPopup = false;
            bool saveLevelPopup = false;

            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("New Level"))
                {
                    sceneSystem.NewScene();
                }

                if (ImGui::MenuItem("Open Level"))
                {
                    openLevelPopup = true;
                }

                if (ImGui::MenuItem("Save Level", "", nullptr, currentScene != nullptr))
                {
                    currentScene->Save(GAME_SCENE_PATH, currentScene->GetName());
                }

                if (ImGui::MenuItem("Save Level as...", "", nullptr, currentScene != nullptr))
                {
                    saveLevelPopup = true;
                }

                ImGui::Separator();

                if (ImGui::MenuItem("Undo", "", nullptr, currentScene->CanUndo())) // Enable or disable based on if anything has been done (or not everything has been undone)
                {
                    currentScene->Undo();
                }

                if (ImGui::MenuItem("Redo", "", nullptr, currentScene->CanRedo())) // Enable or disable based on if undo's have been done
                {
                    currentScene->Redo();
                }

                ImGui::Separator();

                if (ImGui::MenuItem("Exit Game"))
                {
                    DX12Graphics::Get().Quit(0);
                }

                ImGui::EndMenu();
            }

            /// Popup dialogs
            // Open level dialog
            if (openLevelPopup)
            {
                ImGui::OpenPopup("Open a level");
            }

            if (ImGui::BeginPopupModal("Open a level", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
            {
                ImGui::Text("Type the level you want to open:");

                ImGui::PushItemWidth(-0.1f);
                static std::string s_LevelToOpen = "";
                ImGui::InputText("###DialogOpenLevelInput", s_LevelToOpen);

                if (s_LevelToOpen == "")
                {
                    ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);
                    ImGui::Button("Open");
                    ImGui::PopStyleVar();
                }
                else if (ImGui::Button("Open"))
                {
                    sceneSystem.LoadScene(s_LevelToOpen);
                    s_LevelToOpen = "";
                    ImGui::CloseCurrentPopup();
                }

                ImGui::SetItemDefaultFocus();
                ImGui::SameLine();

                if (ImGui::Button("Cancel"))
                {
                    s_LevelToOpen = "";
                    ImGui::CloseCurrentPopup();
                }

                ImGui::EndPopup();
            }

            // Save level dialog
            if (saveLevelPopup)
            {
                ImGui::OpenPopup("Save this level as");
            }

            if (ImGui::BeginPopupModal("Save this level as", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
            {
                ImGui::Text("Save the the level as:");

                ImGui::PushItemWidth(-0.1f);
                static std::string s_LevelToSave = "";
                ImGui::InputText("###DialogSaveLevelInput", s_LevelToSave);

                if (s_LevelToSave == "")
                {
                    ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);
                    ImGui::Button("Save");
                    ImGui::PopStyleVar();
                }
                else if (ImGui::Button("Save"))
                {
                    currentScene->Save(GAME_SCENE_PATH, s_LevelToSave);
                    currentScene->SetName(s_LevelToSave);
                    s_LevelToSave = "";
                    ImGui::CloseCurrentPopup();
                }

                ImGui::SetItemDefaultFocus();
                ImGui::SameLine();

                if (ImGui::Button("Cancel"))
                {
                    s_LevelToSave = "";
                    ImGui::CloseCurrentPopup();
                }

                ImGui::EndPopup();
            }

            /// End popup dialogs

            if (ImGui::BeginMenu("View"))
            {
                for (auto systemIterator : m_SystemManager.m_Systems)
                {
                    ISystem* system = systemIterator.second;
                    if (!(rttr::rttr_cast<ImGuiSystem*>(system))) // Because this contains the main logic of ImGui, you should not be able to disable it
                    {
                        Inspectable* inspectableSystem = rttr::rttr_cast<Inspectable*>(system);

                        if (inspectableSystem) // If the system also inherits from InspectableSystem, the cast will be succesful and not be a nullptr, thus return true
                        {
                            auto subSystems = inspectableSystem->GetAllInspectables();
                            for (auto subSystem : subSystems)
                            {
                                if (ImGui::MenuItem(subSystem.GetName().c_str(), nullptr, *subSystem.GetEnabled()))
                                {
                                    subSystem.ToggleEnabled();
                                }
                            }
                        }
                    }
                }

                ImGui::Separator();

                // Disabled until it is needed/wanted
                /*if (ImGui::BeginMenu("Switch workspace"))
                {
                    if (ImGui::MenuItem("Level Editor"))
                    {
                        //Change ini file

                        //io.IniFilename = "imgui.ini"; // Remember me!
                        //ImGui::LoadIniSettingsFromDisk("");
                        //ImGui::SaveIniSettingsToDisk("");
                    }

                    if (ImGui::MenuItem("Debugging"))
                    {
                        //Change ini file
                    }

                    if (ImGui::MenuItem("ImGui Default"))
                    {
                        //Change to the original ini file (imgui.ini)
                    }

                    ImGui::EndMenu();
                }*/

                if (ImGui::BeginMenu("Style"))
                {
                    static char currentStyleIdx = 1;
                    if (ImGui::MenuItem("Classic", nullptr, currentStyleIdx == 0))
                    {
                        ImGui::StyleColorsClassic();
                        currentStyleIdx = 0;
                    }

                    if (ImGui::MenuItem("Dark", nullptr, currentStyleIdx == 1))
                    {
                        ImGui::StyleColorsDark();
                        currentStyleIdx = 1;
                    }

                    if (ImGui::MenuItem("Light", nullptr, currentStyleIdx == 2))
                    {
                        ImGui::StyleColorsLight();
                        currentStyleIdx = 2;
                    }

                    ImGui::EndMenu();
                }

                ImGui::EndMenu();
            }

            /*
            if (ImGui::BeginMenu("Debug"))
            {
                if (ImGui::MenuItem("Physics Debug Draw", nullptr, false))
                {

                }

                if (ImGui::MenuItem("Graphics Debug Draw", nullptr, false))
                {

                }

                if (ImGui::MenuItem("Enable Debug Logging", nullptr, false))
                {

                }

                ImGui::EndMenu();
            }
            */
        }
        ImGui::EndMainMenuBar();

        static bool disableFrameBufferThingy = false;
        if (disableFrameBufferThingy)
        {
            ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
            windowFlags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;

            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
            ImGui::Begin("##MainViewport", nullptr, windowFlags);
            ImGui::Text("Stuff 'n things.");
            //ImVec2 vMin = ImGui::GetWindowContentRegionMin();
            //ImVec2 vMax = ImGui::GetWindowContentRegionMax();
            ImGui::Image(0, ImVec2(1.f, 1.f)); // Replace with something that will render the FrameBuffer
            ImGui::End();
            ImGui::PopStyleVar(3); // Pop the previous three PushStyleVar's
        }
    }

    void ImGuiSystem::RenderEditorWindows()
    {
        if (m_IsEnabled)
        {
            CreateDockspace();

            // Render everything that needs to be rendered
            for (auto systemIterator : m_SystemManager.m_Systems)
            {
                Inspectable* inspectableSystem = rttr::rttr_cast<Inspectable*>(systemIterator.second);

                if (inspectableSystem) // If the system also inherits from InspectableSystem, the cast will be succesful and not be a nullptr
                {
                    inspectableSystem->Inspect(); // The system itself will know what to display
                }
            }

            //ImGui::ShowDemoWindow(); // Here for demo purposes, remove later

            m_ImGuiRenderer->Render();
        }
    }

    void ImGuiSystem::CreateDockspace()
    {
        ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None | ImGuiDockNodeFlags_PassthruCentralNode;

        // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
        // because it would be confusing to have two docking targets within each others.
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

        // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background and handle the pass-thru hole, so we ask Begin() to not render a background.
        if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
        {
            window_flags |= ImGuiWindowFlags_NoBackground;
        }

        ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->Pos);
        ImGui::SetNextWindowSize(viewport->Size);
        ImGui::SetNextWindowViewport(viewport->ID);

        // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
        // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive, 
        // all active windows docked into it will lose their parent and become undocked.
        // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise 
        // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("DockSpace", nullptr, window_flags);
        ImGui::PopStyleVar(3); // Pop the previous three PushStyleVar's

        // DockSpace
        ImGuiIO& io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }
        else
        {
            // Copied from ImGui::ShowDockingDisabledMessage();
            ImGui::Text("ERROR: Docking is not enabled! See Demo > Configuration.");
            ImGui::Text("Set io.ConfigFlags |= ImGuiConfigFlags_DockingEnable in your code, or ");
            ImGui::SameLine(0.0f, 0.0f);
            if (ImGui::SmallButton("click here"))
            {
                io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
            }
        }

        ImGui::End();
    }
}
