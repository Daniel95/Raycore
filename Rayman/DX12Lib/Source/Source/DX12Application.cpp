#include <DX12LibPCH.h>

#include <DX12Graphics.h>
#include <DX12Application.h>
#include <Window.h>

DX12Application::DX12Application( const std::wstring& name, int width, int height, bool vSync )
    : m_Name( name )
    , m_Width( width )
    , m_Height( height )
    , m_vSync( vSync )
{
}

DX12Application::~DX12Application()
{
    assert(!m_pWindow && "Use Game::Destroy() before destruction.");
}

bool DX12Application::Initialize()
{
    // Check for DirectX Math library support.
    if (!DirectX::XMVerifyCPUSupport())
    {
        MessageBoxA(NULL, "Failed to verify DirectX Math library support.", "Error", MB_OK | MB_ICONERROR);
        return false;
    }

    m_pWindow = DX12Graphics::Get().CreateRenderWindow(m_Name, m_Width, m_Height, m_vSync);
    m_pWindow->RegisterCallbacks(shared_from_this());
    m_pWindow->Show();

    return true;
}

void DX12Application::Destroy()
{
	DX12Graphics::Get().DestroyWindow(m_pWindow);
    m_pWindow.reset();
}

void DX12Application::OnStart()
{

}

void DX12Application::OnFixedUpdate(FixedUpdateEventArgs& e)
{
}

void DX12Application::OnUpdate(UpdateEventArgs& e)
{
}

void DX12Application::OnRender(RenderEventArgs& e)
{
}

void DX12Application::OnKeyPressed(KeyEventArgs& e)
{
    // By default, do nothing.
}

void DX12Application::OnKeyReleased(KeyEventArgs& e)
{
    // By default, do nothing.
}

void DX12Application::OnMouseMoved(class MouseMotionEventArgs& e)
{
    // By default, do nothing.
}

void DX12Application::OnMouseButtonPressed(MouseButtonEventArgs& e)
{
    // By default, do nothing.
}

void DX12Application::OnMouseButtonReleased(MouseButtonEventArgs& e)
{
    // By default, do nothing.
}

void DX12Application::OnMouseWheel(MouseWheelEventArgs& e)
{
    // By default, do nothing.
}

void DX12Application::OnResize(ResizeEventArgs& e)
{
    m_Width = e.Width;
    m_Height = e.Height;
}

void DX12Application::OnWindowDestroy()
{
    // If the Window which we are registered to is 
    // destroyed, then any resources which are associated 
    // to the window must be released.
    UnloadContent();
}

