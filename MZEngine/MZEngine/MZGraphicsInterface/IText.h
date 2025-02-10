#pragma once
#include "ISketchable.h"
#include <windows.h>
#include <string>

namespace MZGraphics
{
	class IText : public ISketchable
	{
	public:
		virtual ~IText() {};
		virtual void SetText(const std::string& str) = 0;
		virtual void SetFont(const std::string fontname) = 0;
		virtual void SetColor(DirectX::FXMVECTOR color) = 0;

		virtual std::string GetText() = 0;
		virtual DirectX::FXMVECTOR GetColor() = 0;
	};
}