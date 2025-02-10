#pragma once
#include "../MZGraphicsEngine/MathHeader.h"

/// <summary>
/// 3D 오브젝트의 렌더러 인터페이스
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