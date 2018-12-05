#pragma once
#ifndef __ACTION_OBJECT_H__
#define __ACTION_OBJECT_H__

#include"Object.h"
#include"Global.h"
#define SWORD_WIDTH 100
class ActionObject :public Object
{
protected:
	Global::EState					_state;
	Global::EDirection				_direct;
	int								_ax;
	int								_ay;
	float							_timeAction;
	bool							_isGround;
	float							_hp;
	bool							_isDead;
	bool							_isLookUp;
	bool							_isJafar;
	bool							_isGems;
	bool							_isA_Deal;
	WRect							_rectSword;
	WRect							_rectMove;
public:
	ActionObject();
	ActionObject(int x, int y, int width = 0, int height = 0);
	~ActionObject();
	virtual void					update(float deltaTime) = 0;
	virtual void					updateBody();
	virtual void					render() = 0;
	virtual Collision::ResultCollision
									processCollision(Object* obj) = 0;
	
	bool							isDead();
	bool							isGround();
	bool							isLookUp();
	void							setLookUp(bool flag);
	bool							isJafar();
	void							setJafar(bool flag);
	bool							isGems();
	void							setGems(bool flag);
	bool							isA_Deal();
	void							setA_Deal(bool flag);
	int								getAx();
	int								getAy();
	Global::EState					getState();
	Global::EDirection				getDirect();
	WRect							getRectSword();
	WRect							getRectMove();
	void							setAx(int ax);
	void							setAy(int ay);
	void							setDead(bool dead = true);
	void							setGround(bool flag = true);
	void							setState(Global::EState state);
	void							setDirect(Global::EDirection direct);
	void							setRectSword(WRect sword);
	void							refreshTime();
	
};

#endif __ACTION_OBJECT_H__