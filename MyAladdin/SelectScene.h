#pragma once
#ifndef _MENU_SENCE_H
#define _MENU_SENCE_H
#include"ISence.h"
#include"KeyBoard.h"
#include"Camera.h"
#include"Application.h"
#include"MapMenu.h"
#include<vector>
#include"Sound.h"
#include"Animation.h"
#include"SenceManager.h"
#include"Graphics.h"
typedef D3DXVECTOR3 Location3D;
class SelectScene :public ISence, public Animation
{
private:
	Camera*					_camera;
	Application*			_application;
	Sound*					_sound;
	MapMenu*				_mapmenu;
	Animation*				_animation;
	SpriteManager*			_sprite_menu;
	Rect					_menuRect;
	Graphics*				_graphic;
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
	bool GoKnife;
	D3DXVECTOR3 location = Location3D(400, 400, 0);
	D3DXVECTOR3 knife = Location3D(250, 320, 0);
public:
	SelectScene();
	~SelectScene();
	void					Render();
	void					LoadContent();
	void					Update(float delta);
	void					ProcessInput();
	void					OnKeyDown(int keyCode);
	void					OnKeyUp(int keyCode);
	void					IsDead();

};

#endif _MENU_SENCE_H