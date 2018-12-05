#pragma once
#ifndef _LEVELCOMPLETE_SENCE_H
#define _LEVELCOMPLETE_SENCE_H
#include"ISence.h"
#include"KeyBoard.h"
#include"Camera.h"
#include"Application.h"
#include"MapLevelComplete.h"
#include<vector>
#include"Sound.h"
#include"Animation.h"
#include"SpriteManager.h"
#include <ctime>
typedef D3DXVECTOR3 Location3D;
class LevelCompleteScene :public ISence, public Animation
{
private:
	Camera*					_camera;
	Application*			_application;
	Sound*					_sound;
	MapLevelComplete*		_mapcomplete;
	Animation*				_animation;
	SpriteManager*			_sprite_victory;
	Rect					_victoryRect;
	D3DXVECTOR3 abu = Location3D(800, 520, 0);
	D3DXVECTOR3 aladdin = Location3D(890, 520, 0);
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
	int time = 0;
public:
	LevelCompleteScene();
	~LevelCompleteScene();

	void					Render();
	void					LoadContent();
	void					Update(float delta);
	void					ProcessInput();
	void					OnKeyDown(int keyCode);
	void					OnKeyUp(int keyCode);
	void					IsDead();

};

#endif _LEVELCOMPLETE_SENCE_H