#pragma once
#ifndef __NOTORBANGER_H__
#define __NOTORBANGER_H__
#include"Enemy.h"
#include"NotorbangerBullet.h"
#define V_Notorbanger 10
#define W_Notorbanger_NORMAL 32
#define H_Notorbanger_NORMAL 64
#define D_ATTACK_NOTORBANGER 200
class Notorbanger
	:public Enemy
{
public:
	Notorbanger();
	Notorbanger(int xRegion, int yRegion, int widthRegion, int heightRegion, Global::EDirection direct);
	~Notorbanger();

	// Inherited via Enemy
	virtual void update(float deltaTime) override;
	virtual bool isAttack() override;
	float _timeAttack;
	bool _canAttack = false;
	int _time = 3;
	int _timeDelay;
	int _timeDelayCount = _timeDelay;
	bool bJump = false;
private:
	virtual void DetermineDirection(Global::EState state, Global::EDirection direct);
	virtual void Refresh() override;
	virtual void LoadResource() override;
	virtual void UpdateRender(Global::EState currentState) override;
	void caculateSpeed(float deltaTime);

	// Inherited via Enemy
};

#endif __NOTORBANGER_H__