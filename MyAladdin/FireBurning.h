#pragma once
#ifndef __FIRE_BURNING_H__
#define __FIRE_BURNING_H__
#include"Enemy.h"
#include"Sound.h"
#define V_FIRE 0
#define W_FIRE 30
#define H_FIRE 0
#define D_ATTACK_FIRE 0
class FireBurning
	:public Enemy
{
public:
	Sound* _sound;
	FireBurning(int xRegion, int yRegion, int widthRegion, int heightRegion, Global::EDirection direct);
	~FireBurning();
	bool isSnake;
	void set(bool flag);
	int _time =0;
	// Inherited via Enemy
	virtual bool isAttack() override;
	virtual void update(float deltaTime) override;
	virtual void Refresh() override;
private:
	Collision::ResultCollision processCollision(Object * obj);
	virtual void LoadResource() override;
	virtual void UpdateRender(Global::EState currentState) override;
	virtual void DetermineDirection(Global::EState state, Global::EDirection direct);
};

#endif __FIRE_BURNING_H__