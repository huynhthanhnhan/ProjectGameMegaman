#pragma once
#ifndef __Helit_H__
#define __Helit_H__
#include"Enemy.h"
#include"HelitBullet.h"
#define V_Helit 10
#define W_Helit_NORMAL 32
#define H_Helit_NORMAL 64
class Helit
	:public Enemy
{
public:
	Helit();
	Helit(int xRegion, int yRegion, int widthRegion, int heightRegion, Global::EDirection direct);
	~Helit();

	// Inherited via Enemy
	virtual void update(float deltaTime) override;
	virtual bool isAttack() override;
	virtual Collision::ResultCollision processCollision(Object * obj) override;
private:
	virtual void DetermineDirection(Global::EState state, Global::EDirection direct);
	virtual void Refresh() override;
	virtual void LoadResource() override;
	virtual void UpdateRender(Global::EState currentState) override;

	// Inherited via Enemy
};

#endif __Helit_H__