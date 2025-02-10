#include "Mesh.h"

namespace MZGraphics
{
	Mesh::Mesh(PosColor* vertexArray, int vertexNum, unsigned int* indexArray, int indicesNum)
	{
		_device = ResourceManager::Instance().GetDevice();
		_deviceContext = ResourceManager::Instance().GetDeviceContext();
		CreateBuffer(vertexArray, vertexNum, indexArray, indicesNum);
	}

	void Mesh::BindBuffers()
	{
		UINT offset = 0;
		_deviceContext->IASetVertexBuffers(0, 1, _vertexBuffer.GetAddressOf(), &_singleVertexSize, &offset);
		_deviceContext->IASetIndexBuffer(_indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
	}

	void Mesh::Draw()
	{
		_deviceContext->DrawIndexed(_numIndices, 0, 0);
	}

	void Mesh::DrawInstanced(UINT instanceCount)
	{
		_deviceContext->DrawIndexedInstanced(_numIndices, instanceCount, 0, 0, 0);
	}

}