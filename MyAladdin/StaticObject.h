#pragma once
#ifndef __STATIC_OBJECT_H__
#define __STATIC_OBJECT_H__
#include"Object.h"
#include<vector>
#include"Ground.h"
#include"Stair.h"
#include"Wall.h"

//Abstract Class of Static objects
class StaticObject
{
private:
	StaticObject();
	static StaticObject*			__instance;
	std::vector<Ground*>			_listGround;
	std::vector<Stair*>				_listStair;
	std::vector<Wall*>				_listWall;
public:
	~StaticObject();
	static StaticObject*			Instance();
	void							clearGround();
	void							clearRope();
	void							clearColumn();
	void							clearBar();
	void							clearStair();
	void							clearWall();
	void							clearTrap();
	void							clear();

	void							addGround(Ground* ground);
	void							addStair(Stair* stair);
	void							addWall(Wall* wall);

	Collision::ResultCollision		processCollision(Object *obj);

	bool							isRopeCollision(Object* obj);
	bool							isColumnCollision(Object* obj);
	Collision::ResultCollision		groundCollision(Object* obj);
	Collision::ResultCollision		ropeCollision(Object* obj);
	Collision::ResultCollision		columnCollision(Object* obj);
	Collision::ResultCollision		barCollision(Object* obj);
	Collision::ResultCollision		stairCollision(Object* obj);
	Collision::ResultCollision		wallCollision(Object* obj);
	Collision::ResultCollision		actionGroundCollision(Object* obj);
	Collision::ResultCollision		stickCollision(Object* obj);
	Collision::ResultCollision		trapCollision(Object* obj);
	Collision::ResultCollision		platformCollision(Object* obj);
	void							permissionStair(Object* obj);

private:
	int								distance(int x, int y);
};

#endif __STATIC_OBJECT_H__