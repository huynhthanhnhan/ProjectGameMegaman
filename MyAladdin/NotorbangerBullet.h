#pragma once
#ifndef __NotorbangerBULLET_H__
#define __NotorbangerBULLET_H__
#include"Bullet.h"
#include"Sound.h"
#define DISTANCE_CIVILIANBULLET 5
class NotorbangerBullet    //Cái chậu
	:public Bullet
{
public:
	NotorbangerBullet(int x, int y, Global::EDirection direct);
	~NotorbangerBullet();

	// Kế thừa lớp Bullet
	Sound* _sound;
	virtual bool isFinish() override;
	float _timeLife;
	virtual Collision::ResultCollision processCollision(Object * obj) override;
	virtual bool isCanAttack() override;
private:
	virtual void Render(Global::EDirection direct, Global::EState state, D3DXVECTOR3 position, D3DXVECTOR2 scale = D3DXVECTOR2(1, 1), D3DXVECTOR2 translation = D3DXVECTOR2(0, 0), float rotation = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2());
	virtual void LoadResource() override;
	virtual void UpdateRender(Global::EState currentState) override;
};

#endif __NotorbangerBULLET_H__