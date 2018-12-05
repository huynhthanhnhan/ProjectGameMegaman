#pragma once
#ifndef __MAPBOSS_H__
#define __MAPBOSS_H__
#include"Graphics.h"
#include"ResourceImage.h"
#include"Rect.h"
#include"Camera.h"
#include"Application.h"
#include"ResourceFile.h"
#include"Global.h"
class MapBoss
{
public:
	enum EMapID
	{
		MapBoss1,
		MapBoss2
	};

private:
	D3DXVECTOR3				_position;
	Rect					_rectMapBoss1, _rectMapBoss2;

	LPDIRECT3DTEXTURE9		_mapBossTexturePart1, _mapBossTexturePart2;

	Camera*					_camera;

	Global::Transform		_transform;
public:
	MapBoss();
	MapBoss(int x, int y, int z);
	~MapBoss();
	void					SetCamera(Camera* camera);
	void					LoadResource();
	void					Render(MapBoss::EMapID mapId);
};

#endif __MAPBOSS_H__