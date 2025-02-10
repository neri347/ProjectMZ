#pragma once
#include "../MZGraphicsEngine/MathHeader.h"

/// <summary>
/// 3D ������Ʈ�� ������ �������̽�
/// </summary>

namespace MZGraphics
{
	class IRenderable
	{
	public:
		virtual ~IRenderable() {};
		virtual void SetWorldTM(const Matrix& worldTM) = 0;
		virtual void SetActive(bool isActive) = 0;
	};
}