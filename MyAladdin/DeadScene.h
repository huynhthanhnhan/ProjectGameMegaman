#pragma once
#ifndef _DEAD_SENCE_H
#define _DEAD_SENCE_H
#include"ISence.h"
#include"KeyBoard.h"
#include"Camera.h"
#include"Application.h"
#include"MapDead.h"
#include<vector>
#include"Sound.h"
#include"Animation.h"

#include"SenceManager.h"
typedef D3DXVECTOR3 Location3D;
class DeadScene :public ISence, public Animation
{
private:
	Camera*					_camera;
	Application*			_application;
	Sound*					_sound;
	MapDead*				_mapdead;
	Animation*				_animation;

	D3DXVECTOR3 aladdin2;
	D3DXVECTOR3 abu2;
	virtual void Render(Global::EDirection direct,
		Global::EState state,
		D3DXVECTOR3 position,
		D3DXVECTOR2 scale = D3DXVECTOR2(1, 1),
		D3DXVECTOR2 translation = D3DXVECTOR2(0, 0),
		float		rotation = 0,
		D3DXVECTOR2 rotationCenter = D3DXVECTOR2());
	virtual void UpdateRender(Global::EState currentState);
	virtual void LoadResource() override;
	virtual void Refresh();
public:
	DeadScene();
	~DeadScene();

	void					Render();
	void					LoadContent();
	void					Update(float delta);
	void					ProcessInput();
	void					OnKeyDown(int keyCode);
	void					OnKeyUp(int keyCode);
	void					IsDead();

};

#endif _DEAD_SENCE_H