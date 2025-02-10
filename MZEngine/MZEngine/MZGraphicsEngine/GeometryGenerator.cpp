#include "GeometryGenerator.h"
#include "ResourceManager.h"
#include "VertexStruct.h"
#include "mesh.h"
#include <DirectXMath.h>
#include <DirectXColors.h>
using namespace DirectX;

namespace MZGraphics
{
	void GeometryGenerator::CreateGrid()
	{
		// 정점 버퍼를 만든다.
		PosColor vertices[100];
		for (int i = 0; i < 100; ++i)
		{
			vertices[i].Position = XMFLOAT3((float)(i % 10) - 5.0f, 0.0f, (float)(i / 10) - 5.0f);
			vertices[i].Color = XMFLOAT4((const float*)&Colors::DarkGray);
		}

		// 인덱스 버퍼를 만든다.
		UINT indices[40];
		for (int i = 0; i < 10; i++)
		{
			indices[i * 2] = i;
			indices[i * 2 + 1] = i + 90;
		}

		for (int i = 0; i < 10; i++)
		{
			indices[20 + (i * 2)] = i * 10;
			indices[20 + (i * 2) + 1] = i * 10 + 9;
		}
		
		// 메쉬를 만든다.
		Mesh* _gridMesh = new Mesh(&vertices[0], 100, &indices[0], 40);

		// 리소스 매니저에 추가한다.
		FileData* data = new FileData();
		data->loadedMeshes.push_back(_gridMesh);
		ResourceManager::Instance().AddFileData("Grid", data);
	}
}