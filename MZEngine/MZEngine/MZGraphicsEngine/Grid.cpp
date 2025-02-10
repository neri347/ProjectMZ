#include "Grid.h"
#include "ResourceManager.h"
#include "Mesh.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include <DirectXMath.h>
using namespace DirectX;

namespace MZGraphics
{
	Grid::Grid()
		: HelperObject()
	{
		_meshes = ResourceManager::Instance().GetFileData("Grid")->loadedMeshes;
	}

	Grid::~Grid()
	{

	}

	void Grid::Update(float deltaTime)
	{

	}

	void Grid::Render()
	{
		if (!_isActive)
			return;

		_deviceContext->RSSetState(_rasterizerState.Get());
		_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);

		_vertexShader->SetMatrix4x4("world", XMMatrixTranspose(_world));

		/// юс╫ц
		_vertexShader->SetMatrix4x4("viewProjection", XMMatrixTranspose(XMMatrixIdentity()));

		_vertexShader->CopyAllBufferData();
		_vertexShader->SetShader();

		_pixelShader->CopyAllBufferData();
		_pixelShader->SetShader();

		for (auto mesh : _meshes)
		{
			mesh->BindBuffers();
			mesh->Draw();
		}
	}

	void Grid::SetWorldTM(const Matrix& worldTM)
	{
		_world = worldTM;
	}

	void Grid::SetActive(bool isActive)
	{
		_isActive = isActive;
	}
}