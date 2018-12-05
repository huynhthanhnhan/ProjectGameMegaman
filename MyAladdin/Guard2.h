#pragma once
#ifndef __GUARD2_H__
#define __GUARD2_H__
#include "Enemy.h"
#include"Sound.h"
#define V_GUARD2 20
#define W_GUARD2_NORMAL 80
#define H_GUARD2_NORMAL 130
#define D_ATTACK_GUARD2 185
class Guard2 :
	public Enemy
{
private:
	int		_time;
	int		_timeAction;
public:
	Sound* _sound;
	Guard2();
	Guard2(int xRegion, int yRegion, int widthRegion, int heightRegion, Global::EDirection direct);
	~Guard2();

	// Inherited via Enemy
	virtual void			update(float deltaTime) override;
	virtual bool			isAttack() override;
private:
	virtual void			Refresh() override;
	virtual void			LoadResource() override;
	virtual void			UpdateRender(Global::EState currentState) override;

	// Inherited via Enemy
};

#endif __GUARD2_H__