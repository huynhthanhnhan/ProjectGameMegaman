#pragma once
#ifndef _BOSS_SENCE_H
#define _BOSS_SENCE_H
#include"ISence.h"
#include"Aladdin.h"
#include"KeyBoard.h"
#include"Ground.h"
#include"Camera.h"
#include"Application.h"
#include"MapBoss.h"
#include"Object.h"
#include<vector>
#include"QuadTree.h"
#include"Sound.h"
#include "DisPlay.h"
class BossScene :public ISence
{
private:
	void					AladdinTakeAction(Global::EState currentState);
	Aladdin*				_aladdin;
	Camera*					_camera;
	MapBoss*				_mapboss;
	std::vector<Object*>	_listObject;
	Application*			_application;
	QuadTree*				_quadtree;
	Sound*					_sound;
	DisPlay*				_display;

public:
	BossScene();
	~BossScene();

	void					Render();
	void					LoadContent();
	void					Update(float delta);
	void					ProcessInput();
	void					OnKeyDown(int keyCode);
	void					OnKeyUp(int keyCode);
	void					IsDead();
};

#endif _BOSS_SENCE_H