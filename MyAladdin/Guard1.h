#pragma once
#ifndef __GUARD1_H__
#define __GUARD1_H__
#include "Enemy.h"
#include"Sound.h"
#define V_GUARD1 10
#define W_GUARD1_NORMAL 80
#define H_GUARD1_NORMAL 130
class Guard1 :
	public Enemy
{
public:
	Sound* _sound;
	Guard1();
	Guard1(int xRegion, int yRegion, int widthRegion, int heightRegion, Global::EDirection direct);
	~Guard1();

	// Inherited via Enemy
	virtual void		update(float deltaTime) override;
	virtual bool		isAttack() override;
private:
	virtual void		Refresh() override;
	virtual void		LoadResource() override;
	virtual void		UpdateRender(Global::EState currentState) override;
	// Inherited via Enemy
};

#endif __GUARD1_H__