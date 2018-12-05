#pragma once
#ifndef __APPLE_H__
#define __APPLE_H__
#include"Bullet.h"
#include"Sound.h"
#define DISTANCE_APPLE 45

//Diễn tả chuyển động của quả táo
class Apple :public Bullet
{
public:
	Sound* _sound;
	Apple(int x, int y, Global::EDirection direct);
	~Apple();
	// Inherited via Bullet
	virtual Collision::ResultCollision processCollision(Object * obj) override;
	virtual void LoadResource() override;
	virtual void UpdateRender(Global::EState currentState) override;
	virtual bool isFinish() override;
	virtual bool isCanAttack() override;
};

#endif __APPLE_H__