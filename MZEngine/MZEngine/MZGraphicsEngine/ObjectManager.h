#pragma once
#include "Singleton.h"
#include <vector>

namespace MZGraphics
{
	class HelperObject;

	class ObjectManager final : public Singleton<ObjectManager>
	{
	public:
		friend Singleton<ObjectManager>;
		~ObjectManager();

	public:
		std::vector<HelperObject*>& GetHelperObjects();

	public:
		// 오브젝트 생성 관련
		void CreateGrid();

	private:
		ObjectManager();
		std::vector<HelperObject*> helperObjects;
	};
}

