#pragma once
#ifndef __OBJECT_FACTORY_H__
#define __OBJECT_FACTORY_H__
#include"Object.h"
#include"Global.h"
#include"Aladdin.h"
#include"Apple.h"
#include"Ground.h"
#include"StaticObject.h"
#include"Stair.h"
#include"Civilian1.h"
#include"HeartItem.h"
class ObjectFactory
{
private:
	static ObjectFactory*			__instance;
	ObjectFactory();
public:
	~ObjectFactory();
	static ObjectFactory*			Instance();
	Object * createObject(Global::EObject id, int x, int y, int width, int height, Global::EDirection direct);
};

#endif __OBJECT_FACTORY_H__