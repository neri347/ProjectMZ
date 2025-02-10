#include "Text.h"
#include "ResourceManager.h"
#include <DirectXColors.h>

namespace MZGraphics
{

	Text::Text()
		: _text(L"Text"), _fontname("KRAFTON_25"),
		_color(DirectX::Colors::White),  
		_position(), _rotation(0.0f), _size(1.0f), 
		_sortOrder(0.0f), _isActive(true)
	{
		SetFont(_fontname);
	}

	Text::~Text()
	{
		delete _text;
		_text = nullptr;
	}

	void Text::SetPosition(const Vector2& position)
	{
		_position = position;
	}

	void Text::SetRotation(float rotate)
	{
		_rotation = rotate;
	}

	void Text::SetSize(float size)
	{
		_size = size;
	}

	void Text::SetSortOrder(float order)
	{
		_sortOrder = order;
	}

	void Text::SetActive(bool isActive)
	{
		_isActive = isActive;
	}

	void Text::SetText(const std::string& str)
	{
		std::wstring wstr(str.begin(), str.end());
		_text = wstr.c_str();
	}

	void Text::SetFont(const std::string fontname)
	{
		/// 리소스 매니저에서 폰트 가져와야 한다
		DirectX::SpriteFont* newFont = ResourceManager::Instance().GetFont(fontname);
		if (newFont)
		{
			_fontname = fontname;
			_font = newFont;
		}
	}

	void Text::SetColor(DirectX::FXMVECTOR color)
	{
		_color = color;
	}

	std::string Text::GetText()
	{
		std::wstring wstr(_text);
		return std::string(wstr.begin(), wstr.end());
	}

	DirectX::FXMVECTOR Text::GetColor()
	{
		return _color;
	}

	void Text::DrawText()
	{
		if (!_isActive)
			return;

		_font->DrawString(
			ResourceManager::Instance().GetSpriteBatch(),
			_text,
			_position,
			_color,
			_rotation,
			DirectX::XMFLOAT2(),
			_size,
			DirectX::SpriteEffects_None,
			_sortOrder
			);
	}

}