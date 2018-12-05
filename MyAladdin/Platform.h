#pragma once
#ifndef __PLATFORM_H__
#define __PLATFORM_H__
#include"Object.h"
class Platform :public Object
{
public:
	Platform();
	Platform(int x, int y, int width, int height);
	~Platform();
	virtual Collision::ResultCollision processCollision(Object* obj);

	// Inherited via Object
	virtual void update(float detalTime) override;
};


#endif __PLATFORM_H__