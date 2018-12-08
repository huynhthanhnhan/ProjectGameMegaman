#include "ObjectFactory.h"

ObjectFactory*					ObjectFactory::__instance = nullptr;

ObjectFactory::ObjectFactory()
{
}


ObjectFactory::~ObjectFactory()
{
}

ObjectFactory * ObjectFactory::Instance()
{
	if (!__instance)
		__instance = new ObjectFactory();
	return __instance;
}

Object * ObjectFactory::createObject(Global::EObject id, int x, int y, int width, int height, Global::EDirection direct)
{
	Object* obj = NULL;
	switch (id)
	{
	case Global::GROUND: obj = new Ground(x, y, width, height); break;
	case Global::STAIR: obj = new Stair(x, y, width, height, direct); break;
	case Global::WALL: obj = new Wall(x, y, width, height); break;
	case Global::CIVILIAN1: obj = new Civilian1(x, y, width, height, direct); break;
	case Global::HEARTITEM: obj = new HeartItem(x, y); break;
	}
	return obj;
}
