#pragma once
#ifndef __JAFAR_H__
#define __JAFAR_H__
#include "Enemy.h"
#include "Sound.h"
#include "SnakeBullet.h"
#include "JafarBullet.h"
#include "FireBurning.h"


#define W_JAFAR_NORMAL 100
#define H_JAFAR_NORMAL 200
#define V_JAFAR 0
#define D_ATTACK_JAFAR 85


class Jafar :
	public Enemy
{
public:
	Sound* _sound;
	Jafar(int xRegion, int yRegion, int widthRegion, int heightRegion, Global::EDirection direct);
	~Jafar();
	// Inherited via Enemy
	int time1;
	int time2;
	int time3 = 0;
	virtual bool isAttack() override;
	virtual void update(float deltaTime) override;

private:
	virtual void Refresh() override;
	virtual void LoadResource() override;
	virtual void UpdateRender(Global::EState currentState) override;
	virtual void DetermineDirection(Global::EState state, Global::EDirection direct);
};

#endif __JAFAR_H__