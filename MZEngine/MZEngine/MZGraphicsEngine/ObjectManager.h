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
		// ������Ʈ ���� ����
		void CreateGrid();

	private:
		ObjectManager();
		std::vector<HelperObject*> helperObjects;
	};
}

