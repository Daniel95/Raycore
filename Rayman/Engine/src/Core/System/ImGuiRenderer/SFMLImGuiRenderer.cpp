#include "RayCorePCH.h"

#include "Core/System/ImGuiRenderer/SFMLImGuiRenderer.h"

#include "imgui.h"
#include "imgui-SFML.h"

#include <SFML/Graphics/RenderWindow.hpp>

namespace Engine
{
    SFMLImGuiRenderer::SFMLImGuiRenderer()
    {
        m_RenderWindow = nullptr;
        m_Time = nullptr;
    }
    
    SFMLImGuiRenderer::~SFMLImGuiRenderer()
    { }
    
    void SFMLImGuiRenderer::Init()
    {
        if (!m_RenderWindow)
        {
            throw std::exception();
        }

        ImGui::SFML::Init(*m_RenderWindow);

        ImGuiIO& io = ImGui::GetIO(); (void) io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
    }
    
    void SFMLImGuiRenderer::Update()
    {
        if (!m_Time)
        {
            throw std::exception();
        }

        ImGui::SFML::Update(*m_RenderWindow, *m_Time);
        m_Time = nullptr;
    }
    
    void SFMLImGuiRenderer::Render()
    {
        ImGui::SFML::Render(*m_RenderWindow);
    }
    
    void SFMLImGuiRenderer::Terminate()
    {
        ImGui::SFML::Shutdown();
    }

    void SFMLImGuiRenderer::SetRenderWindow(sf::RenderWindow* a_RenderWindow)
    {
        if (!a_RenderWindow)
        {
            throw std::exception();
        }

        m_RenderWindow = a_RenderWindow;
    }

    void SFMLImGuiRenderer::SetDeltaTime(sf::Time* a_Time)
    {
        m_Time = a_Time;
    }

    void SFMLImGuiRenderer::ProcessEvents(sf::Event* a_Event)
    {
        if (!a_Event)
        {
            throw std::exception();
        }
        else
        {
            ImGui::SFML::ProcessEvent(*a_Event);
        }
    }
}
