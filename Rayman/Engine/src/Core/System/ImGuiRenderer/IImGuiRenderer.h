#pragma once

namespace Engine
{
    class IImGuiRenderer
    {
    public:
        IImGuiRenderer();
        ~IImGuiRenderer();

        virtual void Init()             = 0;
        virtual void Update()           = 0;
        virtual void Render()           = 0;
        virtual void Terminate()        = 0;

    };
}
