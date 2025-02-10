#pragma once
#include "../MZGraphicsInterface/IHelperObject.h"
#include <d3d11.h>
#include <DirectXMath.h>
#include <wrl.h>
using Microsoft::WRL::ComPtr;

namespace MZGraphics
{
	class Mesh;
	class VertexShader;
	class PixelShader;

	class HelperObject : public IHelperObject
	{
	public:
		HelperObject();
		virtual ~HelperObject();
		virtual void Update(float deltaTime) {};
		virtual void Render() {};

	protected:
		ComPtr<ID3D11DeviceContext> _deviceContext;
		ComPtr<ID3D11RasterizerState> _rasterizerState;

		std::vector<Mesh*> _meshes;
		VertexShader* _vertexShader;
		PixelShader* _pixelShader;

		DirectX::XMMATRIX _world;
		bool _isActive;
	};
}