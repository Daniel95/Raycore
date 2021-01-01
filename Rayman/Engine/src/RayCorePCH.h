#pragma once

#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING

//STD
#include <vector>
#include <map>
#include <experimental/filesystem>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <streambuf>
#include <typeinfo> 
#include <memory>
#include <cassert>
#include <chrono>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <crtdbg.h>

//Box2D
#include <Box2D/Box2D.h>

//EventPP
#include "eventpp/callbacklist.h"
#include "eventpp/eventdispatcher.h"
#include "eventpp/eventqueue.h"
#include "eventpp/eventpolicies.h"

//ImGUI
#include <imgui.h>
#include "imgui_impl_win32.h"
#include "imgui_impl_dx12.h"

//RapidJSON
#include "Core/Utilities/json/from_json.h"
#include "Core/Utilities/json/to_json.h"
#include "Core/Utilities/Math/SimpleMath.h"
#include "Core/Utilities/Math/MathUtils.h"
#include "Core/Utilities/Math/DX12Matrix.h"
#include <DirectXMath.h>

//RTTR
#include <rttr/variant.h>
#include <rttr/registration>

//spdlog
#include "spdlog/spdlog.h"

//DX12
#include <DX12Mesh.h>
#include <DX12Texture.h>
#include <DX12LibPCH.h>
#include <CommandList.h>
#include <CommandQueue.h>
#include <DX12Graphics.h>
#include <Shaders/PixelShader.h>
#include <Shaders/VertexShader.h>
#include <Shaders/ImGUI_PS.h>
#include <Shaders/ImGUI_VS.h>
#include <d3dx12.h>
#include <d3dcompiler.h>
#include <DirectXColors.h>
#include <wrl.h>

#include <DX12Application.h>
#include <Window.h>
#include <RenderTarget.h>
#include <RootSignature.h>
#include <VertexBuffer.h>
#include <DirectXMath.h>

#include <d3d12.h>
#include <dxgi1_4.h>
#include <tchar.h>

using namespace Microsoft::WRL;

using namespace DirectX;
