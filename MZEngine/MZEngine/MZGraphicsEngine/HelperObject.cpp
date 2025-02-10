#include "HelperObject.h"
#include "ResourceManager.h"
#include "Mesh.h"
#include "VertexShader.h"
#include "PixelShader.h"

namespace MZGraphics
{

	HelperObject::HelperObject()
		: _world(DirectX::XMMatrixIdentity())
		, _isActive(true)
	{
		_deviceContext = ResourceManager::Instance().GetDeviceContext();
		_rasterizerState = ResourceManager::Instance().GetRasterizerState(eRasterizerState::WIREFRAME);
		_vertexShader = ResourceManager::Instance().GetVertexShader("VertexShader.cso");
		_pixelShader = ResourceManager::Instance().GetPixelShader("PixelShader.cso");
	}

	HelperObject::~HelperObject()
	{

	}

}