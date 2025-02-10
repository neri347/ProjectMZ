#pragma once
#include <windows.h>
#include "Singleton.h"
#include <memory>
#include "../MZGraphicsInterface/I3DRenderer.h"

namespace MZCore
{
	class RenderSystem final: public Singleton<RenderSystem>
	{
	public:
		friend Singleton<RenderSystem>;
		void Initialize(HWND hWnd, UINT screenWidth, UINT screenHeight);
		void Update(float deltaTime);
		void Render();
		void OnResize(UINT screenWidth, UINT screenHeight);
		void Finalize();

	private:
		RenderSystem();
		std::unique_ptr<MZGraphics::I3DRenderer> _renderer;
	};
}