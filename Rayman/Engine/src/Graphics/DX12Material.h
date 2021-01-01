#pragma once

/*
 *  Copyright(c) 2018 Jeremiah van Oosten
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files(the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions :
 *
 *  The above copyright notice and this permission notice shall be included in
 *  all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 *  IN THE SOFTWARE.
 */

 /**
  *  @file Material.h
  *  @date October 24, 2018
  *  @author Jeremiah van Oosten
  *
  *  @brief Material structure that uses HLSL constant buffer padding rules.
  */


#include <DirectXMath.h>

namespace Engine
{
	struct DX12Material
	{
		DX12Material(
			DirectX::XMFLOAT4 emissive = { 0.0f, 0.0f, 0.0f, 1.0f },
			DirectX::XMFLOAT4 ambient = { 0.1f, 0.1f, 0.1f, 1.0f },
			DirectX::XMFLOAT4 diffuse = { 1.0f, 1.0f, 1.0f, 1.0f },
			DirectX::XMFLOAT4 specular = { 1.0f, 1.0f, 1.0f, 1.0f },
			float specularPower = 128.0f
		) :
			Emissive(emissive),
			Ambient(ambient),
			Diffuse(diffuse),
			Specular(specular),
			SpecularPower(specularPower)
		{}
	
		DirectX::XMFLOAT4 Emissive;
		//----------------------------------- (16 byte boundary)
		DirectX::XMFLOAT4 Ambient;
		//----------------------------------- (16 byte boundary)
		DirectX::XMFLOAT4 Diffuse;
		//----------------------------------- (16 byte boundary)
		DirectX::XMFLOAT4 Specular;
		//----------------------------------- (16 byte boundary)
		float             SpecularPower;
		uint32_t          Padding[3];
		//----------------------------------- (16 byte boundary)
		// Total:                              16 * 5 = 80 bytes
	
		// Define some interesting materials.
		static const DX12Material UnlitWhite;
		static const DX12Material Red;
		static const DX12Material Green;
		static const DX12Material Blue;
		static const DX12Material Cyan;
		static const DX12Material Magenta;
		static const DX12Material Yellow;
		static const DX12Material White;
		static const DX12Material Black;
		static const DX12Material Emerald;
		static const DX12Material Jade;
		static const DX12Material Obsidian;
		static const DX12Material Pearl;
		static const DX12Material Ruby;
		static const DX12Material Turquoise;
		static const DX12Material Brass;
		static const DX12Material Bronze;
		static const DX12Material Chrome;
		static const DX12Material Copper;
		static const DX12Material Gold;
		static const DX12Material Silver;
		static const DX12Material BlackPlastic;
		static const DX12Material CyanPlastic;
		static const DX12Material GreenPlastic;
		static const DX12Material RedPlastic;
		static const DX12Material WhitePlastic;
		static const DX12Material YellowPlastic;
		static const DX12Material BlackRubber;
		static const DX12Material CyanRubber;
		static const DX12Material GreenRubber;
		static const DX12Material RedRubber;
		static const DX12Material WhiteRubber;
		static const DX12Material YellowRubber;
	};
}