#pragma once
#ifndef __SWORD_H__
#define __SWORD_H__
#include "Bullet.h"
#include "Sound.h"
#define DISTANCE_SWORD 30
class Sword :
	public Bullet
{
private:
	int			_time;
public:
	Sound* _sound;
	Sword();
	Sword(int x, int y, Global::EDirection direct, float angle = 0, int distance = DISTANCE_SWORD);
	~Sword();

	// Inherited via Bullet
	virtual bool isFinish() override;
	virtual Collision::ResultCollision processCollision(Object * obj) override;
private:
	virtual void Render(Global::EDirection direct, Global::EState state, D3DXVECTOR3 position, D3DXVECTOR2 scale = D3DXVECTOR2(1, 1), D3DXVECTOR2 translation = D3DXVECTOR2(0, 0), float rotation = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2());
	virtual void DetermineDirection(Global::EState state, Global::EDirection direct);
	virtual void LoadResource() override;
	virtual void UpdateRender(Global::EState currentState) override;

	virtual bool isCanAttack() override;
};

#endif __SWORD_H__