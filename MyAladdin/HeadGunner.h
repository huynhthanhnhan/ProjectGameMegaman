#pragma once
#ifndef __HEADGUNNER_H__
#define __HEADGUNNER_H__
#include "Enemy.h"
#define V_GUNNER 10
#define W_GUNNER_NORMAL 80
#define H_GUNNER_NORMAL 130
#define D_ATTACK_GUNNER 80
class HeadGunner :
	public Enemy
{
public:
	Sound* _sound;
	HeadGunner();
	HeadGunner(int xRegion, int yRegion, int widthRegion, int heightRegion, Global::EDirection direct);
	~HeadGunner();

	// Inherited via Enemy
	virtual void		update(float deltaTime) override;
	virtual bool		isAttack() override;
private:
	virtual void		DetermineDirection(Global::EState state, Global::EDirection direct);
	virtual void		Refresh() override;
	virtual void		LoadResource() override;
	virtual void		UpdateRender(Global::EState currentState) override;
	// Inherited via Enemy
};

#endif __HEADGUNNER_H__
