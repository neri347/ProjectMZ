#include "ObjectManager.h"
#include "HelperObject.h"
#include "Grid.h"

namespace MZGraphics
{
	ObjectManager::ObjectManager()
	{

	}

	ObjectManager::~ObjectManager()
	{

	}

	std::vector<MZGraphics::HelperObject*>& ObjectManager::GetHelperObjects()
	{
		return helperObjects;
	}

	void ObjectManager::CreateGrid()
	{
		HelperObject* grid = new Grid();
		helperObjects.push_back(grid);
	}

}