#pragma once
#ifndef __SNAKE_BULLET_H__
#define __SNAKE_BULLET_H__
#include "Bullet.h"
#include "Sound.h"
#include "Aladdin.h"
#include "Jafar.h"
#define DISTANCE_FIRE 100
class SnakeBullet :
	public Bullet
{
public:
	Sound* _sound;
	SnakeBullet();
	SnakeBullet(int x, int y, Global::EDirection direct, float angle = 0, int distance = DISTANCE_FIRE);
	~SnakeBullet();
	bool	_isFinish;

	// Inherited via Bullet
	void setFinish();
	virtual bool isFinish() override;
	virtual void update(float deltaTime);
	virtual Collision::ResultCollision processCollision(Object * obj) override;
private:
	D3DXVECTOR2 _preV = D3DXVECTOR2(0, 0);
	D3DXVECTOR2 _nextPos = D3DXVECTOR2(0, 0);
	virtual void Render(Global::EDirection direct, Global::EState state, D3DXVECTOR3 position, D3DXVECTOR2 scale = D3DXVECTOR2(1, 1), D3DXVECTOR2 translation = D3DXVECTOR2(0, 0), float rotation = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2());
	virtual void DetermineDirection(Global::EState state, Global::EDirection direct);
	virtual void LoadResource() override;
	virtual void UpdateRender(Global::EState currentState) override;

	virtual bool isCanAttack() override;
};

#endif __SNAKE_BULLET_H__