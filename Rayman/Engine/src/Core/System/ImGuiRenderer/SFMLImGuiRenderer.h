#pragma once
#include "Core/System/ImGuiRenderer/IImGuiRenderer.h"

namespace sf
{
    class Event;
    class RenderWindow;
    class Time;
}

namespace Engine
{
    class SFMLImGuiRenderer : public IImGuiRenderer
    {
    public:
        SFMLImGuiRenderer();
        ~SFMLImGuiRenderer();

        void Init() override;
        void Update() override;
        void Render() override;
        void Terminate() override;

        void SetRenderWindow(sf::RenderWindow* a_RenderWindow);
        void SetDeltaTime(sf::Time* a_Time);
        void ProcessEvents(sf::Event* a_Event);

    private:
        sf::RenderWindow* m_RenderWindow;
        sf::Time* m_Time;

    };
}
