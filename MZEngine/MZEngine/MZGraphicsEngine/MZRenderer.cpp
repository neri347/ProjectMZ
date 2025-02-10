#include "MZRenderer.h"
#include <memory>
#include <DirectXColors.h>
#include "DX11DeviceBuilder.h"
#include "ResourceManager.h"
#include "ObjectManager.h"
#include "HelperObject.h"

MZGraphics::I3DRenderer* CreateRenderer()
{
	return new MZGraphics::MZRenderer();
}

void ReleaseRenderer(MZGraphics::I3DRenderer* instance)
{
	delete instance;
}

namespace MZGraphics
{

	MZRenderer::MZRenderer()
	{
	}

	MZRenderer::~MZRenderer()
	{
	}

	void MZRenderer::Initialize(HWND hWnd, UINT screenWidth, UINT screenHeight)
	{
		DX11DeviceBuilder* builder = new DX11DeviceBuilder(hWnd, screenWidth, screenHeight);
		// 리소스 매니저
		ResourceManager::Instance().Initialize(builder);

		// 임시
		ObjectManager::Instance().CreateGrid();
	}

	void MZRenderer::Update(float deltaTime)
	{
	}

	void MZRenderer::Render()
	{
		ResourceManager::Instance().GetDeviceContext()->ClearRenderTargetView(ResourceManager::Instance().GetRTV(), reinterpret_cast<const float*>(&DirectX::Colors::Black));
		
		for (auto& obj : ObjectManager::Instance().GetHelperObjects())
		{
			obj->Render();
		}

		ResourceManager::Instance().GetSwapChain()->Present(0, 0);
	}

	void MZRenderer::OnResize(UINT screenWidth, UINT screenHeight)
	{
	}

	void MZRenderer::Finalize()
	{
	}

}