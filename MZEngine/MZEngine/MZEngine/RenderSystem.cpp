#include "RenderSystem.h"

namespace MZCore
{

	RenderSystem::RenderSystem()
		: _renderer(nullptr)
	{

	}

	void RenderSystem::Initialize(HWND hWnd, UINT screenWidth, UINT screenHeight)
	{
		_renderer = (std::unique_ptr<MZGraphics::I3DRenderer>(CreateRenderer()));
		_renderer->Initialize(hWnd, screenWidth, screenHeight);
	}

	void RenderSystem::Update(float deltaTime)
	{
		_renderer->Update(deltaTime);
	}

	void RenderSystem::Render()
	{
		_renderer->Render();
	}

	void RenderSystem::OnResize(UINT screenWidth, UINT screenHeight)
	{
		_renderer->OnResize(screenWidth, screenHeight);
	}

	void RenderSystem::Finalize()
	{
		_renderer->Finalize();
	}

}