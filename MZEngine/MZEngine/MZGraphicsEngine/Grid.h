#pragma once
#include "HelperObject.h"

namespace MZGraphics
{
	class Grid : public HelperObject
	{
	public:
		Grid();
		~Grid();

	public:
		virtual void Update(float deltaTime) override;
		virtual void Render() override;
		virtual void SetWorldTM(const Matrix& worldTM) override;
		virtual void SetActive(bool isActive) override;
	};
}

