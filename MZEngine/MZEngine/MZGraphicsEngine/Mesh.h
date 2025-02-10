#pragma once
#include <d3d11.h>
#include <dxgi.h>
#include <DirectXMath.h>
#include <wrl.h>
#include "VertexStruct.h"
#include "ResourceManager.h"
using Microsoft::WRL::ComPtr;

namespace MZGraphics
{
	class Mesh
	{
	public:
		Mesh(PosColor* vertexArray, int vertexNum, unsigned int* indexArray, int indicesNum);
		void BindBuffers();
		void Draw();
		void DrawInstanced(UINT instanceCount);

	private:
		template <typename T>
		void CreateBuffer(T* vertexArray, int vertexNum, unsigned int* indexArray, int indicesNum)
		{
			// Create the vertex buffer
			D3D11_BUFFER_DESC vbd
			{
				.ByteWidth = sizeof(T) * vertexNum,
				.Usage = D3D11_USAGE_IMMUTABLE,
				.BindFlags = D3D11_BIND_VERTEX_BUFFER,
				.CPUAccessFlags = 0,
				.MiscFlags = 0,
				.StructureByteStride = 0,
			};
			D3D11_SUBRESOURCE_DATA initialVertexData;
			initialVertexData.pSysMem = vertexArray;
			ResourceManager::Instance().GetDevice()->CreateBuffer(&vbd, &initialVertexData, _vertexBuffer.GetAddressOf());

			// Create the index buffer
			D3D11_BUFFER_DESC ibd
			{
				.ByteWidth = sizeof(unsigned int) * indicesNum,
				.Usage = D3D11_USAGE_IMMUTABLE,
				.BindFlags = D3D11_BIND_INDEX_BUFFER,
				.CPUAccessFlags = 0,
				.MiscFlags = 0,
				.StructureByteStride = 0,
			};
			D3D11_SUBRESOURCE_DATA initialIndexData;
			initialIndexData.pSysMem = indexArray;
			_device->CreateBuffer(&ibd, &initialIndexData, _indexBuffer.GetAddressOf());

			// Save the indices
			_numIndices = indicesNum;
			_singleVertexSize = sizeof(T);
		}

	private:
		ComPtr<ID3D11Device> _device;
		ComPtr<ID3D11DeviceContext> _deviceContext;
		ComPtr<ID3D11Buffer> _vertexBuffer;
		ComPtr<ID3D11Buffer> _indexBuffer;
		UINT _singleVertexSize;
		int _numIndices;
	};
}
