#pragma once
#include <windows.h>
#include <d3d11.h>
#include <dxgi.h>
#include <wrl.h>
#include "../MZGraphicsInterface/I3DRenderer.h"

using Microsoft::WRL::ComPtr;

namespace MZGraphics
{
	class MZRenderer : public I3DRenderer
	{
	public:
		MZRenderer();
		virtual ~MZRenderer();
		virtual void Initialize(HWND hWnd, UINT screenWidth, UINT screenHeight) override;
		virtual void Update(float deltaTime) override;
		virtual void Render() override;
		virtual void OnResize(UINT screenWidth, UINT screenHeight) override;
		virtual void Finalize() override;
	};
}