#pragma once
#include "../MZGraphicsInterface/IText.h"
#include <DXTK/SpriteFont.h>
namespace MZGraphics
{
	class Text : public IText
	{
	public:
		Text();
		~Text();

		virtual void SetPosition(const Vector2& position) = 0;
		virtual void SetRotation(float rotate) = 0;
		virtual void SetSize(float size) = 0;
		virtual void SetSortOrder(float order) override;
		virtual void SetActive(bool isActive) override;

		virtual void SetText(const std::string& str) override;
		virtual void SetFont(const std::string fontname) override;
		virtual void SetColor(DirectX::FXMVECTOR color) override;		

		virtual std::string GetText() override;
		virtual DirectX::FXMVECTOR GetColor() override;

	public:
		void DrawText();

	private:
		DirectX::SpriteFont* _font;
		const wchar_t* _text;
		std::string _fontname;
		DirectX::XMVECTOR _color;
		DirectX::XMFLOAT2 _position;
		float _rotation;
		float _size;
		float _sortOrder;
		bool _isActive;
	};
}

