#pragma once
#ifndef _DEMO_SENCE_H
#define _DEMO_SENCE_H
#include"ISence.h"
#include"Aladdin.h"
#include"KeyBoard.h"
#include"Ground.h"
#include"Camera.h"
#include"Application.h"
#include"Map.h"
#include"Object.h"
#include<vector>
#include"QuadTree.h"
#include"Sound.h"
#include "DisPlay.h"
#include "AladdinGame.h"
#include "SenceManager.h"
#include "BossScene.h"
class PlaySence :public ISence
{
private:
	void					AladdinTakeAction(Global::EState currentState);
	Aladdin*				_aladdin;
	Camera*					_camera;
	Map*					_map;
	std::vector<Object*>	_listObject;
	Application*			_application;
	QuadTree*				_quadtree;
	Sound*					_sound;
	DisPlay*				_display;
	bool					_pastLevel1;		//Biến báo hiệu qua màn 1

public:
	PlaySence();
	~PlaySence();

	void					Render();
	void					LoadContent();
	void					Update(float delta);
	void					ProcessInput();
	void					OnKeyDown(int keyCode);
	void					OnKeyUp(int keyCode);
	void					IsDead();
};

#endif _DEMO_SENCE_H