#pragma once
#include <windows.h>

/// <summary>
/// 그래픽스 엔진의 인터페이스
/// </summary>

namespace MZGraphics
{
	class I3DRenderer abstract
	{
	public:
		virtual ~I3DRenderer() {};
		virtual void Initialize(HWND hWnd, UINT screenWidth, UINT screenHeight) = 0;
		virtual void Update(float deltaTime) = 0;
		virtual void Render() = 0;
		virtual void OnResize(UINT screenWidth, UINT screenHeight) = 0;
		virtual void Finalize() = 0;
	};
}

__declspec(dllexport) MZGraphics::I3DRenderer* CreateRenderer();
__declspec(dllexport) void ReleaseRenderer(MZGraphics::I3DRenderer* instance);