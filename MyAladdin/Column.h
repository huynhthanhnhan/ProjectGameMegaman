#pragma once
#ifndef __COLUMN_H__
#define __COLUMN_H__

#include"Object.h"
class Column :public Object
{
public:
	Column();
	Column(int x, int y, int width, int height);
	~Column();
	virtual Collision::ResultCollision processCollision(Object* obj);

	// Inherited via Object
	virtual void update(float detalTime) override;
};

#endif __COULMN_H__