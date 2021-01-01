#pragma once

#include "Core/Application.h"
#include "Core/Utilities/Log.h"

#include "imgui.h"
#include "Examples/EventExample.h"
#include "Examples/RTTRExample.h"

#include <cstdint>
#include <DX12Graphics.h>
#include <DX12LibPCH.h>

extern Engine::Application* Engine::CreateApplication();

_Use_decl_annotations_
int CALLBACK wWinMain(HINSTANCE a_hInstance, HINSTANCE a_hPrevInstance, PWSTR a_lpCmdLine, int a_nCmdShow)
{
	//Start console.
	AllocConsole();

	Engine::Log::Init();

	LOG_ENGINE_WARN("Initialized Log!");

    TestRTTR();

	int returnValue = 0;

	WCHAR path[MAX_PATH];

	int argc = 0;
	LPWSTR* argv = CommandLineToArgvW(a_lpCmdLine, &argc);
	if (argv)
	{
		for (int i = 0; i < argc; ++i)
		{
			// -wd Specify the Working Directory.
			if (wcscmp(argv[i], L"-wd") == 0)
			{
				wcscpy_s(path, argv[++i]);
				SetCurrentDirectoryW(path);
			}
		}
		LocalFree(argv);
	}

	DX12Graphics::Create(a_hInstance);
	{
		//std::shared_ptr<Engine::Application> app = std::make_shared<Engine::Application>();
		Engine::Application* rawApp = Engine::CreateApplication();
		std::shared_ptr<Engine::Application> app(rawApp);
		returnValue = DX12Graphics::Get().Run(app);
	}
	DX12Graphics::Destroy();

	return returnValue;
}