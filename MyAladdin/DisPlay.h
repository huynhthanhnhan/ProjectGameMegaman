#pragma once
#ifndef __DISPLAY_H__
#define __DISPLAY_H__
#include"Graphics.h"
#include"Application.h"
#include"SpriteManager.h"
#include"HealthPoint.h"
#include"Shop.h"
#include"Aladdin.h"
typedef D3DXVECTOR3 Location3D;
class DisPlay
{
private:
	DisPlay();
	static DisPlay*			__instance;
	Graphics*				_graphics;
	Application*			_apps;
	//===================================================
	//Location
	//===================================================
	Location3D				_hpLocation;
	Location3D				_shop;
	Location3D				_scoreLocation;
	Location3D				_lifeLocation;
	Location3D				_numberOfAppleLocation;
	Location3D				_gemLocation;
	//===================================================
	//Sprite
	//===================================================
	SpriteManager*			_sprite;
	HealthPoint*			_healthPoint;
	Shop*					_Shop;
	//===================================================
	//Rectangle
	//===================================================
	Rect					_hpRect;
	Rect					_scoreRect;
	Rect					_lifeRect;
	Rect					_appleRect;
	Rect					_gemRect;
public:
	static DisPlay*			Instance();
	int time0, time1, time2, timeapple, timegem, timeadeal;

	void					render(int hp, int life, int numberOfApple, int gem, int score);
	~DisPlay();
private:
	void					LoadResource();
	void					RenderText(int number, Location3D location);
};

#endif __DISPLAY_H__