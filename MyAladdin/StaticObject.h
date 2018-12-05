#pragma once
#ifndef __STATIC_OBJECT_H__
#define __STATIC_OBJECT_H__
#include"Object.h"
#include<vector>
#include"Ground.h"
#include"Rope.h"
#include"Column.h"
#include"Stair.h"
#include"Bar.h"
#include"Wall.h"
#include"ActionGround.h"
#include"Stick.h"
#include"Trap.h"
#include"Platform.h"

//Abstract Class of Static objects
class StaticObject
{
private:
	StaticObject();
	static StaticObject*			__instance;
	std::vector<Ground*>			_listGround;
	std::vector<ActionGround*>		_listActionGround;
	std::vector<Rope*>				_listRope;
	std::vector<Column*>				_listColumn;
	std::vector<Stair*>				_listStair;
	std::vector<Bar*>				_listBar;
	std::vector<Wall*>				_listWall;
	std::vector<Stick*>				_listStick;
	std::vector<Trap*>				_listTrap;
	std::vector<Platform*>			_listPlatform;
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
	void							addRope(Rope* rope);
	void							addColumn(Column* column);
	void							addBar(Bar* bar);
	void							addStair(Stair* stair);
	void							addWall(Wall* wall);
	void							addActionGround(ActionGround* acGround);
	void							addStick(Stick* stick);
	void							addTrap(Trap* trap);
	void							addPlatform(Platform* platform);

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