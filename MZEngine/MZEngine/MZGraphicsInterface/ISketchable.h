#pragma once
#include "../MZGraphicsEngine/MathHeader.h"

/// <summary>
/// 2D ������Ʈ�� ������ �������̽�
/// </summary>

namespace MZGraphics
{
	class ISketchable
	{
	public:
		virtual ~ISketchable() {};
		virtual void SetPosition(const Vector2& position) = 0;
		virtual void SetRotation(float rotate) = 0;
		virtual void SetSize(float size) = 0;
		virtual void SetSortOrder(float order) = 0;
		virtual void SetActive(bool isActive) = 0;
	};
}